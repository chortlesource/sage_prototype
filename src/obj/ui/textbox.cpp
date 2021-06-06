////////////////////////////////////////////////////////////////////////////
//
// sage - textbox.cpp
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
// TEXTBOX Class implementation
//

textbox::textbox(state_ptr const& g_state, std::string const& name, int const& len) : object(g_state) {
  // Initialize dimension variables
  int tile_w = g_state->get_input().tile_w;
  int tile_h = g_state->get_input().tile_h;
  int width  = tile_w * len;
  int height = tile_h;

  // Initialize our object
  o_source   = { 0, 0, width, height };
  o_position = o_source;
  o_active   = false;
  caption    = "";
  offset     = 0;
  length     = len;
  t_name     = name;

  SDL_Renderer *render = g_state->get_window()->get_render();

  // Create our textbox texture
  sdltexture_ptr texture(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    width, height), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  o_texture = texture;

  // Draw our text box
  handle_draw(g_state);

  // Register the event delegates
  register_delegates(g_state);
  initialized = true;
}


bool const& textbox::update(state_ptr const& g_state) {
  if(!initialized) return o_changed;

  // Lambda function for convenience
  auto is_over = [&] (int const& x, int const& y) {
    return (x > o_position.x && x < o_position.x + o_position.w && y > o_position.y && y < o_position.y + o_position.h);
  };

  // Obtain the current position of the mouse
  istate const& mouse = g_state->get_input();

  if(is_over(mouse.x, mouse.y)) {
    if(mouse.buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
      if(!o_active) {
        o_active  = true;
        o_changed = true;
      }
    }
  }

  if(o_changed)
    handle_draw(g_state);

  return o_changed;
}


void textbox::data() {
  // Send out data as requested
  o_manager->send_event(event(data_event(data_event::type::response, t_name, "", caption)));
};


void textbox::reset() {
  // Clear the current contents of the textbox
  offset    = 0;
  o_changed = true;
  caption.clear();
}


void textbox::finalize(state_ptr const& g_state) {
  // Remove event delegates
  initialized = false;
  remove_delegates(g_state);
}


void textbox::handle_key(const char *str) {

  for(auto const& key : _APP_CHARS) {
    if(key == str[0]) {
      caption.append(1, key);
      if(length <= (int)caption.size())
        offset  += 1;
      o_changed = true; // Redraw the textbox
    }
  }
}


void textbox::handle_draw(state_ptr const& g_state) {
  // Initialize dimension variables and renderer
  int tile_w = g_state->get_input().tile_w;
  int tile_h = g_state->get_input().tile_h;

  SDL_Renderer *render = g_state->get_window()->get_render();

  // Clear our texture for drawing
  SDL_SetTextureBlendMode(o_texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(render, o_texture.get());
  SDL_Color color = g_state->get_assets()->find_color("D_GRAY");
  SDL_Color tcolor = g_state->get_assets()->find_color("DEFAULT");
  SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 255);
  SDL_RenderClear(render);

  // Print the textbox
  int size = (length > (int)caption.size()) ? (int)caption.size() : length - 1;

  if(size != 0) {
    for(int i = 0; i < size; i++) {
      // Find the corresponding glyph and add to the textbox
      glyph_ptr gly   = g_state->get_assets()->find_glyph(caption[i + offset]);

      if(gly != nullptr) {
        // Copy the glyph to the image
        SDL_Rect pos = { tile_w * i, 0 , tile_w, tile_h };
        SDL_SetTextureColorMod(gly->get_texture(), tcolor.r, tcolor.g, tcolor.b);
        SDL_RenderCopy(render, gly->get_texture(), &gly->get_source(), &pos);
      }
    }
  }

  // Print the cursor if the textbox is active
  if(o_active) {
    object_ptr cursor = g_state->get_assets()->find_tile(12);
    SDL_Rect pos { tile_w * size, 0, tile_w, tile_h };
    SDL_RenderCopy(render, cursor->get_texture(), &cursor->get_source(), &pos);
  }

  SDL_SetRenderTarget(render, NULL);
  o_changed = false;
}


void textbox::register_delegates(state_ptr const& g_state) {
  // Register the event listeners
  std::function<void(event const&)> callback = [=](event const& e) -> void { this->on_event(e); };

  o_manager->add_delegate(delegate(o_eventid, eventtype::key, callback));
  o_manager->add_delegate(delegate(o_eventid, eventtype::data, callback));
}


void textbox::remove_delegates(state_ptr const& g_state) {
  o_manager->remove_delegate(delegate(o_eventid, eventtype::key, nullptr));
  o_manager->add_delegate(delegate(o_eventid, eventtype::data, nullptr));
}


void textbox::on_event(event const& e) {
  if(!o_active) return;

  switch(e.type) {
    case eventtype::key:
      if(e.key.keytype == key_event::type::release) {
        switch(e.key.scancode) {
          case SDL_SCANCODE_ESCAPE:
          case SDL_SCANCODE_RETURN:
            if(o_active) {
              o_active = false;
              o_changed = true;
            }
            break;
          case SDL_SCANCODE_DELETE:
          case SDL_SCANCODE_BACKSPACE:
            if(caption.size() > 0) {
              caption.pop_back();
              if(offset > 0)
                offset -= 1;
              o_changed = true;
            }
            break;
          case SDL_SCANCODE_SPACE:
            caption.append(" ");
            if(length <= (int)caption.size())
              offset  += 1;
            o_changed = true; // Redraw the textbox
            break;
          case SDL_SCANCODE_CAPSLOCK:
          case SDL_SCANCODE_LSHIFT:
          case SDL_SCANCODE_LALT:
          case SDL_SCANCODE_LCTRL:
          case SDL_SCANCODE_LGUI:
          case SDL_SCANCODE_RSHIFT:
          case SDL_SCANCODE_RALT:
          case SDL_SCANCODE_RCTRL:
          case SDL_SCANCODE_RGUI:
            break;
          default:
            handle_key(SDL_GetKeyName(e.key.key));
            break;
        };
      }
      break;
    case eventtype::data:
      if(e.data.target == t_name && e.data.action == data_event::type::request)
        data();
      break;
    default:
      break;
  }
}
