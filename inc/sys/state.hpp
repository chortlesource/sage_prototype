////////////////////////////////////////////////////////////////////////////
//
// sage - state.hpp
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

#ifndef _SAGE_STATE_HPP
#define _SAGE_STATE_HPP


/////////////////////////////////////////////////////////////////
// ISTATE Struct
//
// The istate struct contains state information about the mouse
// and keyboard input

struct istate {
  // Mouse state
  int             x;
  int             y;
  uint32_t        buttons;

  // Window state
  int             width;
  int             height;

  // Keyboard state
  const uint8_t  *keys;

  istate() : x(0), y(0), buttons(0), width(0), height(0), keys(SDL_GetKeyboardState(NULL)) {};
};


/////////////////////////////////////////////////////////////////
// STATE Class
//
// The state class is a container for game components

class state {
public:
  enum class status { init, run, menu, pause, exit };

  state();
  ~state();

  void initialize(state_ptr const& g_state);
  void update();

  // state get and set functions
  void set_status(status const& value) { g_status = value;}

  timer       &      get_timer()   { return g_timer; }
  assets      &      get_assets()  { return g_assets; }
  window      &      get_window()  { return g_window; }
  manager     &      get_manager() { return g_manager; }
  stage       &      get_stage()   { return g_stage; }
  game_ptr    &      get_game()    { return g_game; }
  istate      const& get_input()   { return g_input; }
  status      const& get_status()  { return g_status; }
  double      const& get_delta()   { return g_timer.delta(); }
  Json::Value const& get_config()  { return g_config; }

private:
  timer    g_timer;
  assets   g_assets;
  manager  g_manager;
  stage    g_stage;
  game_ptr g_game;
  window   g_window;
  istate   g_input;
  status   g_status;

  Json::Value g_config;
};


#endif // _SAGE_STATE_HPP
