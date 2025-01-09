#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <spdlog/spdlog.h>

#include <string>
#include <vector>
#include <optional>


#include "nile/app/renderer.hpp"

const int RES_WIDTH = 800;
const int RES_HEIGHT = 600;

class Window {
 private:
  SDL_Window *window = nullptr;

  void initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      spdlog::error("Failed to init SDL: {}", SDL_GetError());
      return;
    }

    if (SDL_Vulkan_LoadLibrary(nullptr) < 0) {
      spdlog::error("Failed to load SDL Vulkan Library: {}", SDL_GetError());
      return;
    }

    window = SDL_CreateWindow("Nile",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      RES_WIDTH, RES_HEIGHT,
      SDL_WINDOW_VULKAN);

    if (!window) {
      spdlog::error("Failed to create SDL window: {}", SDL_GetError());
      return;
    }

    SDL_UpdateWindowSurface(window);
  }

  void close() {
    if (window != nullptr) {
      SDL_DestroyWindow(window);
    }
  }

 public:
  Window() { initialize(); }

  ~Window() { close(); }

  bool isInitialized() {
    return window != nullptr;
  }

  std::optional<std::vector<const char*>> getVulkanInstanceExtensions() {
    uint count;

    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, NULL)) {
      spdlog::error("Unable to get Vulkan extensions count: {}", SDL_GetError());
      return {};
    }

    std::vector<const char *> names(count);
    if (!SDL_Vulkan_GetInstanceExtensions(window, &count, names.data())) {
      spdlog::error("Unable to get Vulkan extension names: {}", SDL_GetError());
      return {};
    }

    return names;
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