////////////////////////////////////////////////////////////////////////////
//
// sage - manager.hpp
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

#ifndef _SAGE_MANAGER_HPP
#define _SAGE_MANAGER_HPP


/////////////////////////////////////////////////////////////
// DELEGATE Class
//
// The delegate Class are containers for callbacks to the object's
// on notify and are handled by the manager


class delegate {
public:
  delegate(uint32_t const& i, eventtype const& t, std::function<void(event const&)> const& f) : id(i), type(t), callback(f) {}
  ~delegate() {}

  void operator()(event const& e) const;
  bool operator==(delegate const& rhs) const noexcept;

  eventtype const& get_type() const noexcept;
  uint32_t const& get_id() const noexcept;

private:
  uint32_t  id;
  eventtype type;
  std::function<void(event const&)> callback;
};


/////////////////////////////////////////////////////////////
// MANAGER Class
//
// MANAGER class is a container for application events and delegates
// for the management and execution of events within the game


class manager {
  using delegatelist = std::vector<delegate>;
  using delegatemap  = std::unordered_map<eventtype, delegatelist>;

public:
  manager() : ids(0), delegates(), events() {}
  ~manager() {}

  // Public MANAGER methods
  bool add_delegate(delegate const& del);
  bool remove_delegate(delegate const& del);
  void send_event(event const& e);
  void update();

  uint32_t const& get_delegate_id();

private:
  uint32_t          ids;
  delegatemap       delegates;
  std::queue<event> events;
};

#endif // _SAGE_MANAGER_HPP
