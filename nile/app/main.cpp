#include <spdlog/spdlog.h>

#include "nile/app/window.hpp"

int main() {
  try {
    // TODO: configurable
    spdlog::set_level(spdlog::level::debug);

    Window window;
    if (!window.isInitialized()) {
      throw std::runtime_error("Window failed to initialize, aborting");
    }
    
    spdlog::info("Getting Vulkan extensions");
    auto extensions = window.getVulkanInstanceExtensions();
    if (!extensions.has_value()) {
      throw std::runtime_error("Cannot acquire Vulkan extensions");
    }

    RendererOptions rendererOptions = {
      .useDebugLayers = true,
      .extensions = extensions.value(),
    };

    Renderer renderer(rendererOptions);
    Window::runEventLoop(renderer);
  } catch (std::exception& exception) {
    spdlog::error("An Error has ocured: {}", exception.what());
  } catch (...) {
    spdlog::error("Main caught unknown error");
  }
}
