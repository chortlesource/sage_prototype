////////////////////////////////////////////////////////////////////////////
//
// sage - map.cpp
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
// MAP Class implementation
//

map::map(state_ptr const& g_state, unsigned int const& seed) : layer(g_state) {
  // Add the cursor to the map
  cursor = g_state->get_assets()->find_tile(16);
  cursor->set_position({32, 32, 0, 0});
  cursor->set_color({255, 255, 255, 255});

  int tile_w = g_state->get_input().tile_w;
  int tile_h = g_state->get_input().tile_h;
  int w      = g_state->get_input().width;
  int h      = g_state->get_input().height;

  width  = (w / tile_w) - 2;
  height = (h / tile_h) - 2;
  gen    = std::make_shared<worldgen>(g_state, width, height, seed);

  // Add our objects to the screen
  add(gen);
  add(cursor);
}


bool const& map::update(state_ptr const& g_state) {
  if(!initialized || o_paused) return o_changed;

  // Update the cursor position
  update_cursor(g_state);

  for(auto const& id : l_objectid)
    o_changed += l_objects[id]->update(g_state);

  if(o_changed)
    draw(g_state);

  return o_changed;
}


void map::update_cursor(state_ptr const& g_state) {
  int tile_w = g_state->get_assets()->find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets()->find_json("atlas")["TILE_H"].asInt();

  // Lambda function for convenience
  auto is_over = [&] (int const& x, int const& y) {
    return (x > (o_position.x + tile_w) && x < (o_position.x - tile_w) + o_position.w &&
      y > (o_position.y + tile_h) && y < (o_position.y - tile_h) + o_position.h);
  };

  // Obtain the current position of the mouse
  istate const& mouse = g_state->get_input();

  if(is_over(mouse.x, mouse.y) && mouse.x > 0 && mouse.y > 0) {
    int worldx = mouse.x / tile_w;
    int worldy = mouse.y / tile_h;
    cursor->set_position({ worldx * tile_w, worldy * tile_h, 0, 0});
    o_changed += 1;
  }

  if(SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE)
    SDL_ShowCursor(SDL_DISABLE);

}
