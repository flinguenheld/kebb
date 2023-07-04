#include "renderer.h"
#include "SDL_render.h"

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height), grid_width(grid_width),
      grid_height(grid_height), _font(nullptr) {

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

  _font = TTF_OpenFont("../font/DejaVuSansMono-Bold.ttf", 3000);
  if (_font == nullptr) {
    std::cerr << "Could not open the lazy.ttf";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width,
                             screen_height, SDL_WINDOW_SHOWN);

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

  // FIX: logical size - need an elegant solution !!

  if (SDL_RenderSetLogicalSize(_renderer, screen_width * 100, screen_height * 100) != 0) {
    std::cerr << "Renderer could not be scale.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // std::cout << "logical: " << SDL_RenderSetLogicalSize(_renderer, screen_width * 100, screen_height * 100)
  //           << "\n";
  // std::cout << SDL_RenderSetScale(_renderer, screen_width * 100, screen_height * 100) << "\n";
  // std::cout << SDL_RenderSetIntegerScale(_renderer, SDL_bool::SDL_TRUE) << "\n";
}

Renderer::~Renderer() {

  for (auto &i : _images)
    SDL_DestroyTexture(i);

  TTF_CloseFont(_font);
  TTF_Quit();
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

// TEST ----------------------------------------------------
// TEST ----------------------------------------------------
void Renderer::render_targets(const std::vector<Target> &targets) {
  for (std::vector<SDL_Texture *>::iterator it = _images.begin(); it != _images.end();) {
    SDL_DestroyTexture(*it);
    it = _images.erase(it);
  }

  for (auto &target : targets) {

    SDL_Surface *textSurface = TTF_RenderText_Solid(_font, target.char_ptr(), target.color());
    if (textSurface == NULL) {
      printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {

      // Create texture from surface pixels
      auto new_image = SDL_CreateTextureFromSurface(_renderer, textSurface);
      if (new_image == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
      } else {
        _images.emplace_back(new_image);
      }

      // Get rid of old surface
      SDL_FreeSurface(textSurface);

      SDL_Rect renderQuad = {target.position().x, target.position().y, target.w(), target.h()};
      SDL_Point center = {};
      SDL_RendererFlip flip = {};

      SDL_RenderCopyEx(_renderer, new_image, nullptr, &renderQuad, 0, &center, flip);
    }
  }
}

// TEST ----------------------------------------------------

TTF_Font *Renderer::font() { return _font; }

void Renderer::Render(Snake const snake, SDL_Point const &food, const std::vector<Target> &targets) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer);

  // Render food
  SDL_SetRenderDrawColor(_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_renderer, &block);
  }

  // TEST ----------------------------------------------------
  // TEST ----------------------------------------------------
  render_targets(targets);

  // TEST ----------------------------------------------------

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(_renderer, &block);
  // Update Screen
  SDL_RenderPresent(_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_window, title.c_str());
}
