////////////////////////////////////////////////////////////////////////////
//
// sage - logic.cpp
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
// LOGIC Class implementation
//

void logic::toggle_main_menu(state_ptr const& g_state) {
  // Toggle the main menu
  if(g_state->get_status() == state::status::run) {
    g_state->get_stage()->use_menu("MAIN_MENU");
    g_state->set_status(state::status::menu);
    return;
  }
  if(g_state->get_status() == state::status::menu && g_state->get_game() != nullptr) {
    g_state->get_stage()->pop_menu();
    g_state->set_status(state::status::run);
    return;
  }
}


void logic::init_new_game(state_ptr const& g_state, std::string const& seed) {
  // Hash the seed
  std::hash<std::string> to_hash;
  unsigned int const& hvalue = to_hash(seed);

  INFO("H: ", hvalue);

  // Clear the stage first
  g_state->get_stage()->clear(g_state);

  INFO("H: ", hvalue);


  // Initialize the new game
  game_ptr newgame = std::make_shared<game>(g_state, hvalue);
  g_state->set_game(newgame);
  g_state->set_status(state::status::run);

  INFO("Creating new world...");
}


void logic::sage_halt(state_ptr const& g_state) {
  g_state->set_status(state::status::exit);
}
