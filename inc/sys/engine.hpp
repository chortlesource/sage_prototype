////////////////////////////////////////////////////////////////////////////
//
// sage - engine.hpp
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

#ifndef _SAGE_ENGINE_HPP
#define _SAGE_ENGINE_HPP


/////////////////////////////////////////////////////////////////
// ENGINE Class
//
// The engine class handles the main game loop logic

class engine {
public:
  engine();
  virtual ~engine();

  virtual void start() final;

private:
  bool         initialized;
  unsigned int eventid;
  state_ptr    g_state;

  // These functions are where game logic is to be implemented
  virtual void on_user_init()     {}
  virtual void on_user_update()   {}
  virtual void on_user_finalize() {}
};


#endif // _SAGE_ENGINE_HPP
