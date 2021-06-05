////////////////////////////////////////////////////////////////////////////
//
// sage - forwards.hpp
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

#ifndef _SAGE_FORWARDS_HPP
#define _SAGE_FORWARDS_HPP


/////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
//

// Utility Classes
class timer;

// Object Primatives
class object;
class tile;
class glyph;
class layer;

// UI Objects
class text;
class gtext;
class button;
class border;
class statbar;
class menu;
class frame;

// Core Objects
class map;
class enemy;
class worldgen;

// System Classes
class manager;
class assets;
class stage;
class window;
class game;
class state;
class engine;


/////////////////////////////////////////////////////////////
// SMART POINTERS
//

// System Smart Pointers
using state_ptr      = std::shared_ptr<state>;
using object_ptr     = std::shared_ptr<object>;
using glyph_ptr      = std::shared_ptr<glyph>;
using layer_ptr      = std::shared_ptr<layer>;
using game_ptr       = std::shared_ptr<game>;

// SDL Smart Pointers
using sdlwindow_ptr  = std::shared_ptr<SDL_Window>;
using sdlrender_ptr  = std::shared_ptr<SDL_Renderer>;
using sdltexture_ptr = std::shared_ptr<SDL_Texture>;
using font_ptr       = std::shared_ptr<TTF_Font>;
using tile_ptr       = std::shared_ptr<tile>;

/////////////////////////////////////////////////////////////
// APPLICATION GLOBALS
//

static const std::string _APP_NAME    = "sage";
static const std::string _APP_VERSION = "v0.0.1-A";
static const std::string _APP_AUTHOR  = "C. M. Short";
static const std::string _APP_SOURCE  = "http://www.github.com/chortlesoft/sage";
static const std::string _APP_INIT    = "./asset/init.json";

static const std::vector<std::string> APP_STRINGS = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
  "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4",
  "5", "6", "7", "8", "9", "[", "]", "\"", "\\", "#", "*", "(", ")", "-", "+", "=", "'", "<", ">",
  "?", "@", ".", ",", ";", ":", " ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
  "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "/" };


#endif // _SAGE_FORWARDS_HPP
