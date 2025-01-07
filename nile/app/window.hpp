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

  bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      spdlog::error("Failed to init SDL: {}", SDL_GetError());
      return false;
    }

    if (SDL_Vulkan_LoadLibrary(nullptr) < 0) {
      spdlog::error("Failed to load SDL Vulkan Library: {}", SDL_GetError());
      return false;
    }

    window = SDL_CreateWindow("Nile", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, RES_WIDTH, RES_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

    if (!window) {
      spdlog::error("Failed to create SDL window: {}", SDL_GetError());
      return false;
    }

    surface = SDL_GetWindowSurface(window);
    if (!surface) {
      spdlog::error("Failed to get SDL surface: {}", SDL_GetError());
      return false;
    }

    SDL_UpdateWindowSurface(window);
    return true;
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
    spdlog::info("asidn");
    // while (true) {
    //   SDL_Event e;
    //   while (SDL_PollEvent(&e) != 0) {
    //     if (e.type == SDL_QUIT) {
    //       break;
    //     }

    //     renderer.render();
    //   }
    // }
  }
};