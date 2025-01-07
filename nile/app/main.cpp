#include <spdlog/spdlog.h>

#include "window.hpp"

int main() {
  try {
    Window window;

    if (!window.isInitialized()) {
      spdlog::error("Window failed to initialize, aborting");
      return -1;
    }

    Renderer renderer;
    Window::runEventLoop(renderer);
  } catch (...) {
    spdlog::error("Main caught unknown error");
  }
}
