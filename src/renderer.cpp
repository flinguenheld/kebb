#include "renderer.h"

Renderer::Renderer(boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target,
                   uint16_t font_size_score, std::shared_ptr<Score> score)
    : _screen_size(screen_size), _scale_factor(scale_factor), _font_target(nullptr), _font_score(nullptr),
      _score(score) {

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
  // TODO: Use a different font for score or use only one font ?
  _font_target = TTF_OpenFont("../font/dejavu-sans-mono.bold.ttf", font_size_target);
  // _font_target = TTF_OpenFont("../font/cmu.typewriter-text-bold.ttf", font_size_target);
  _font_score = TTF_OpenFont("../font/charybdis.regular.ttf", font_size_score);
  // _font_score = TTF_OpenFont("../font/intelone-mono.regular.ttf", font_size_score);

  if (_font_target == nullptr || _font_score == nullptr) {
    std::cerr << "Could not open the lazy.ttf";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
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

  // TODO: logical size - need an elegant solution !!

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

TTF_Font *Renderer::font() { return _font_target; }
TTF_Font *Renderer::font_score() { return _font_score; }
SDL_Renderer *Renderer::renderer() { return _renderer; }

void Renderer::Render(const std::vector<Target> &targets) {

  // Clear screen
  SDL_SetRenderDrawColor(_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer);

  _score->render(_renderer, _font_score);

  for (auto &target : targets)
    target.render(_renderer, _font_target);

  // Update Screen
  SDL_RenderPresent(_renderer);
}

void Renderer::UpdateWindowTitle(uint16_t fps) {
  std::string title{"Kepp - FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_window, title.c_str());
}
