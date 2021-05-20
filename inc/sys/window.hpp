////////////////////////////////////////////////////////////////////////////
//
// sage - window.hpp
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

#ifndef _SAGE_WINDOW_HPP
#define _SAGE_WINDOW_HPP


/////////////////////////////////////////////////////////////
// WINDOW Class
//
// The window class handles the sdl window logic

class window {
public:
  window() {}
  ~window();

  void initialize(Json::Value const& g_config);
  void update(state_ptr const& g_state);

  SDL_Window*   get_window();
  SDL_Renderer* get_render();

private:
  bool          initialized;
  sdlwindow_ptr g_window;
  sdlrender_ptr g_renderer;
};

#endif // _SAGE_WINDOW_HPP
