////////////////////////////////////////////////////////////////////////////
//
// sage - button.cpp
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
// BUTTON Class implementation
//

button::button(state_ptr const& g_state, std::string const& caption, std::string const& fontid, std::string const& action) : object(g_state) {
  b_clicked  = false;
  b_action   = action;
  b_texts.push_back(gtext(g_state, caption, "L_GRAY", "NONE"));
  b_texts.push_back(gtext(g_state, caption, "BLUE", "NONE"));
  b_texts.push_back(gtext(g_state, caption, "D_GRAY", "NONE"));

  o_source    = b_texts[0].get_source();
  o_position  = b_texts[0].get_position();
  o_texture   = b_texts[0].get_textureptr();
  initialized = true;
}


button::~button() {
  initialized = false;

  o_texture = nullptr;
}


bool const& button::update(state_ptr const& g_state) {
  if(o_paused) {
    o_texture = b_texts[2].get_textureptr();
    return o_changed;
  }

  if(SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE)
    handle_mouse(g_state);
  else
    handle_key(g_state);

  // Let our layer know if we need to redraw the button
  return o_changed;
}


void button::handle_mouse(state_ptr const& g_state) {
  // Lambda function for convenience
  auto is_over = [&] (int const& x, int const& y) {
    return (x > o_position.x && x < o_position.x + o_position.w && y > o_position.y && y < o_position.y + o_position.h);
  };

  // Obtain the current position of the mouse
  istate& mouse = g_state->get_input();

  // Clarify if it's over our button and manip accordling
  if(is_over(mouse.x, mouse.y)) {
    if(mouse.buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
      b_clicked = true;

      while(SDL_GetMouseState(NULL, NULL)) { SDL_PumpEvents(); }
    }
    if(b_clicked) {
      o_texture = b_texts[2].get_textureptr();
      o_changed = true;
      o_manager->send_event(event(button_event(button_event::type::clicked, b_action)));
    } else {
      o_texture = b_texts[1].get_textureptr();
      o_changed = true;
      b_clicked = false;
    }
  } else {
    o_texture = b_texts[0].get_textureptr();
    o_changed = true;
    b_clicked = false;
  }
}


void button::handle_key  (state_ptr const& g_state) {
  // Obtain the current input state
  istate const& keyboard = g_state->get_input();

  // Clarify the current button status
  if(o_active) {
    o_texture = b_texts[1].get_textureptr();

    if(!b_clicked) {
      if(keyboard.keys[SDL_SCANCODE_RETURN]) {
        o_texture = b_texts[2].get_textureptr();
        o_manager->send_event(event(button_event(button_event::type::clicked, b_action)));
        b_clicked = true;
        return;
      }
    }
    b_clicked = false;
  } else {
    b_clicked = false;
    o_texture = b_texts[0].get_textureptr();
  }
}
