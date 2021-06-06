////////////////////////////////////////////////////////////////////////////
//
// sage - glyph.hpp
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
// GLYPH Class implementation
//

glyph::glyph(state_ptr const& g_state, std::string const& fontid, char const& ch) : object(g_state) {
  // Obtain some essential variables
  SDL_Renderer *render = g_state->get_window()->get_render();
  int tile_w = g_state->get_assets()->find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets()->find_json("atlas")["TILE_H"].asInt();

  // Configure our glyph object
  o_source   = { 0, 0, tile_w, tile_h };
  o_position = { 0, 0, tile_w, tile_h };
  o_color    = { 255, 255, 255, 255 };

  // Generate the text and caculate it's position in the tile
  text t(g_state, std::string(1, ch), fontid, "DEFAULT");
  SDL_Rect source = t.get_source();
  SDL_Rect newpos = { (o_position.w / 2) - (source.w / 2), (o_position.h / 2) - (source.h / 2) - 1, source.w, source.h };

  // Create our tile texture
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    tile_w, tile_h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Copy accross our glyph
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, 0,0,0,0);
  SDL_RenderClear(render);
  SDL_RenderCopy(render, t.get_texture(), &source, &newpos);
  SDL_SetRenderTarget(render, NULL);

  initialized = true;
}
