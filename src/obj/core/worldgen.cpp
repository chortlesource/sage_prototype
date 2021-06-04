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

worldgen::worldgen(int const& width, int const& height) {
  // Generate the biome and temperature map
  generate_noise_map(width, height);

  // Populate the map based on noise and elevation
  generate_world_map(width, height);

  // Print the map to take a look
  print_world_map(width, height);
}


void worldgen::generate_world_map(int const& width, int const& height) {
  int size = width * height;
  w_map.resize(size);

  for(int i = 0; i < size; i++) {
    if(w_elev[i] < 0.05f) w_map[i] = biome::water;
    if(w_elev[i] < 0.12f) w_map[i] = biome::sand;

    if(w_elev[i] > 0.7f) {
      if(w_temp[i] < 0.4)
        w_map[i] = biome::mountain;
      else
        w_map[i] = biome::grass;
      continue;
    }

    if(w_elev[i] < 0.5f) {
      if(w_temp[i] < 0.1) w_map[i] = biome::sand;
      if(w_temp[i] < 0.3) w_map[i] = biome::grass;
      if(w_temp[i] < 0.7) w_map[i] = biome::forrest;
      continue;
    }

    if(w_elev[i] < 0.27f) {
      if(w_temp[i] < 0.1) w_map[i] = biome::sand;
      if(w_temp[i] < 0.3) w_map[i] = biome::dirt;
      if(w_temp[i] < 0.7) w_map[i] = biome::forrest;
      continue;
    }
  }
}


void worldgen::print_world_map(int const& width, int const& height) {
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      std::cout << w_map[y * width + x];
    }
    std::cout << std::endl;
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
  int   res = 5;

  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      double elev = noise.octave_noise_0_1(x * nx * res, y * ny * res, 0.1, 20);
      double temp = noise.octave_noise_0_1(x * nx * res, y * ny * res, 1, 3);

      w_elev[y * width + x] = elev;
      w_temp[y * width + x] = temp;
    }
  }
}
