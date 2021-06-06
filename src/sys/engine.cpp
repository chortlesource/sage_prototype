////////////////////////////////////////////////////////////////////////////
//
// sage - engine.hpp
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
// ENGINE Class implementation
//

engine::engine() {
  // Initialize SDL Library
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
   DEBUG("SDL_INIT_ERROR: ", SDL_GetError());
   return;
  } else {
   INFO("Initialized SDL2 Library");
  }

  if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
   DEBUG("SDL_IMG_INIT_ERROR: ", IMG_GetError());
   return;
  } else {
    INFO("Initialized SDL_IMG Library");
  }

  if(TTF_Init() != 0) {
   DEBUG("[SDL_TTF_INIT_ERROR]: ", TTF_GetError());
   return;
  } else {
   INFO("Initialized SDL_TTF Library");
  }

  SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "2");

  // Initialize the game state
  INFO("Initialize the gamestate");
  g_state = std::make_shared<state>();
  g_state->initialize(g_state);

  // Add engine event listeners
  register_delegates();

  // Initialize game
  on_user_init();

  initialized = true;
}


engine::~engine() {
  initialized = false;

  // Remove engine event listeners
  remove_delegates();
  g_state     = nullptr;

  IMG_Quit();
  INFO("Finalized SDL_TTF Library");

  TTF_Quit();
  INFO("Finalized SDL_TTF Library");

  SDL_Quit();
  INFO("Finalized SDL2 Library");
}


void engine::start() {
  if(!initialized) return;

  // Initialize the timer
  g_state->get_timer()->start();

  double rate    = 0.01;
  double elapsed = 0.00;

  // Main game loop
  while(g_state->get_status() != state::status::exit) {

    // Update the timer each loop
    g_state->get_timer()->update();
    double delta = g_state->get_delta();

    // Calculate the frame time elapsed
    if(delta > 0.80) delta = 0.80;
    elapsed += delta;

    while(elapsed >= rate) {
      // Update the game state
      g_state->update();

      // Poll for game events
      g_state->get_manager()->update();

      // Handle game logic
      on_user_update();

      // Update the game world
      g_state->get_stage()->update(g_state);

      // Render the game world to the screen
      g_state->get_window()->update(g_state);
      elapsed -= rate;
    }
  }

  INFO("SAGE HALT");
  on_user_finalize();
}


void engine::on_user_init() {
  // Initialize the main menu
  layer_ptr mainmenu = std::make_shared<menumain>(g_state);
  g_state->get_stage()->add_menu("MAIN_MENU", mainmenu);

  // Initialize the world menu
  layer_ptr worldmenu = std::make_shared<menuworld>(g_state);
  g_state->get_stage()->add_menu("WORLD_MENU", worldmenu);

  // Show the main menu by default
  g_state->get_stage()->use_menu("MAIN_MENU");
  g_state->set_status(state::status::menu);
}


void engine::register_delegates() {
  eventid = g_state->get_manager()->get_delegate_id();

  // Register the event listeners
  std::function<void(event const&)> callback = [=](event const& e) -> void { this->on_event(e); };

  g_state->get_manager()->add_delegate(delegate(eventid, eventtype::button, callback));
  g_state->get_manager()->add_delegate(delegate(eventid, eventtype::key, callback));
  g_state->get_manager()->add_delegate(delegate(eventid, eventtype::system, callback));
  g_state->get_manager()->add_delegate(delegate(eventid, eventtype::data, callback));
}


void engine::remove_delegates() {
  g_state->get_manager()->remove_delegate(delegate(eventid, eventtype::button, nullptr));
  g_state->get_manager()->remove_delegate(delegate(eventid, eventtype::key, nullptr));
  g_state->get_manager()->remove_delegate(delegate(eventid, eventtype::system, nullptr));
  g_state->get_manager()->add_delegate(delegate(eventid, eventtype::data, nullptr));
}


void engine::on_event(event const& e) {
  switch(e.type) {
    case eventtype::system:
      if(e.system.action == system_event::type::halt)
        g_state->get_logic()->sage_halt(g_state);
      break;
    case eventtype::button:
      if(e.button.command == "MNU_QUIT")
        g_state->get_logic()->sage_halt(g_state);
      else if(e.button.command == "MNU_WORLD_SHOW")
        g_state->get_stage()->use_menu("WORLD_MENU");
      else if(e.button.command == "MNU_WORLD_CREATE")
        g_state->get_manager()->send_event(event(data_event(data_event::type::request, "ENGINE", "WORLDSEED", "")));
      else if(e.button.command == "MNU_WORLD_CANCEL")
        g_state->get_stage()->pop_menu();
      else if(e.button.command == "MNU_CONT")
        g_state->get_logic()->toggle_main_menu(g_state);
      break;
    case eventtype::key:
      SDL_ShowCursor(SDL_DISABLE);
      if(e.key.keytype == key_event::type::release) {
        if(e.key.scancode == SDL_SCANCODE_ESCAPE)
          g_state->get_logic()->toggle_main_menu(g_state);
      }
      break;
    case eventtype::data:
      if(e.data.action == data_event::type::response && e.data.origin == "WORLDSEED")
        g_state->get_logic()->init_new_game(g_state, e.data.data);
      break;
    default:
      break;
  }
}
