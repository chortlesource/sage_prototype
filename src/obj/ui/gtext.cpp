////////////////////////////////////////////////////////////////////////////
//
// sage - gtext.cpp
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
// GTEXT Class implementation
//

gtext::gtext(state_ptr const& g_state, std::string const& caption, std::string const& fgcolor, std::string const& bgcolor) : object(g_state) {
  // Obtain some essential variables
  SDL_Renderer *render = g_state->get_window().get_render();
  int tile_w = g_state->get_assets().find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets().find_json("atlas")["TILE_H"].asInt();

  // Configure our gtext object
  o_source   = { 0, 0, tile_w * (int)caption.size(), tile_h };
  o_position = { 0, 0, tile_w * (int)caption.size(), tile_h };
  o_color    = { 255, 255, 255, 255 };

  // Create our gtext texture
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    o_source.w, o_source.h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Configure the background of the gtext
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());

  if(bgcolor == "NONE") {
    SDL_SetRenderDrawColor(render, 0,0,0,0);
  } else {
    SDL_Color bg = g_state->get_assets().find_color(bgcolor);
    SDL_SetRenderDrawColor(render, bg.r, bg.g, bg.b, 255);
  }
  SDL_RenderClear(render);

  // Draw our glyphs onto the texture
  SDL_Color fg = g_state->get_assets().find_color(fgcolor);

  for(int i = 0; i < (int)caption.size(); i++) {
    glyph_ptr g = g_state->get_assets().find_glyph(caption.substr(i, 1));
    SDL_Rect pos { i * tile_w, 0, tile_w, tile_h };

    if(caption.substr(i, 1) == ".")
      pos { }
    SDL_SetTextureColorMod(g->get_texture(), fg.r, fg.g, fg.b);
    SDL_RenderCopy(render, g->get_texture(), &g->get_source(), &pos);
  }

  SDL_SetRenderTarget(render, NULL);
  initialized = true;
}

std::array<std::string, 4> punctuation { ",", ".", ":", ";" };
