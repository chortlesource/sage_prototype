////////////////////////////////////////////////////////////////////////////
//
// sage - layer.hpp
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

#ifndef _SAGE_LAYER_HPP
#define _SAGE_LAYER_HPP


/////////////////////////////////////////////////////////////
// LAYER Class
//
// The layer class contains objects to be drawn

class layer : public object {
public:
  layer(state_ptr const& g_state);
  virtual ~layer();

  virtual bool const& update(state_ptr const& g_state) override;
  virtual void        finalize(state_ptr const& g_state) override;
  virtual void        set_paused(bool const& value);


  virtual void add(object_ptr const& obj);
  virtual void pop(object_ptr const& obj);

protected:
  std::unordered_map<unsigned int, object_ptr> l_objects;
  std::vector<unsigned int>                    l_objectid;

  void draw(state_ptr const& g_state);
};


#endif // _SAGE_LAYER_HPP
