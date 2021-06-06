////////////////////////////////////////////////////////////////////////////
//
// sage - enemy.cpp
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
// ENEMY Class implementation
//

enemy::enemy(state_ptr const& g_state) : object(g_state) {
  SDL_Renderer *render = g_state->get_window()->get_render();
  object_ptr t         = g_state->get_assets()->find_tile(2);

  // Configure basic details about the object
  o_source   = { 0, 0, t->get_source().w, t->get_source().h };
  o_position = o_source;

  // Create our enemy texture
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    o_source.w, o_source.h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Clear our texture to make transparent
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, 0,0,0,0);
  SDL_RenderClear(render);

  SDL_SetTextureColorMod(t->get_texture(), o_color.r, o_color.g, o_color.b);
  SDL_RenderCopy(render, t->get_texture(), &t->get_source(), &o_position);
  SDL_SetRenderTarget(render, NULL);
  initialized = true;
}
