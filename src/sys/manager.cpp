////////////////////////////////////////////////////////////////////////////
//
// sage - manager.cpp
//
// Copyright (c) 2021 Christopher M. Short
//
// This file is part of sage.
//
// sage is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// sage is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
// License for more details.
//
// You should have received a copy of the GNU General Public License
// along with sage. If not, see <https://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////

#include <sage.hpp>


/////////////////////////////////////////////////////////////
// DELEGATE implementation
//

void delegate::operator()(event const& e) const {
  // Execute the delegate function with a call to operator();
  callback(e);
};


bool delegate::operator==(delegate const& rhs) const noexcept {
  // Compare delegates to see if the pointers match
  return (id == rhs.id) && (type == rhs.type);
};


eventtype const& delegate::get_type() const noexcept {
  return type;
};


uint32_t const& delegate::get_id() const noexcept {
  return id;
};


/////////////////////////////////////////////////////////////
// MANAGER implementation
//

bool manager::add_delegate(delegate const& del) {
  // Retrieve or create the list
  delegatelist& list = delegates[del.get_type()];

  // Prevent duplicates
  for(const auto &it : list)
    if(del == it) return false;

  list.push_back(del);
  return true;
}


bool manager::remove_delegate(delegate const& del) {
  // Find the relevant list
  auto find_list = delegates.find(del.get_type());
  if(find_list != delegates.end()) {
    delegatelist& list = find_list->second;
    for(auto it = list.begin(); it != list.end(); ++it) {
      if(del == (*it)) {
        list.erase(it); // Remove the item
        return true;
      }
    }
  }

  return false;
}


void manager::send_event(event const& e) {
  events.push(e);
}


void manager::update() {
  // We process all events until the queue is empty
  while(!events.empty()) {

    // Ascertain this type of event exists
    auto find_list = delegates.find(events.front().e_type);
    if(find_list != delegates.end()) {

      // Obtain the list of listeners
      const delegatelist& list = find_list->second;

      // Call the method for all delegates registered
      for(const auto &it : list)
        it(events.front());

      // Pop the event from the queue
      events.pop();
    } else {
      ERROR("Unexpected event occured", eventstring[static_cast<int>(events.front().e_type)]);
      events.pop(); // Prevents infinite loop
    }
  }
}


uint32_t const& manager::get_delegate_id() {
  return ++ids;
}
