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

// Object Classes
class object;
class tile;
class layer;

// System Classes
class manager;
class assets;
class window;
class state;
class engine;


/////////////////////////////////////////////////////////////
// SMART POINTERS
//

// System Smart Pointers
using state_ptr      = std::shared_ptr<state>;
using object_ptr     = std::shared_ptr<object>;
using layer_ptr      = std::shared_ptr<layer>;

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
static const std::string _APP_VERSION = "0.0.1-ALPHA";
static const std::string _APP_AUTHOR  = "C. M. Short";
static const std::string _APP_SOURCE  = "http://www.github.com/chortlesoft/sage";
static const std::string _APP_INIT    = "./asset/init.json";


#endif // _SAGE_FORWARDS_HPP
