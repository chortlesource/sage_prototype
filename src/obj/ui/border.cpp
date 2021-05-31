////////////////////////////////////////////////////////////////////////////
//
// sage - border.cpp
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
// BORDER Class implementation
//

border::border(state_ptr const& g_state, std::string const& colorid) : object(g_state) {
  // Calculate border dimensions
  int tile_w = g_state->get_assets().find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets().find_json("atlas")["TILE_H"].asInt();
  int scrnw  = g_state->get_config()["APP_W"].asInt();
  int scrnh  = g_state->get_config()["APP_H"].asInt();

  // Configure basic details about the object
  o_source   = { 0, 0, scrnw, scrnh };
  o_position = { 0, 0, scrnw, scrnh };
  o_color    = { 255, 255, 255, 255 };

  int max_w  = o_position.w / tile_w;
  int max_h  = o_position.h / tile_h;

  SDL_Renderer *render = g_state->get_window().get_render();

  // Create our border texture
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    o_source.w, o_source.h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Clear our texture to make transparent
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, 0,0,0,0);
  SDL_RenderClear(render);

  object_ptr t     = g_state->get_assets().find_tile(13);
  SDL_Color tcolor = g_state->get_assets().find_color(colorid);
  SDL_SetTextureColorMod(t->get_texture(), tcolor.r, tcolor.g, tcolor.b);

  for(int x = 0; x < max_w; x++) {
    for(int y = 0; y < max_h; y++) {
      if(y == 0 || y == max_h - 1 || x == 0 || x == max_w - 1) {
        SDL_Rect pos { x * tile_w, y * tile_w, tile_w, tile_h };
        SDL_RenderCopy(render, t->get_texture(), &t->get_source(), &pos);
      }
    }
  }

  SDL_SetRenderTarget(render, NULL);
  initialized = true;
}
