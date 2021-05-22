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
  none, system, button
};


static const std::array<std::string, 3> eventstring = {
  "NON_EVENT", "SYSTEM_EVENT", "BUTTON_EVENT"
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
// EVENT struct
//
// The main event struct which contains all event types

struct event {
  eventtype    type;
  system_event system;
  button_event button;

  event() : type(eventtype::none), system(), button() {};
  event(system_event const& sys) : type(eventtype::system), system(sys), button() {};
  event(button_event const& btn) : type(eventtype::button), system(), button(btn) {};
};


#endif // _SAGE_EVENTS_HPP
