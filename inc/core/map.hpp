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
// The map class is a basic level map to be drawn to the stage

class map : public object {
public:
  map(state_ptr const& g_state, int const& w, int const& h);
  ~map();

  virtual bool const& update(state_ptr const& g_state) override;

private:
  int              m_width;
  int              m_height;
  int              m_offsetx;
  int              m_offsety;
  int              m_zoom;
  bool             m_pressed;
  sdltexture_ptr   m_overlay;
  sdltexture_ptr   m_maptxtr;
  std::vector<int> m_map;

  void gen_overlay(state_ptr const& g_state, int const& tile_w, int const& tile_h);
  void gen_maptxtr(state_ptr const& g_state, int const& tile_w, int const& tile_h);

};

#endif // _SAGE_MAP_HPP
