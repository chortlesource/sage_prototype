////////////////////////////////////////////////////////////////////////////
//
// sage - assets.hpp
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

#ifndef _SAGE_ASSETS_HPP
#define _SAGE_ASSETS_HPP


/////////////////////////////////////////////////////////////
// ASSETS Class
//
// The assets class loads and stores game assets

class assets {
public:
  assets();
  ~assets();

  Json::Value const&    load_json(std::string const& id, std::string const& path);
  Json::Value const&    find_json(std::string const& id);

  sdltexture_ptr const& load_texture(SDL_Renderer *render, std::string const& id, std::string const& path);
  sdltexture_ptr const& find_texture(std::string const& id);

  void             load_fonts(Json::Value const& f_config);
  font_ptr  const& find_font(std::string const& id);

  void             load_colors(Json::Value const& c_config);
  SDL_Color const& find_color(std::string const& id);

  void             load_tiles(state_ptr const& g_state, Json::Value const& t_config);
  tile_ptr  const& find_tile(int const& id);

private:
  std::unordered_map<std::string, Json::Value>    jsons;
  std::unordered_map<std::string, sdltexture_ptr> textures;
  std::unordered_map<std::string, font_ptr>       fonts;
  std::unordered_map<std::string, SDL_Color>      colors;
  std::unordered_map<int, tile_ptr>               tiles;
};


#endif // SAGE_ASSETS_HPP
