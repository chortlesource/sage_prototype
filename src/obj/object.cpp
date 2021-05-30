////////////////////////////////////////////////////////////////////////////
//
// sage - object.cpp
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
// OBJECT Class implementation
//

object::object(state_ptr const& g_state) : initialized(false), o_visible(true),
  o_paused(false), o_changed(false), o_source({0,0,0,0}), o_position({0,0,0,0}),
    o_color({0,0,0,0}), o_texture(nullptr), o_eventid(g_state->get_manager().get_delegate_id()) {}

object::~object() {
  initialized = false;
  o_texture   = nullptr;
}


bool const& object::update(state_ptr const& g_state) { return o_changed; };

void        object::finalize(state_ptr const& g_state) {};

void object::set_visible(bool const& value) {
  o_changed = true;
  o_visible = value;
};


void object::set_paused(bool const& value)  {
  o_paused = value;
};


void object::set_position(SDL_Rect const& value) {
  o_changed  = true;
  o_position = SDL_Rect { value.x, value.y, o_source.w, o_source.h };
};


void object::set_color(SDL_Color const& value) {
  o_changed = true;
  o_color   = value;
};


void object::set_eventid(unsigned int const& value) {
  o_eventid = value;
};


bool const&         object::get_visible()  const {
  return o_visible;
};


bool const&         object::get_paused()   const {
  return o_paused;
};


SDL_Rect  const&    object::get_source()   const {
  return o_source;
};


SDL_Rect  const&    object::get_position() const {
  return o_position;
};


SDL_Color const&    object::get_color()    const {
  return o_color;
};


SDL_Texture*        object::get_texture()  const {
  return o_texture.get();
};

sdltexture_ptr      object::get_textureptr()  const {
  return o_texture;
}


unsigned int const& object::get_id()       const {
  return o_eventid;
};
