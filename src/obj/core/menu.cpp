////////////////////////////////////////////////////////////////////////////
//
// sage - menu.cpp
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
// MENU Class implementation
//

menu::menu(state_ptr const& g_state) : layer(g_state), m_active(0) {
  // Register our delegates for events
  register_delegates(g_state);
}


menu::~menu() {};


void menu::finalize(state_ptr const& g_state) {
  for(auto &id : l_objectid)
    l_objects[id]->finalize(g_state);

  // Remove our event delegates
  remove_delegates(g_state);
};


void menu::add_menu_object(object_ptr const& obj) {
  m_objects.push_back(obj);
}


void menu::register_delegates(state_ptr const& g_state) {
  // Register the event listeners
  std::function<void(event const&)> callback = [=](event const& e) -> void { this->on_event(e); };

  o_manager->add_delegate(delegate(o_eventid, eventtype::key, callback));
}


void menu::remove_delegates(state_ptr const& g_state) {
  o_manager->remove_delegate(delegate(o_eventid, eventtype::key, nullptr));
}


void menu::on_event(event const& e) {
  if(!o_active || m_objects.empty()) return;

  switch(e.type) {
    case eventtype::key:
      if(e.key.keytype == key_event::type::release) {
        switch(e.key.scancode) {
          case SDL_SCANCODE_TAB:
            {
              unsigned int size = m_objects.size();
              m_objects[m_active]->set_active(false);

              if(m_active < size)
                m_active += 1;
              if(!(m_active < size))
                m_active = 0;

              for(unsigned int i = m_active; i < size; i++) {
                if(m_objects[i]->get_visible()) {
                  m_objects[i]->set_active(true);
                  return;
                }
              }
            }
            break;
          default:
            break;
        };
      }
    default:
      break;
  }
}
