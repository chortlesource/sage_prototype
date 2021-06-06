////////////////////////////////////////////////////////////////////////////
//
// sage - worldgen.hpp
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

#ifndef _SAGE_WORLDGEN_HPP
#define _SAGE_WORLDGEN_HPP


/////////////////////////////////////////////////////////////
// WORLDGEN Class
//
// The worldgen class generates a tilemap based on perlin noise

class worldgen : public object {
public:
  enum class biome { water, sand, grass, forrest, dirt, swamp, mountain, snow };

  worldgen(state_ptr const& g_state, int const& width, int const& height, unsigned int const& seed);

private:
  std::vector<double> w_elev;
  std::vector<double> w_temp;
  std::vector<biome>  w_map;
  sdltexture_ptr      w_texture;
  unsigned int        w_seed;

  void generate_noise_map(int const& width, int const& height);
  void generate_world_map(int const& width, int const& height);
  void generate_world_txt(state_ptr const& g_state, int const& width, int const& height, int const& tile_w, int const& tile_h);
};


#endif // _SAGE_WORLDGEN_HPP
