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
// LAYER Class implementation
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
  l_objectid.clear();
}


bool const& layer::update(state_ptr const& g_state) {
  if(!initialized || o_paused) return o_changed;

  for(auto const& id : l_objectid)
    o_changed += l_objects[id]->update(g_state);

  if(o_changed)
    draw(g_state);

  return o_changed;
}


void layer::add(object_ptr const& obj) {
  if((l_objects.try_emplace(obj->get_id(), obj)).second)
    INFO("Added object:", obj->get_id());
  else
    WARN("Object already loaded:", obj->get_id());

  l_objectid.push_back(obj->get_id());
  o_changed = true;
}


void layer::pop(object_ptr const& obj) {
  l_objects.erase(obj->get_id());

  for(auto itr = l_objectid.begin(); itr != l_objectid.end(); itr++) {
    if(*itr == obj->get_id())
      l_objectid.erase(itr);
  }

  o_changed = true;
}


void layer::draw(state_ptr const& g_state) {
  if(!initialized) return;

  SDL_Color bg_color   = g_state->get_assets().find_color("BLACK");
  SDL_Renderer *render = g_state->get_window().get_render();

  // First clear the texture
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, bg_color.r, bg_color.g, bg_color.b, 255);
  SDL_RenderClear(render);

  // Cycle through and draw objects to the layer
  for(auto const& id : l_objectid) {
    object_ptr &obj = l_objects[id];

    SDL_Color objc = obj->get_color();

    SDL_SetTextureColorMod(o_texture.get(), objc.r, objc.g, objc.b);
    SDL_RenderCopy(render, obj->get_texture(), &obj->get_source(), &obj->get_position());
  }

  SDL_SetRenderTarget(render, NULL);
  o_changed = false;
}
