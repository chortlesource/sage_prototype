////////////////////////////////////////////////////////////////////////////
//
// sage - map.hpp
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

#ifndef _SAGE_MAP_HPP
#define _SAGE_MAP_HPP


/////////////////////////////////////////////////////////////
// MAP Class
//
// The map class represents a basic level map

class map : public layer {
public:
  map(state_ptr const& g_state);

  virtual bool const& update(state_ptr const& g_state) override;

private:
  object_ptr gen;
  object_ptr cursor;
  int        width;
  int        height;

  void update_cursor(state_ptr const& g_state);
};

#endif // _SAGE_MAP_HPP
