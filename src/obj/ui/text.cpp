////////////////////////////////////////////////////////////////////////////
//
// sage - text.cpp
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
// TEXT Class implementation
//

text::text(state_ptr const& g_state, std::string const& caption, std::string const& fontid, std::string const& colorid) : object(g_state) {
  t_text = caption;

  // Some helper vars to generate the button
  SDL_Renderer *render = g_state->get_window()->get_render();
  TTF_Font     *font   = g_state->get_assets()->find_font(fontid).get();
  o_color              = g_state->get_assets()->find_color(colorid);


  // Create a surface for the text
  SDL_Surface *surf = TTF_RenderText_Solid(font, t_text.c_str(), o_color);

  if(surf == nullptr) {
    ERROR("Could not generate text surface: ", t_text);
    return;
  }

  // Create a texture from the surface
  sdltexture_ptr texture(SDL_CreateTextureFromSurface(render, surf), [=](SDL_Texture *t) { SDL_DestroyTexture(t); });

  if(texture == nullptr) {
    ERROR("Could not generate text textures: ", t_text);
    return;
  }

  // Configure the object variables
  o_source       = { 0, 0, surf->w, surf->h };
  o_position     = { 0, 0, surf->w, surf->h };
  o_texture      = texture;

  // Free the surface as it's no longer required
  SDL_FreeSurface(surf);
  initialized = true;
}


text::~text() {
  initialized = false;

  o_texture   = nullptr;
  t_text.clear();
}
