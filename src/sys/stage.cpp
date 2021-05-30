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

stage::stage() : initialized(false), s_menu_depth(0), s_position(), s_layers(), s_menus() {}


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
    for(auto &l : s_layers)
      l->update(g_state);

    // Draw our layers to the window
    for(auto &l : s_layers) {
      if(l->get_visible())
        SDL_RenderCopy(g_state->get_window().get_render(), l->get_texture(), NULL, &s_position);
    }
  }
}


void stage::add(layer_ptr const& layer) {
  // Add new layers to the back of the vector
  s_layers.push_back(layer);
}


void stage::pop() {
  // Pop from the back of the layer vector
  s_layers.pop_back();
}


void stage::clear() {
  // Clear the layer stack
  s_layers.clear();
}


void stage::add_menu(std::string const& id, layer_ptr const& menu) {
  // Add it to the menu map
  if((s_menus.try_emplace(id, menu)).second)
    INFO("Menu added:", id);
  else
    WARN("Duplicate menu: ", id);
}


void stage::use_menu(std::string const& id) {
  // First pause all the layers
  for(auto &layers : s_layers)
    layers->set_paused(true);

  try {
    // Try to add out menu to the layer vector
    s_layers.push_back(s_menus.at(id));
    s_menu_depth += 1; // to track how many menu's are present

  } catch (std::out_of_range const& oor) {
    ERROR("Menu not found: ", id);

    // Unpause to avoid hanging
    for(auto &layers : s_layers)
      layers->set_paused(false);
  }
}


void stage::pop_menu() {
  if(s_menu_depth == 0) return;

  // Pop our menu from the back
  s_layers.pop_back();
  s_menu_depth -= 1;

  // Clarify if there are no more menu's
  if(s_menu_depth == 0) {
    for(auto &layers : s_layers)
      layers->set_paused(false);
  } else {
    s_layers.back()->set_paused(false);
  }
}
