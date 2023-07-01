#include "renderer.h"
#include "SDL_image.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height), grid_width(grid_width),
      grid_height(grid_height), sdl_font(nullptr) {
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

  std::cout << "helloooo \n";
  sdl_font = TTF_OpenFont("../font/lazy.ttf", 500);
  if (sdl_font == nullptr) {
    std::cerr << "Could not open the lazy.ttf";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  // std::cout << font << "helloooo \n";

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_CloseFont(sdl_font);
  TTF_Quit();
  SDL_Quit();
}

// Test ----------------------------------------------------
SDL_Texture *renderText(TTF_Font *font, const std::string &message, const std::string &fontFile,
                        SDL_Color color, SDL_Renderer *renderer) {
  // We need to first render to a surface as that's what TTF_RenderText
  // returns, then load that surface into a texture

  SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
  if (surf == nullptr) {
    // logSDLError(std::cout, "TTF_RenderText");
    return nullptr;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
  if (texture == nullptr) {
    // logSDLError(std::cout, "CreateTexture");
  }
  // Clean up the surface and font
  SDL_FreeSurface(surf);
  return texture;
}
// Test ----------------------------------------------------

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // TEST ----------------------------------------------------

  // const std::string resPath = getResourcePath("Lesson6");
  // We'll render the string "TTF fonts are cool!" in white
  // Color is in RGBA format
  SDL_Color color = {255, 255, 255, 255};

  SDL_Texture *image = renderText(sdl_font, "TTF fonts are cool!", "../font/lazy.ttf", color, sdl_renderer);
  if (image == nullptr) {
    // cleanup(sdl_renderer, sdl_window);
    // TTF_Quit();
    // SDL_Quit();
  }
  // Get the texture w/h so we can center it in the screen
  int iW, iH;
  SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
  int x = 200;
  int y = 200;

  // Note: This is within the program's main loop
  // SDL_RenderClear(renderer);
  // We can draw our message as we do any other texture, since it's been
  // rendered to a texture
  SDL_RenderCopy(sdl_renderer, image, nullptr, nullptr);

  // TEST ----------------------------------------------------

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
