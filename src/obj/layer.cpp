////////////////////////////////////////////////////////////////////////////
//
// sage - layer.cpp
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
// LAYER implementation
//

layer::layer(state_ptr const& g_state) : object(g_state) {
  // Firstly configure the layer position
  int w = g_state->get_config()["APP_W"].asInt();
  int h = g_state->get_config()["APP_H"].asInt();
  o_position = SDL_Rect { 0, 0, w, h };

  // Create a texture for the layer
  sdltexture_ptr texture(SDL_CreateTexture(g_state->get_window().get_render(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
  o_position.w, o_position.h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });

  o_texture   = texture;
  initialized = true;
}


layer::~layer() {
  l_objects.clear();
}


bool const& layer::update(state_ptr const& g_state) {
  if(!initialized || o_paused) return o_changed;

  for(auto &obj : l_objects)
    o_changed += obj->update(g_state);

  if(o_changed)
    draw(g_state);

  return o_changed;
}


void layer::add(object_ptr const& obj) {
  l_objects.push_back(obj);
  o_changed = true;
}


void layer::pop() {
  l_objects.pop_back();
  o_changed = true;
}


void layer::draw(state_ptr const& g_state) {
  if(!initialized) return;

  SDL_Renderer *render = g_state->get_window().get_render();

  // First clear the texture
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
  SDL_RenderClear(render);

  // Cycle through and draw objects to the layer
  for(auto &obj : l_objects)
    SDL_RenderCopy(render, obj->get_texture(), &obj->get_source(), &obj->get_position());

  SDL_SetRenderTarget(render, NULL);
  o_changed = false;
}
