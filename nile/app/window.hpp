#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <spdlog/spdlog.h>

#include "nile/app/renderer.hpp"

const int RES_WIDTH = 800;
const int RES_HEIGHT = 600;

class Window {
 private:
  SDL_Window *window = nullptr;
  SDL_Surface *surface = nullptr;

  void initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      spdlog::error("Failed to init SDL: {}", SDL_GetError());
      return;
    }

    if (SDL_Vulkan_LoadLibrary(nullptr) < 0) {
      spdlog::error("Failed to load SDL Vulkan Library: {}", SDL_GetError());
      return;
    }

    window = SDL_CreateWindow("Nile", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, RES_WIDTH, RES_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

    if (!window) {
      spdlog::error("Failed to create SDL window: {}", SDL_GetError());
      return;
    }

    surface = SDL_GetWindowSurface(window);
    if (!surface) {
      spdlog::error("Failed to get SDL surface: {}", SDL_GetError());
      return;
    }

    SDL_Rect rect = { .x = 0, .y = 0, .w = RES_WIDTH, .h = RES_HEIGHT };
    Uint32 color = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_FillRect(surface, &rect, color);

    SDL_UpdateWindowSurface(window);
  }

  void close() {
    if (surface != nullptr) {
      SDL_DestroyWindowSurface(window);
    }

    if (window != nullptr) {
      SDL_DestroyWindow(window);
    }
  }

 public:
  Window() { initialize(); }

  ~Window() { close(); }

  bool isInitialized() {
    return surface != nullptr;
  }

  static void runEventLoop(Renderer &renderer) {
    bool shouldQuit = false;

    while (!shouldQuit) {
      SDL_Event e;
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          shouldQuit = true;
        }

        renderer.render();
      }
    }
  }
};