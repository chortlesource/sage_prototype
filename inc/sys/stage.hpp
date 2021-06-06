////////////////////////////////////////////////////////////////////////////
//
// sage - stage.hpp
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

#ifndef _SAGE_STAGE_HPP
#define _SAGE_STAGE_HPP


/////////////////////////////////////////////////////////////
// STAGE Class
//
// The stage class renders layers of objects to the window

class stage {
public:
  stage();
  ~stage();

  void initialize(Json::Value const& g_config);
  void update(state_ptr const& g_state);
  void finalize(state_ptr const& g_state);

  void add(layer_ptr const& layer);
  void pop();
  void clear(state_ptr const& g_state);

  void add_menu(std::string const& id, layer_ptr const& menu);
  void use_menu(std::string const& id);
  void pop_menu();

private:
  bool                                        initialized;
  unsigned int                                s_menu_depth;
  SDL_Rect                                    s_position;
  std::vector<layer_ptr>                      s_layers;
  std::vector<std::string>                    s_menuid;
  std::unordered_map<std::string, layer_ptr>  s_menus;
};


#endif // _SAGE_STAGE_HPP
