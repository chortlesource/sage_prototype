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
  none, system
};


static const std::array<std::string, 4> eventstring = {
  "NON_EVENT", "SYSTEM_EVENT"
};


/////////////////////////////////////////////////////////////
// SYSTEM_EVENT Struct
//

struct system_event {
  enum class action { none, halt, pause };

  const eventtype e_type;
  const action    e_action;

  system_event(eventtype const& e, action const& a) : e_type(e), e_action(a) {};
};


/////////////////////////////////////////////////////////////
// EVENT Union
//
// The main event Union which contains all event types

union event {
  const eventtype    e_type;
  const system_event e_system;

  event() : e_type(eventtype::none) {};
  event(system_event const& sys) : e_system(sys) {};
};


#endif // _SAGE_EVENTS_HPP
