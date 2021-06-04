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

class worldgen {
public:
  enum biome { water = 0, sand, dirt, grass, forrest, mountain };

  worldgen() {};
  worldgen(int const& width, int const& height);

  std::vector<int> const& get_map() { return w_map; }

private:
  std::vector<double> w_elev;
  std::vector<double> w_temp;
  std::vector<int>    w_map;

  void generate_noise_map(int const& width, int const& height);
  void generate_world_map(int const& width, int const& height);
  void print_world_map   (int const& width, int const& height);
};

#endif // _SAGE_WORLDGEN_HPP
