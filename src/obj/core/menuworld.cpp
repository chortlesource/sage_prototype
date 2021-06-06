////////////////////////////////////////////////////////////////////////////
//
// sage - menuworld.cpp
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
// MENUWOLRD Class implementation
//

menuworld::menuworld(state_ptr const& g_state) : menu(g_state) {
  // Create our menu objects
  object_ptr over     = std::make_shared<overlay>(g_state, "BLACK", 255);
  object_ptr bordr    = std::make_shared<border>(g_state, "D_GRAY");
  object_ptr title    = std::make_shared<text>(g_state, "CREATE NEW WORLD", "M_MNU_TITLE", "DEFAULT");
  object_ptr seedlbl  = std::make_shared<gtext>(g_state, "ENTER SEED", "DEFAULT", "NONE");
  object_ptr seedtxt  = std::make_shared<textbox>(g_state,"WORLDSEED" , 15);
  object_ptr creabtn  = std::make_shared<button>(g_state, "Create", "M_MNU_BUTTON", "MNU_WORLD_CREATE");
  object_ptr cancbtn  = std::make_shared<button>(g_state, "Cancel", "M_MNU_BUTTON", "MNU_WORLD_CANCEL");

  // Add our menu objects to the menu
  add(over);
  add(bordr);
  add(title);
  add(seedlbl);
  add(seedtxt);
  add(creabtn);
  add(cancbtn);
  add_menu_object(seedtxt);
  add_menu_object(creabtn);
  add_menu_object(cancbtn);

  // Calculate the space our menu will take up
  int padd   = title->get_source().h;
  int startx = (o_position.w / 2);
  int starty = (o_position.h / 2) - (padd * 5); //- height;
  int offset = 0;

  title->set_position({ startx - (title->get_source().w / 2), starty - (padd / 2) + (offset += padd), 0, 0});
  seedlbl->set_position({ startx - (seedlbl->get_source().w / 2), starty - (padd / 2) + (offset += (padd + (padd / 2))), 0, 0});
  seedtxt->set_position({ startx - (seedtxt->get_source().w / 2), starty - (padd / 2) + (offset += padd), 0, 0});
  creabtn->set_position({ startx - creabtn->get_source().w - (creabtn->get_source().w / 2), starty - (padd / 2) + (offset += padd), 0, 0});
  cancbtn->set_position({ startx + (cancbtn->get_source().w / 2), starty - (padd / 2) + offset, 0, 0});
}


void menuworld::reset() {
  for(auto &obj : m_objects)
    obj->reset();
}
