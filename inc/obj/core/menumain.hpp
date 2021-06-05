////////////////////////////////////////////////////////////////////////////
//
// sage - menumain.hpp
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

#ifndef _SAGE_MENUMAIN_HPP
#define _SAGE_MENUMAIN_HPP


/////////////////////////////////////////////////////////////
// MENUMAIN Class
//
// The menumain class handles the games menumain logic

class menumain : public menu {
public:
  menumain(state_ptr const& g_state);

  virtual bool const& update(state_ptr const& g_state) override;

private:
  void toggle_continue();

};

#endif // _SAGE_MENU_HPP
