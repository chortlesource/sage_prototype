////////////////////////////////////////////////////////////////////////////
//
// sage - object.hpp
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

#ifndef _SAGE_OBJECT_HPP
#define _SAGE_OBJECT_HPP


/////////////////////////////////////////////////////////////
// OBJECT Class
//
// The object class is an interface for game objects

class object {
public:
  object(state_ptr const& g_state);
  virtual ~object();

  virtual bool const& update(state_ptr const& g_state);
  virtual void        finalize(state_ptr const& g_state);

  // object get and set functions
  virtual void set_visible(bool const& value) final;
  virtual void set_paused(bool const& value)  final;
  virtual void set_position(SDL_Rect const& value) final;
  virtual void set_color(SDL_Color const& value) final;
  virtual void set_eventid(unsigned int const& value) final;

  virtual bool const&         get_visible()     const final;
  virtual bool const&         get_paused()      const final;
  virtual SDL_Rect  const&    get_source()      const final;
  virtual SDL_Rect  const&    get_position()    const final;
  virtual SDL_Color const&    get_color()       const final;
  virtual SDL_Texture*        get_texture()     const final;
  virtual sdltexture_ptr      get_textureptr()  const final;
  virtual unsigned int const& get_id()          const final;

protected:
  bool           initialized;
  bool           o_visible;
  bool           o_paused;
  bool           o_changed;

  SDL_Rect       o_source;
  SDL_Rect       o_position;
  SDL_Color      o_color;
  sdltexture_ptr o_texture;

  unsigned int   o_eventid;
};


#endif // _SAGE_OBJECT_HPP
