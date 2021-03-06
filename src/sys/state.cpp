////////////////////////////////////////////////////////////////////////////
//
// sage - state.cpp
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


/////////////////////////////////////////////////////////////////
// STATE Class implementation
//

state::state() : g_timer(), g_assets(), g_manager(), g_window(), g_input(), g_status(status::init), g_config(Json::Value::null) {}


state::~state() {}


void state::initialize(state_ptr const& g_state) {
  // Load the default configuration files
  g_config             = g_assets.load_json("init", _APP_INIT);
  Json::Value g_fonts  = g_assets.load_json("fonts", g_config["FONTS_JSON"].asString());
  Json::Value g_colors = g_assets.load_json("colors", g_config["COLORS_JSON"].asString());
  Json::Value g_tiles  = g_assets.load_json("atlas", g_config["ATLAS_JSON"].asString());

  // Initialize the game window
  g_window.initialize(g_config);

  // Initialize the stage
  g_stage.initialize(g_config);

  // Load the game fonts
  g_assets.load_fonts(g_fonts);

  // Load the game colors
  g_assets.load_colors(g_colors);

  // Load the game tiles
  g_assets.load_tiles(g_state, g_tiles);

  // Set the gamestate status
  g_status = state::status::run;
}


void state::update() {
  if(g_status != state::status::run) return;

  // Obtain the current mouse state
  g_input.buttons = SDL_GetMouseState(&g_input.x, &g_input.y);

  // Update the keyboard state
  SDL_PumpEvents();
}
