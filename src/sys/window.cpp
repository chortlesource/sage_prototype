////////////////////////////////////////////////////////////////////////////
//
// sage - window.cpp
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
// WINDOW Class implementation
//

window::~window() {
  initialized = false;
  g_renderer  = nullptr;
  g_window    = nullptr;
}


void window::initialize(Json::Value const& g_config) {
  // Initialize basic variables
  std::string title = _APP_NAME + " - " + _APP_VERSION;
  const int w = g_config["APP_W"].asInt();
  const int h = g_config["APP_H"].asInt();

  // Create the window
  sdlwindow_ptr win(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN), [=](SDL_Window *w) { SDL_DestroyWindow(w); });

  g_window = win;
  if(g_window == nullptr) {
    ERROR("[SDL_WINDOW_ERROR]:", SDL_GetError());
    return;
  }

  // Create the renderer
  sdlrender_ptr ren(SDL_CreateRenderer(g_window.get(), -1, SDL_RENDERER_ACCELERATED
    | SDL_RENDERER_PRESENTVSYNC), [=](SDL_Renderer *r) { SDL_DestroyRenderer(r); });

  g_renderer = ren;
  if(g_renderer == nullptr) {
    ERROR("[SDL_RENDER_ERROR]:", SDL_GetError());
    g_window = nullptr;
    return;
  }

  SDL_RenderSetLogicalSize(g_renderer.get(), w, h);
  SDL_SetRenderDrawColor(g_renderer.get(), 255, 255, 255, 255);
  SDL_RenderClear(g_renderer.get());
  SDL_RenderPresent(g_renderer.get());

  initialized = true;
  INFO("Initialized SDL WINDOW [COMPLETE]");
}


void window::update(state_ptr const& g_state) {
  if(!initialized) return;

  // Poll for window events
  SDL_Event s_event;

  if(SDL_PollEvent(&s_event)) {
    switch(s_event.type) {
      case SDL_WINDOWEVENT:
        switch(s_event.window.event) {
          case SDL_WINDOWEVENT_CLOSE:
            g_state->set_status(state::status::exit);
            break;
          default:
            break;
        };
      default:
        break;
    };
  }

  SDL_RenderPresent(g_renderer.get());
  SDL_SetRenderDrawColor(g_renderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(g_renderer.get());
}


SDL_Window*   window::get_window() {
  return g_window.get();
};


SDL_Renderer* window::get_render() {
  return g_renderer.get();
}
