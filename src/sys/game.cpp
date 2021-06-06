////////////////////////////////////////////////////////////////////////////
//
// sage - game.cpp
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
// GAME Class implementation
//

game::game(state_ptr const& g_state, unsigned int const& seed) {
  // Initialize our game Objects
  g_map   = std::make_shared<map>(g_state, seed);
  g_frame = std::make_shared<frame>(g_state);

  // Add our map to the stage
  g_state->get_stage()->add(g_map);
  g_state->get_stage()->add(g_frame);
}

void game::update(state_ptr const& g_state) {
  // Do something
}

void game::finalize(state_ptr const& g_state) {
  // Finalize game objects
  g_map->finalize(g_state);
  g_frame->finalize(g_state);

  // Remove all objects from the stage
  g_state->get_stage()->clear(g_state);
}
