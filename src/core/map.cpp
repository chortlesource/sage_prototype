////////////////////////////////////////////////////////////////////////////
//
// sage - map.cpp
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


map::map(state_ptr const& g_state, int const& w, int const& h) : object(g_state) {
  // Initialize the map dimensions
  m_width    = w;
  m_height   = h;
  m_zoom     = 1;
  m_pressed  = false;

  // Fetch relevant configuration data
  int tile_w = g_state->get_assets().find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets().find_json("atlas")["TILE_H"].asInt();
  int scrnw  = g_state->get_config()["APP_W"].asInt();
  int scrnh  = g_state->get_config()["APP_H"].asInt();
  int map_w  = m_width * tile_w;
  int map_h  = m_height * tile_h;

  // Create a texture for the overlay and map
  SDL_Renderer *render = g_state->get_window().get_render();

  o_texture = sdltexture_ptr(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    scrnw, scrnh), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });

  m_overlay = sdltexture_ptr(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    map_w, map_h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  SDL_Rect opos { (scrnw / 2) - (map_w / 2), (scrnh / 2) - (map_h / 2), map_w + m_zoom, map_h + m_zoom };

  // Generate the overlay
  gen_overlay(g_state, tile_w, tile_h);

  // Configure object variables
  o_source   = SDL_Rect { 0, 0, scrnw, scrnh };
  o_position = SDL_Rect { 0, 0, scrnw, scrnh };
  o_color    = SDL_Color{ 255, 255, 255, 255 };

  // Generate our map image
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_Color bg_color = g_state->get_assets().find_color("BLACK");
  SDL_SetRenderDrawColor(render, bg_color.r, bg_color.g, bg_color.b, 255);
  SDL_RenderClear(render);
  SDL_RenderCopy(render, m_overlay.get(), NULL, &opos);
  SDL_SetRenderTarget(render, NULL);

  initialized = true;
}


map::~map() {
  initialized = false;
  m_overlay   = nullptr;
  m_maptxtr   = nullptr;
}


bool const& map::update(state_ptr const& g_state) {

  istate const& key = g_state->get_input();

  if(key.keys[SDL_SCANCODE_PERIOD]) {
    if(!m_pressed) {
      m_zoom   += 60;
      m_pressed = true;
      o_changed = true;
    }
  }
  else if(key.keys[SDL_SCANCODE_COMMA]) {
    if(!m_pressed) {
      m_zoom   -= 60;
      m_pressed = true;
      o_changed = true;
    }
  }
  else if(key.keys[SDL_SCANCODE_SLASH]) {
    if(!m_pressed) {
      m_zoom    = 0;
      m_pressed = true;
      o_changed = true;
    }
  } else {
    m_pressed = false;
    o_changed = false;
  }

  int tile_w = g_state->get_assets().find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets().find_json("atlas")["TILE_H"].asInt();
  int scrnw  = g_state->get_config()["APP_W"].asInt();
  int scrnh  = g_state->get_config()["APP_H"].asInt();
  int map_w  = m_width * tile_w;
  int map_h  = m_height * tile_h;

  SDL_Renderer *render = g_state->get_window().get_render();
  SDL_Rect opos { (scrnw / 2) - (map_w / 2), (scrnh / 2) - (map_h / 2), map_w + m_zoom, map_h + m_zoom };
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_Color bg_color = g_state->get_assets().find_color("BLACK");
  SDL_SetRenderDrawColor(render, bg_color.r, bg_color.g, bg_color.b, 255);
  SDL_RenderClear(render);
  SDL_RenderCopy(render, m_overlay.get(), NULL, &opos);
  SDL_SetRenderTarget(render, NULL);

  return o_changed;
}


void map::gen_overlay(state_ptr const& g_state, int const& tile_w, int const& tile_h) {
  SDL_Renderer *render = g_state->get_window().get_render();

  // Generate the overlay
  SDL_SetRenderTarget(render, m_overlay.get());
  SDL_Color bg_color = g_state->get_assets().find_color("BLACK");
  SDL_SetRenderDrawColor(render, bg_color.r, bg_color.g, bg_color.b, 0);
  SDL_RenderClear(render);

  tile_ptr t       = g_state->get_assets().find_tile(11);
  SDL_Color tcolor = g_state->get_assets().find_color("D_GRAY");
  SDL_SetTextureColorMod(t->get_texture(), tcolor.r, tcolor.g, tcolor.b);

  for(int x = 0; x < m_width; x++) {
    for(int y = 0; y < m_height; y++) {
      SDL_Rect pos { x * tile_w, y * tile_w, tile_w, tile_h };
      SDL_RenderCopy(render, t->get_texture(), &t->get_source(), &pos);
    }
  }

  SDL_SetTextureColorMod(t->get_texture(), 255, 255, 255);
  SDL_SetTextureBlendMode(m_overlay.get(), SDL_BLENDMODE_BLEND);
  SDL_SetTextureAlphaMod(m_overlay.get(), 70);
  SDL_SetRenderTarget(render, NULL);
}


void map::gen_maptxtr(state_ptr const& g_state, int const& tile_w, int const& tile_h) {

}
