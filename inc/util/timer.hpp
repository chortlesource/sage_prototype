////////////////////////////////////////////////////////////////////////////
//
// sage - timer.hpp
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

#ifndef _SAGE_TIMER_HPP
#define _SAGE_TIMER_HPP


/////////////////////////////////////////////////////////////
// TIMER Class
//
// The timer class handles time logic for the application

class timer {

private:
  double start_time;
  double last_time;
  double delta_time;
  double elapsed_time;
  double ms;

public:
  timer() : start_time(0), last_time(0), delta_time(0), elapsed_time(0), ms(0) {};
  ~timer() {};

  void start() {
    // start() - Initialize the timer and begin the count
    start_time = this->time();
  }

  void update() {
    // update() - Update the timer to calculate delta and elapsed
    double new_time = this->time();
    delta_time = new_time - last_time;
    last_time = new_time;

    elapsed_time += delta_time;
  }


  double const& delta() const noexcept {
    return delta_time;
  }


  double const& elapsed() const noexcept {
    return elapsed_time;
  }

  double const& time() {
    const auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
    return ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000;
  }

};


#endif // _SAGE_TIMER_HPP
