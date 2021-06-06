////////////////////////////////////////////////////////////////////////////
//
// sage - overlay.cpp
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
// OVERLAY Class implementation
//

overlay::overlay(state_ptr const& g_state, std::string const& colorid, int const& alpha) : object(g_state) {
  // Configure basic details about the object
  int scrnw  = g_state->get_config()["APP_W"].asInt();
  int scrnh  = g_state->get_config()["APP_H"].asInt();
  o_source   = { 0, 0, scrnw, scrnh };
  o_position = { 0, 0, scrnw, scrnh };

  SDL_Renderer *render = g_state->get_window()->get_render();

  // Create our border texture
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    o_source.w, o_source.h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Clear our texture to make transparent
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_Color color = g_state->get_assets()->find_color(colorid);
  SDL_SetRenderDrawColor(render, color.r, color.g, color.b, alpha);
  SDL_RenderClear(render);

  SDL_SetRenderTarget(render, NULL);
  initialized = true;
}
