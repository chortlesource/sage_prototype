////////////////////////////////////////////////////////////////////////////
//
// sage - stage.cpp
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
// STAGE Class implementation
//

stage::stage() : initialized(false), s_menuirq(false), s_position(), s_layers(), s_menus() {}


stage::~stage() {
  initialized = false;

  s_layers.clear();
  s_menus.clear();
}


void stage::initialize(Json::Value const& g_config) {
  // Use window dimensions for rendering layers
  int w = g_config["APP_W"].asInt();
  int h = g_config["APP_H"].asInt();
  s_position  = SDL_Rect { 0, 0, w, h };

  initialized = true;
}


void stage::update(state_ptr const& g_state) {
  if(!initialized) return;

  if(!s_layers.empty()) {
    // Update our layers
    if(!s_menuirq)
      for(auto &l : s_layers)
        l->update(g_state);

    // Draw our layers to the window
    for(auto &l : s_layers) {
      if(l->get_visible())
        SDL_RenderCopy(g_state->get_window().get_render(), l->get_texture(), NULL, &s_position);
    }
  }

  // Update our menu's
  if(!s_menus.empty()) {
    for(auto &m : s_menus) {
      m->update(g_state);
      if(m->get_visible())
        SDL_RenderCopy(g_state->get_window().get_render(), m->get_texture(), NULL, &s_position);
    }
  }
}


void stage::add(layer_ptr const& layer) {
  s_layers.push_back(layer);

  // Ensure we pause the new layer if menus are active
  if(s_menuirq)
    s_layers[s_layers.size() - 1]->set_paused(true);
}


void stage::pop() {
  // Pop from the back of the layer stack
  s_layers.pop_back();
}


void stage::add_menu(layer_ptr const& menu) {
  if(!s_menuirq) {
    // If irq is not set then set it
    for(auto &l : s_layers)
      l->set_paused(true);

    s_menuirq = true;
  } else {
    // Pause menu's currently in use
    s_menus.back()->set_paused(true);
  }

  // Add our menu
  s_menus.push_back(menu);
}


void stage::pop_menu() {
  // Pop from the back of the menu stack
  s_menus.pop_back();

  if(s_menuirq) {
    if(s_menus.empty())
      s_menuirq = false;
    else
      s_menus.back()->set_paused(false);
  }
}
