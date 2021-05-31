////////////////////////////////////////////////////////////////////////////
//
// sage - tile.cpp
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
// TILE Class implementation
//

tile::tile(state_ptr const& g_state, sdltexture_ptr const& texture, SDL_Rect const& src) : object(g_state) {
  // Configure object variables
  o_source   = SDL_Rect{ 0, 0, src.w, src.h };
  o_position = o_source;
  o_color    = { 255, 255, 255, 255 };

  SDL_Renderer *render = g_state->get_window().get_render();

  // Allocate memory for the tile texture
  sdltexture_ptr tmp_texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    o_source.w, o_source.h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });

  o_texture = tmp_texture;

  // Clear the current texture
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, 0,0,0,0);
  SDL_RenderClear(render);
  // Write the portion of the texture to the tile texture
  SDL_SetTextureColorMod(texture.get(), o_color.r, o_color.g, o_color.b);
  SDL_RenderCopy(render, texture.get(), &src, &o_position);
  SDL_SetRenderTarget(render, NULL);
  initialized = true;
}


tile::~tile() {
  initialized = false;
  o_texture   = nullptr;
}
