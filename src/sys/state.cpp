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

state::state() : g_status(status::init), g_input() {}


state::~state() {}


void state::initialize(state_ptr const& g_state) {
  g_status = state::status::run;
}


void state::update() {
  if(g_status != state::status::run) return;

  // Obtain the current mouse state
  g_input.buttons = SDL_GetMouseState(&g_input.x, &g_input.y);

  // Update the keyboard state
  SDL_PumpEvents();
}
