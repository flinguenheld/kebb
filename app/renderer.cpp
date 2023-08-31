#include "renderer.h"

Renderer::Renderer(kebb::boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target,
                   uint16_t font_size_game, uint16_t font_size_menu)
    : _screen_size(screen_size), _scale_factor(scale_factor), _font_target(nullptr), _font_game(nullptr),
      _font_menu(nullptr), _init_ok(false) {

  _color_background = kebb::color(kebb::ColorName::C_Base);

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {

    // Initialize the TTF library
    if (TTF_Init() >= 0) {

      // Fonts --
#ifdef RELEASE_LINUX
      _font_target = TTF_OpenFont("/usr/share/kebb/font/dejavu-sans-mono.bold.ttf", font_size_target);
      _font_game = TTF_OpenFont("/usr/share/kebb/font/charybdis.regular.ttf", font_size_game);
      _font_menu = TTF_OpenFont("/usr/share/kebb/font/charybdis.regular.ttf", font_size_menu);
#else
      _font_target = TTF_OpenFont("./font/dejavu-sans-mono.bold.ttf", font_size_target);
      _font_game = TTF_OpenFont("./font/charybdis.regular.ttf", font_size_game);
      _font_menu = TTF_OpenFont("./font/charybdis.regular.ttf", font_size_menu);
#endif

      if (_font_target != nullptr && _font_game != nullptr && _font_menu != nullptr) {

        int w = 0; // Get the size for one char here
        int h = 0;

        TTF_SizeUTF8(_font_target, "X", &w, &h);
        _char_size_target = {static_cast<uint16_t>(w), static_cast<uint16_t>(h)};

        TTF_SizeUTF8(_font_game, "X", &w, &h);
        _char_size_game = {static_cast<uint16_t>(w), static_cast<uint16_t>(h)};

        TTF_SizeUTF8(_font_menu, "X", &w, &h);
        _char_size_menu = {static_cast<uint16_t>(w), static_cast<uint16_t>(h)};

        // Create Window
        _window = SDL_CreateWindow("Kebb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_size.w,
                                   _screen_size.h, SDL_WINDOW_SHOWN);
        if (_window != nullptr) {

          // Create renderer
          _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
          if (_renderer != nullptr) {

            // Add transparency
            if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND) == 0) {

              // Set a logical scale, mandatory to move in all directions
              if (SDL_RenderSetLogicalSize(_renderer, _screen_size.w * _scale_factor,
                                           _screen_size.h * _scale_factor) == 0) {

                _init_ok = true;

              } else {
                std::cerr << "Renderer could not be scale.\n";
                std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
              }
            } else {
              std::cerr << "Transparency management could not be set.\n";
              std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
            }
          } else {
            std::cerr << "Renderer could not be created.\n";
            std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
          }
        } else {
          std::cerr << "Window could not be created.\n";
          std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
        }
      } else {
        std::cerr << "Could not open the font ttf files.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
      }
    } else {
      std::cerr << "Could not initialize TTF.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
  } else {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  TTF_CloseFont(_font_target);
  TTF_CloseFont(_font_menu);
  TTF_CloseFont(_font_game);
  TTF_Quit();
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

bool Renderer::init_ok() const { return _init_ok; }
SDL_Renderer *Renderer::renderer() { return _renderer; }

void Renderer::update_window_title(uint16_t fps) {
  std::string title{"Kebb - [" + std::to_string(fps) + (" fps]")};
  SDL_SetWindowTitle(_window, title.c_str());
}

/*
 * Standardize SDL_RenderClear with the background color
 */
void Renderer::clear_screen() {
  SDL_SetRenderDrawColor(_renderer, _color_background.r, _color_background.g, _color_background.b, 0xFF);
  SDL_RenderClear(_renderer);
}

// ----------------------------------------------------------------------------------------------------
// FONTS ----------------------------------------------------------------------------------------------

kebb_font Renderer::font_blabla(FontName font_name) {

  switch (font_name) {
  case FontName::F_Target:
    return {_font_target, _char_size_target};
  case FontName::F_Menu:
    return {_font_menu, _char_size_menu};
  default:
    return {_font_game, _char_size_game};
  }
}

TTF_Font *Renderer::font(FontName fn) {
  switch (fn) {
  case FontName::F_Target:
    return _font_target;
  case FontName::F_Menu:
    return _font_menu;
  default:
    return _font_game;
  }
}
kebb::boxsize Renderer::font_char_size(FontName fn) const {
  switch (fn) {
  case FontName::F_Target:
    return _char_size_target;
  case FontName::F_Menu:
    return _char_size_menu;
  default:
    return _char_size_game;
  }
}
