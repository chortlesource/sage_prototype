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

#include <sage.hpp>


/////////////////////////////////////////////////////////////
// ASSETS Class implementation
//

static inline bool fexist(std::string const& path) {
  // Identify if file exists and return true if exists
  return (std::filesystem::exists(std::filesystem::path(path))
    && std::filesystem::is_regular_file(std::filesystem::path(path)));
}


assets::assets() {
  // Create empty instances to return where a valid id is not found
  Json::Value empty_json = Json::Value::null;
  jsons.insert({"EMPTY", empty_json});

  sdltexture_ptr empty_texture = nullptr;
  textures.insert({"EMPTY", empty_texture});

  font_ptr empty_font = nullptr;
  fonts.insert({"EMPTY", empty_font});

  SDL_Color empty_color { 255, 255, 255, 255 };
  colors.insert({"EMPTY", empty_color});

  tile_ptr empty_tile = nullptr;
  tiles.insert({0, empty_tile});
}


assets::~assets() {
  jsons.clear();
  textures.clear();
  fonts.clear();
  colors.clear();
  tiles.clear();
}


Json::Value const&    assets::load_json(std::string const& id, std::string const& path) {
  // Verify the file exists
  if(!fexist(path)) {
    ERROR("Cannot find json file at: ", path);
    return jsons.at("EMPTY");
  }

  // Load our Json File
  Json::Value value;
  std::ifstream input(path, std::ifstream::binary);
  if(input.is_open()) {
    // Get our json file
    input >> value;
    input.close();

    // Add it to the json map
    if((jsons.try_emplace(id, value)).second)
      INFO("Json file loaded:", id);
    else
      WARN("Json file already loaded: ", id);

    // Return our json file
    return jsons.at(id);
  }

  ERROR("Cannot load json file: ", path);
  return jsons.at("EMPTY");
}


Json::Value const&    assets::find_json(std::string const& id) {
  // Try to access the json and handle the exception
  try {
    return jsons.at(id);
  } catch (std::out_of_range const& oor) {
    ERROR("Json not loaded: ", id);
  }

  return jsons.at("EMPTY");
}


sdltexture_ptr const& assets::load_texture(SDL_Renderer *render, std::string const& id, std::string const& path) {
  // Verify the file exists
  if(!fexist(path)) {
    ERROR("Cannot find texture file at: ", path);
    return textures.at("EMPTY");
  }

  // Load our texture
  sdltexture_ptr texture(IMG_LoadTexture(render, path.c_str()),
    [=](SDL_Texture *t) { SDL_DestroyTexture(t); });

  if(texture != nullptr) {
    // Add it to the texture map
    if((textures.try_emplace(id, texture)).second)
      INFO("Texture file loaded:", id);
    else
      WARN("Texture file already loaded: ", id);

    // Return our json file
    return textures.at(id);
  }

  ERROR("Cannot load Texture file: ", path, IMG_GetError());
  return textures.at("EMPTY");
}


sdltexture_ptr const& assets::find_texture(std::string const& id) {
  // Try to access the texture and handle the exception
  try {
    return textures.at(id);
  } catch (std::out_of_range const& oor) {
    ERROR("Texture not loaded: ", id);
  }

  return textures.at("EMPTY");
}


void             assets::load_fonts(Json::Value const& g_config) {
  std::string  src  = g_config["SRC"].asString();
  unsigned int size = g_config["NFONT"].asUInt();

  // Verify the file exists
  if(!fexist(src)) {
    ERROR("Cannot find font file at: ", src);
    return;
  }

  // iterate through each size to be loaded
  for(unsigned int n = 0; n < size; n++) {
    // Establish the font id
    std::string id = g_config["SIZE"][std::to_string(n)]["NAME"].asString();
    int fsize      = g_config["SIZE"][std::to_string(n)]["SIZE"].asInt();

    // Attempt to load the font size
    font_ptr font(TTF_OpenFont(src.c_str(), fsize), [=](TTF_Font *f) { TTF_CloseFont(f); });

    if(font != nullptr) {
      // Add it to the font map
      if((fonts.try_emplace(id, font)).second)
        INFO("Font file loaded:", src, "[", id, "]");
      else
        WARN("Font file already loaded: ", src, "[", id, "]");
    } else {
      ERROR("Cannot load font file: ", src, "[", id, "]", TTF_GetError());
      return;
    }
  }

  INFO("Fonts loaded [COMPLETE]");
}


font_ptr const&  assets::find_font(std::string const& id) {
  // Try to access the texture and handle the exception
  try {
    return fonts.at(id);
  } catch (std::out_of_range const& oor) {
    ERROR("Font not loaded: ", id);
  }

  return fonts.at("EMPTY");
}


void             assets::load_colors(Json::Value const& config) {
  unsigned int num = config["NCOLOR"].asUInt();

  // iterate through each size to be loaded
  for(unsigned int n = 0; n < num; n++) {
    // Pull out the vars from the json
    uint8_t r = config["COLORS"][std::to_string(n)]["R"].asUInt() & 0xFF;
    uint8_t g = config["COLORS"][std::to_string(n)]["G"].asUInt() & 0xFF;
    uint8_t b = config["COLORS"][std::to_string(n)]["B"].asUInt() & 0xFF;

    // Initialize the id and color
    std::string id = config["COLORS"][std::to_string(n)]["NAME"].asString();
    SDL_Color color { r, g, b, 255 };

    // Add it to the font map
    if((colors.try_emplace(id, color)).second)
      INFO("Color loaded:", id);
    else
      WARN("Color already loaded: ", id);
  }

  INFO("Colors loaded [COMPLETE]");
}


SDL_Color const& assets::find_color(std::string const& id) {
  // Try to access the color and handle the exception
  try {
    return colors.at(id);
  } catch (std::out_of_range const& oor) {
    ERROR("Color not loaded: ", id);
  }

  return colors.at("EMPTY");
}


void             assets::load_tiles(state_ptr const& g_state, Json::Value const& t_config) {
  sdltexture_ptr texture = load_texture(g_state->get_window().get_render(), "atlas", t_config["ATLAS"].asString());

  int tile_w = t_config["TILE_W"].asInt();
  int tile_h = t_config["TILE_H"].asInt();
  int ntiles = t_config["TILEN"].asInt();

  for(int n = 1; n < ntiles; n++) {
    std::string index   = std::to_string(n);

    std::string colorid = t_config["TILES"][index]["COLOR"].asString();
    int tile_x          = t_config["TILES"][index]["X"].asInt();
    int tile_y          = t_config["TILES"][index]["Y"].asInt();

    SDL_Rect  src { tile_x * tile_w, tile_y * tile_h, tile_w, tile_h };

    // Add it to the font map
    tile_ptr t = std::make_shared<tile>(g_state, texture, src, colorid);
    if((tiles.try_emplace(n, t).second))
      INFO("Tile loaded:", n);
    else
      WARN("Tile already loaded: ", n);
  }
  INFO("Tiles Loaded [COMPLETE]");
}


tile_ptr  const& assets::find_tile(int const& id) {
  // Try to access the tile and handle the exception
  try {
    return tiles.at(id);
  } catch (std::out_of_range const& oor) {
    ERROR("Tile not loaded: ", id);
  }

  return tiles.at(0);
}
