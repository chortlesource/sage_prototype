////////////////////////////////////////////////////////////////////////////
//
// sage - worldgen.cpp
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
// WORLDGEN Class implementation
//

worldgen::worldgen(state_ptr const& g_state, int const& width, int const& height) : object(g_state) {
  // Generate the biome and temperature map
  generate_noise_map(width, height);

  // Populate the map based on noise and elevation
  generate_world_map(width, height);

  // Generate the map texture
  int tile_w = g_state->get_assets().find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets().find_json("atlas")["TILE_H"].asInt();
  generate_world_txt(g_state, width, height, tile_w, tile_h);

  o_source   = { 0, 0, width * tile_w, height * tile_h };
  o_position = { tile_w, tile_h, o_source.w, o_source.h };
}


void worldgen::generate_world_map(int const& width, int const& height) {
  int size = width * height;
  w_map.resize(size);

  for(int i = 0; i < size; i++) {
    if (w_elev[i] < 0.12) w_map[i] = biome::water;
     else if (w_elev[i] < 0.22) w_map[i] = biome::sand;
     else if (w_elev[i] < 0.5) w_map[i] = biome::grass;
     else if (w_elev[i] < 0.6) w_map[i] = biome::forrest;
     else if (w_elev[i] < 0.7) w_map[i] = biome::dirt;
     else if (w_elev[i] < 0.8) w_map[i] = biome::swamp;
     else if (w_elev[i] < 0.9) w_map[i] = biome::mountain;
     else if (w_elev[i] == 1.0) w_map[i] = biome::snow;
   }
}


void worldgen::generate_noise_map(int const& width, int const& height) {
  // Create and resize the elevation and temperature map to fit our world dimensions
  w_elev.resize(width * height + 1);
  w_temp.resize(width * height + 1);

  // Initialize the perlin noise generator
  perlin noise(std::default_random_engine::default_seed);

  // Generate the noisemaps
  double nx = 1.0 / width;
  double ny = 1.0 / height;
  int   res = 3;

  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      double elev = noise.octave_noise_0_1(x * nx * res, y * ny * res, 0.1, 20);
      double temp = noise.octave_noise_0_1(x * nx * res, y * ny * res, 1, 3);

      w_elev[y * width + x] = elev;
      w_temp[y * width + x] = temp;
    }
  }
}


void worldgen::generate_world_txt(state_ptr const& g_state, int const& width, int const& height, int const& tile_w, int const& tile_h) {
  // Create our world texture
  SDL_Renderer *render = g_state->get_window().get_render();
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    width * tile_w, height * tile_h), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Clear our texture to make transparent
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_SetRenderDrawColor(render, 0,0,0,0);
  SDL_RenderClear(render);

  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      SDL_Color  color { 255, 255, 255, 255 };
      SDL_Rect   pos   { x * tile_w, y * tile_h, tile_w, tile_h };
      object_ptr t = g_state->get_assets().find_tile(16);

      switch(w_map[y * width + x]) {
        case biome::water:
          t     = g_state->get_assets().find_tile(11);
          color = g_state->get_assets().find_color("BLUE");
          break;
        case biome::sand:
          t     = g_state->get_assets().find_tile(16);
          color = g_state->get_assets().find_color("YELLOW");
          break;
        case biome::grass:
          t     = g_state->get_assets().find_tile(16);
          color = g_state->get_assets().find_color("GREEN");
          break;
        case biome::forrest:
          t     = g_state->get_assets().find_tile(5);
          color = g_state->get_assets().find_color("GREEN");
          break;
        case biome::dirt:
          t     = g_state->get_assets().find_tile(21);
          color = g_state->get_assets().find_color("BROWN");
          break;
        case biome::swamp:
          t     = g_state->get_assets().find_tile(21);
          color = g_state->get_assets().find_color("GREEN");
          break;
        case biome::mountain:
          t     = g_state->get_assets().find_tile(6);
          color = g_state->get_assets().find_color("D_GRAY");
          break;
        default:
          break;
      }

      SDL_SetTextureColorMod(t->get_texture(), color.r, color.g, color.b);
      SDL_RenderCopy(render, t->get_texture(), &t->get_source(), &pos);
    }
  }

  SDL_SetRenderTarget(render, NULL);
  INFO("DONE");
  initialized = true;
}
