////////////////////////////////////////////////////////////////////////////
//
// sage - textbox.hpp
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

#ifndef _SAGE_TEXTBOX_HPP
#define _SAGE_TEXTBOX_HPP


/////////////////////////////////////////////////////////////
// TEXTBOX Class
//
// A basic ui object for text input

class textbox : public object {
public:
  textbox(state_ptr const& g_state, int const& len);

  virtual bool const& update  (state_ptr const& g_state) override;
  virtual void        finalize(state_ptr const& g_state) override;

private:
  int         offset;
  int         length;
  std::string caption;

  bool handle_key (std::string const& str);
  void handle_draw(state_ptr const& g_state);

  void register_delegates(state_ptr const& g_state);
  void remove_delegates(state_ptr const& g_state);
  void on_event(event const& e);

};


#endif // _SAGE_TEXTBOX_HPP
