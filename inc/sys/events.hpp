////////////////////////////////////////////////////////////////////////////
//
// sage - events.hpp
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

#ifndef _SAGE_EVENTS_HPP
#define _SAGE_EVENTS_HPP


/////////////////////////////////////////////////////////////
// EVENT enumeration and strings
//

enum class eventtype {
  none, system, button, key
};


static const std::array<std::string, 4> eventstring = {
  "NON_EVENT", "SYSTEM_EVENT", "BUTTON_EVENT", "KEY_EVENT"
};


/////////////////////////////////////////////////////////////
// SYSTEM_EVENT Struct
//

struct system_event {
  enum class type { none, halt, pause };

  const type action;

  system_event() : action(type::none) {};
  system_event(type const& a) : action(a) {};
};


/////////////////////////////////////////////////////////////
// BUTTON_EVENT Struct
//

struct button_event {
  enum class type { none, clicked };

  const type        action;
  const std::string command;

  button_event() : action(type::none), command() {};
  button_event(type const& a, std::string const& c) : action(a), command(c) {};
};


/////////////////////////////////////////////////////////////
// KEY_EVENT Struct
//

struct key_event {
  enum class type { none, press, release };

  const type          keytype;
  const unsigned int  key;
  const unsigned int  scancode;
  const unsigned int  action;
  const unsigned int  mods;

  key_event() : keytype(type::none), key(0), scancode(0), action(0), mods(0) {};
  key_event(type const& t, int const& k, int const s, int const& a, int const& m) : keytype(t), key(k), scancode(s), action(a), mods(m) {};
};

/////////////////////////////////////////////////////////////
// EVENT struct
//
// The main event struct which contains all event types

struct event {
  eventtype    type;
  system_event system;
  button_event button;
  key_event    key;

  event() : type(eventtype::none), system(), button(), key() {};
  event(system_event const& s) : type(eventtype::system), system(s), button(), key() {};
  event(button_event const& b) : type(eventtype::button), system(), button(b), key() {};
  event(key_event const& k)    : type(eventtype::key), system(), button(), key(k) {};
};


#endif // _SAGE_EVENTS_HPP
