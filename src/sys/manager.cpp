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
  SDL_Event s_event;

  // Handle SDL events
  if(SDL_PollEvent(&s_event)) {
    switch(s_event.type) {
      case SDL_KEYDOWN:
        {
          key_event k(key_event::type::press, s_event.key.keysym.sym, s_event.key.keysym.scancode, s_event.key.state, s_event.key.keysym.mod);
          events.push(event(k));
          INFO("KEY_DOWN: ", SDL_GetKeyName(s_event.key.keysym.sym));
        }
        break;
      case SDL_KEYUP:
        {
          key_event k(key_event::type::release, s_event.key.keysym.sym, s_event.key.keysym.scancode, s_event.key.state, s_event.key.keysym.mod);
          events.push(event(k));
          INFO("KEY_UP: ", SDL_GetKeyName(s_event.key.keysym.sym));
        }
        break;
      case SDL_WINDOWEVENT:
        switch(s_event.window.event) {
          case SDL_WINDOWEVENT_CLOSE:
            {
              system_event sys(system_event::type::halt);
              events.push(event(sys));
            }
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }

  // We process all events until the queue is empty
  while(!events.empty()) {

    // Ascertain this type of event exists
    auto find_list = delegates.find(events.front().type);
    if(find_list != delegates.end()) {

      // Obtain the list of listeners
      const delegatelist& list = find_list->second;

      // Call the method for all delegates registered
      for(const auto &it : list)
        it(events.front());

      // Pop the event from the queue
      events.pop();
    } else {
      ERROR("Unexpected event occured", eventstring[static_cast<int>(events.front().type)]);
      events.pop(); // Prevents infinite loop
    }
  }
}


uint32_t const& manager::get_delegate_id() {
  return ++ids;
}
