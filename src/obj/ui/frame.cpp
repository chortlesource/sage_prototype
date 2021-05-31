////////////////////////////////////////////////////////////////////////////
//
// sage - frame.cpp
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
// FRAME Class implementation
//

frame::frame(state_ptr const& g_state) : layer(g_state) {

  // Calculate tile dimensions
  int tile_w = g_state->get_assets().find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets().find_json("atlas")["TILE_H"].asInt();

  int max_w  = o_position.w / tile_w;
  int max_h  = o_position.h / tile_h;

  SDL_Renderer *render = g_state->get_window().get_render();

  // Draw frame buffer
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, 0,0,0,0);
  SDL_RenderClear(render);

  tile_ptr t       = g_state->get_assets().find_tile(13);
  SDL_Color tcolor = g_state->get_assets().find_color("L_GRAY");
  SDL_SetTextureColorMod(t->get_texture(), tcolor.r, tcolor.g, tcolor.b);

  for(int x = 0; x < max_w; x++) {
    for(int y = 0; y < max_h; y++) {
      if(y == 0 || y == max_h - 1 || x == 0 || x == max_w - 1) {
        SDL_Rect pos { x * tile_w, y * tile_w, tile_w, tile_h };
        SDL_RenderCopy(render, t->get_texture(), &t->get_source(), &pos);
      }
    }
  }

  object_ptr title = std::make_shared<gtext>(g_state, " sage ", "BLUE", "BLACK");
  object_ptr versn = std::make_shared<gtext>(g_state, _APP_VERSION, "RED", "BLACK");
  title->set_position({(o_position.w / 2) - (title->get_position().w / 2), 0, 0, 0 });
  versn->set_position({ tile_w * 2, o_position.h - tile_h, 0, 0 });
  add(title);
  add(versn);
  //SDL_RenderCopy(render, title->get_texture(), NULL, &title->get_position());

  SDL_SetRenderTarget(render, NULL);
}
