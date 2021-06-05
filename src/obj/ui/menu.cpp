////////////////////////////////////////////////////////////////////////////
//
// sage - menu.cpp
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
// MENU Class implementation
//

menu::menu(state_ptr const& g_state) : layer(g_state) {
  // Create our menu objects
  object_ptr over     = std::make_shared<overlay>(g_state, "BLACK", 230);
  object_ptr bordr    = std::make_shared<border>(g_state, "D_GRAY");
  object_ptr title    = std::make_shared<text>(g_state, "SAGE", "M_MNU_TITLE", "DEFAULT");
  object_ptr conbtn   = std::make_shared<button>(g_state, "Continue", "M_MNU_BUTTON", "MNU_CONT");
  object_ptr newbtn   = std::make_shared<button>(g_state, "New", "M_MNU_BUTTON", "MNU_NEW");
  object_ptr loadbtn  = std::make_shared<button>(g_state, "Load", "M_MNU_BUTTON", "MNU_LOAD");
  object_ptr aboutbtn = std::make_shared<button>(g_state, "About", "M_MNU_BUTTON", "MNU_ABOUT");
  object_ptr quitbtn  = std::make_shared<button>(g_state, "Quit", "M_MNU_BUTTON", "MNU_QUIT");

  // Add our menu objects to the menu
  add(over);
  add(bordr);
  add(title);
  add(conbtn);
  add(newbtn);
  add(loadbtn);
  add(aboutbtn);
  add(quitbtn);

  // Calculate the space our menu will take up
  int padd   = title->get_source().h;
  int startx = (o_position.w / 2);
  int starty = (o_position.h / 2) - (padd * 5); //- height;
  int offset = 0;

  title->set_position({ startx - (title->get_source().w / 2), starty - (title->get_source().h / 2) + (offset += padd), 0, 0});
  conbtn->set_position({ startx - (conbtn->get_source().w / 2), starty - (conbtn->get_source().h / 2) + (offset += (padd + (padd / 2))), 0, 0});
  newbtn->set_position({ startx - (newbtn->get_source().w / 2), starty - (newbtn->get_source().h / 2) + (offset += padd), 0, 0});
  loadbtn->set_position({ startx - (loadbtn->get_source().w / 2), starty - (loadbtn->get_source().h / 2) + (offset += padd), 0, 0});
  aboutbtn->set_position({ startx - (aboutbtn->get_source().w / 2), starty - (aboutbtn->get_source().h / 2) + (offset += padd), 0, 0});
  quitbtn->set_position({ startx - (quitbtn->get_source().w / 2), starty - (quitbtn->get_source().h / 2) + (offset += padd), 0, 0});

  if(g_state->get_game() == nullptr)
    conbtn->set_paused(true);
}


void        menu::finalize(state_ptr const& g_state) {
  for(auto &id : l_objectid)
    l_objects[id]->finalize(g_state);

}


bool const& menu::update(state_ptr const& g_state) {

  if(g_state->get_game() == nullptr)
    l_objects[l_objectid[3]]->set_paused(true);
  else
    l_objects[l_objectid[3]]->set_paused(false);

  for(auto const& id : l_objectid)
    o_changed += l_objects[id]->update(g_state);

  if(o_changed)
    draw(g_state);

  return o_changed;
}
