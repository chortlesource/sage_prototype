////////////////////////////////////////////////////////////////////////////
//
// sage - sage.hpp
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

#ifndef _SAGE_HPP
#define _SAGE_HPP


/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

// SDL Dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Jsoncpp Dependencies
#include <libs/json-forwards.h>
#include <libs/json.h>

// C++ Std Dependencies
#include <iostream>
#include <memory>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <functional>
#include <filesystem>

#include <string>
#include <array>
#include <queue>
#include <unordered_map>

/////////////////////////////////////////////////////////////
// LOCAL INCLUDES
//

// Utility
#include <util/forwards.hpp>
#include <util/debug.hpp>
#include <util/timer.hpp>

// Object
#include <obj/object.hpp>
#include <obj/tile.hpp>
#include <obj/layer.hpp>
#include <obj/ui/text.hpp>
#include <obj/ui/button.hpp>
#include <obj/ui/menu.hpp>
#include <obj/ui/frame.hpp>

// Core
#include <core/game.hpp>
#include <core/map.hpp>

// System
#include <sys/events.hpp>
#include <sys/manager.hpp>
#include <sys/assets.hpp>
#include <sys/stage.hpp>
#include <sys/window.hpp>
#include <sys/state.hpp>
#include <sys/engine.hpp>


#endif // SAGE_HPP
