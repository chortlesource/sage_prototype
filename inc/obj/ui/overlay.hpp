////////////////////////////////////////////////////////////////////////////
//
// sage - overlay.hpp
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

#ifndef _SAGE_OVERLAY_HPP
#define _SAGE_OVERLAY_HPP


/////////////////////////////////////////////////////////////
// OVERLAY Class
//
// The overlay class is an overlay ui object

class overlay : public object {
public:
  overlay(state_ptr const& g_state, std::string const& colorid, int const& alpha);

};


#endif // _SAGE_OVERLAY_HPP
