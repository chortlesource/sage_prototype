////////////////////////////////////////////////////////////////////////////
//
// sage - statbar.cpp
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
// STATBAR Class implementation
//

statbar::statbar(state_ptr const& g_state) : object(g_state) {
  // Obtain some essential variables
  SDL_Renderer *render = g_state->get_window().get_render();
  int tile_w = g_state->get_assets().find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets().find_json("atlas")["TILE_H"].asInt();

  glyph_ptr  slash = g_state->get_assets().find_glyph("/");
  glyph_ptr  hash  = g_state->get_assets().find_glyph("#");
  glyph_ptr  colon = g_state->get_assets().find_glyph(":");
  glyph_ptr  zero  = g_state->get_assets().find_glyph("0");
  object_ptr dolla = g_state->get_assets().find_tile(21);
  object_ptr heart = g_state->get_assets().find_tile(22);

  SDL_Color def = g_state->get_assets().find_color("DEFAULT");
  SDL_Color red = g_state->get_assets().find_color("RED");
  SDL_Color yel = g_state->get_assets().find_color("YELLOW");
  SDL_Color cyn = g_state->get_assets().find_color("CYAN");

  // Configure basic details about the object
  o_source   = { 0, 0, tile_w * 9, tile_h };
  o_position = { 0, 0, tile_w * 9, tile_h };

  // Create our sidebar texture
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    o_source.w, o_source.h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Configure the background of the gtext
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_Color bg = g_state->get_assets().find_color("BLACK");
  SDL_SetRenderDrawColor(render, bg.r, bg.g, bg.b, 255);
  SDL_RenderClear(render);

  // DO STUFF HERE
  SDL_Rect pos { 0, 0, tile_w, tile_h };

  SDL_SetTextureColorMod(colon->get_texture(), def.r, def.g, def.b);
  SDL_RenderCopy(render, colon->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(hash->get_texture(), cyn.r, cyn.g, cyn.b);
  SDL_RenderCopy(render, hash->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(zero->get_texture(), cyn.r, cyn.g, cyn.b);
  SDL_RenderCopy(render, zero->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(slash->get_texture(), def.r, def.g, def.b);
  SDL_RenderCopy(render, slash->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(dolla->get_texture(), yel.r, yel.g, yel.b);
  SDL_RenderCopy(render, dolla->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(zero->get_texture(), yel.r, yel.g, yel.b);
  SDL_RenderCopy(render, zero->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(slash->get_texture(), def.r, def.g, def.b);
  SDL_RenderCopy(render, slash->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(heart->get_texture(), red.r, red.g, red.b);
  SDL_RenderCopy(render, heart->get_texture(), NULL, &pos);
  pos.x += tile_w;

  SDL_SetTextureColorMod(zero->get_texture(), red.r, red.g, red.b);
  SDL_RenderCopy(render, zero->get_texture(), NULL, &pos);

  SDL_SetRenderTarget(render, NULL);
  initialized = true;
}
