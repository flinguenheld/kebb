#include "renderer.h"

Renderer::Renderer(kebb::boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target,
                   uint16_t font_size_score, uint16_t font_size_menu)
    : _screen_size(screen_size), _scale_factor(scale_factor), _font_target(nullptr), _font_score(nullptr),
      _font_menu(nullptr) {

  // _color_background = kebb::color(kebb::ColorName::C_Sky);
  _color_background = kebb::color(kebb::ColorName::C_Base);

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize the TTF library
  if (TTF_Init() < 0) {
    std::cerr << "Could not initialize TTF.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Fonts --
  _font_target = TTF_OpenFont("../font/dejavu-sans-mono.bold.ttf", font_size_target);
  // _font_target = TTF_OpenFont("../font/cmu.typewriter-text-bold.ttf", font_size_target);
  _font_score = TTF_OpenFont("../font/charybdis.regular.ttf", font_size_score);
  // _font_score = TTF_OpenFont("../font/intelone-mono.regular.ttf", font_size_score);
  _font_menu = TTF_OpenFont("../font/charybdis.regular.ttf", font_size_menu);

  if (_font_target == nullptr || _font_score == nullptr || _font_menu == nullptr) {
    std::cerr << "Could not open the lazy.ttf";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  } else {

    int w = 0; // Get the size for one char here
    int h = 0;

    TTF_SizeUTF8(_font_target, "X", &w, &h); // NOTE: Add a check ?
    _char_size_target = {static_cast<uint16_t>(w), static_cast<uint16_t>(h)};

    TTF_SizeUTF8(_font_score, "X", &w, &h);
    _char_size_score = {static_cast<uint16_t>(w), static_cast<uint16_t>(h)};

    TTF_SizeUTF8(_font_menu, "X", &w, &h);
    _char_size_menu = {static_cast<uint16_t>(w), static_cast<uint16_t>(h)};
  }

  // Create Window
  _window = SDL_CreateWindow("Kebb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_size.w,
                             _screen_size.h, SDL_WINDOW_SHOWN);

  if (nullptr == _window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == _renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Add transparency
  if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND) != 0) {
    std::cerr << "Transparency management could not be set.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Set a logical scale, mandatory to move in all directions
  if (SDL_RenderSetLogicalSize(_renderer, _screen_size.w * _scale_factor, _screen_size.h * _scale_factor) !=
      0) {
    std::cerr << "Renderer could not be scale.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  TTF_CloseFont(_font_target);
  TTF_CloseFont(_font_score);
  TTF_Quit();
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

SDL_Renderer *Renderer::renderer() { return _renderer; }

void Renderer::update_window_title(uint16_t fps) {
  // std::string title{"Kebb - " + std::to_string(_screen_size.w) + "x" + std::to_string(_screen_size.h) +
  //                   " - fps: " + std::to_string(fps)};
  std::string title{"Kebb - [" + std::to_string(fps) + (" fps]")};
  SDL_SetWindowTitle(_window, title.c_str());
}

/*
 * Standardize SDL_RenderClear with the background color
 */
void Renderer::clear_screen() {
  // SDL_SetRenderDrawColor(_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_SetRenderDrawColor(_renderer, _color_background.r, _color_background.g, _color_background.b, 0xFF);
  SDL_RenderClear(_renderer);
}

// ----------------------------------------------------------------------------------------------------
// FONTS ----------------------------------------------------------------------------------------------
TTF_Font *Renderer::font(FontName fn) {
  switch (fn) {
  case FontName::F_Target:
    return _font_target;
  case FontName::F_Menu:
    return _font_menu;
  default: // F_Score
    return _font_score;
  }
}
kebb::boxsize Renderer::font_char_size(FontName fn) const {
  switch (fn) {
  case FontName::F_Target:
    return _char_size_target;
  case FontName::F_Menu:
    return _char_size_menu;
  default: // F_Score
    return _char_size_score;
  }
}
