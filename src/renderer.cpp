#include "renderer.h"
#include "SDL_ttf.h"
#include <cstdint>

Renderer::Renderer(boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target,
                   uint16_t font_size_score, uint16_t font_size_menu)
    : _screen_size(screen_size), _scale_factor(scale_factor), _font_target(nullptr), _font_score(nullptr),
      _font_menu(nullptr) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  /* Initialize the TTF library */
  if (TTF_Init() < 0) {
    std::cerr << "Could not initialize TTF.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // TODO: Manage the fonts files
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
  _window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_size.w,
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

TTF_Font *Renderer::font_target() { return _font_target; }
TTF_Font *Renderer::font_score() { return _font_score; }
TTF_Font *Renderer::font_menu() { return _font_menu; }
boxsize Renderer::char_size_target() const { return _char_size_target; }
boxsize Renderer::char_size_score() const { return _char_size_score; }
boxsize Renderer::char_size_menu() const { return _char_size_menu; }

SDL_Renderer *Renderer::renderer() { return _renderer; }

void Renderer::UpdateWindowTitle(uint16_t fps) {
  std::string title{"Kepp - FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_window, title.c_str());
}
