////////////////////////////////////////////////////////////////////////////
//
// sage - frame.cpp
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
// FRAME Class implementation
//

frame::frame(state_ptr const& g_state) : layer(g_state) {

  // Calculate tile dimensions
  int tile_w = g_state->get_assets()->find_json("atlas")["TILE_W"].asInt();
  int tile_h = g_state->get_assets()->find_json("atlas")["TILE_H"].asInt();

  object_ptr bordr = std::make_shared<border>(g_state, "L_GRAY");
  object_ptr title = std::make_shared<gtext>(g_state, " sage ", "BLUE", "BLACK");
  object_ptr versn = std::make_shared<gtext>(g_state, _APP_VERSION, "RED", "BLACK");
  object_ptr stats = std::make_shared<statbar>(g_state);
  title->set_position({(o_position.w / 2) - (title->get_position().w / 2), 0, 0, 0 });
  versn->set_position({ tile_w * 2, o_position.h - tile_h, 0, 0 });
  stats->set_position({ o_position.w - (stats->get_position().w + tile_w), o_position.h - tile_h, 0, 0 });
  add(bordr);
  add(title);
  add(versn);
  add(stats);

}
