#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include <algorithm>
#include <string>
#include <vector>

#include "nile/app/assert.hpp"

const std::vector<const char*> DEBUG_LAYERS = {"VK_LAYER_KHRONOS_validation"};

struct RendererOptions {
  bool useDebugLayers;
  std::vector<std::string> extensions;
};

struct InstanceInfo {
  VkInstance instance;
};

class Renderer {
 private:
  InstanceInfo instanceInfo;

  InstanceInfo createInstance(RendererOptions& options) {
    VkApplicationInfo applicationInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = NULL,
        .pApplicationName = "Nile",
        .applicationVersion = 1,
        .pEngineName = "vulkan engine",
        .apiVersion = VK_API_VERSION_1_3,
    };

    std::vector<const char*> extensions(options.extensions.size());
    std::transform(options.extensions.begin(), options.extensions.end(),
                   extensions.begin(),
                   [](const std::string& str) { return str.c_str(); });
    extensions.push_back(
        VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    for (auto& extension : extensions) {
      spdlog::debug("Using extension: {}", extension);
    }

    std::vector<const char*> layers;
    if (options.useDebugLayers) {
      layers.insert(layers.end(), DEBUG_LAYERS.begin(), DEBUG_LAYERS.end());
    }

    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = NULL,
        .pApplicationInfo = &applicationInfo,
        .enabledExtensionCount =
            static_cast<uint32_t>(options.extensions.size()),
        .ppEnabledExtensionNames = extensions.data(),
        .enabledLayerCount = static_cast<uint32_t>(layers.size()),
        .ppEnabledLayerNames = layers.data(),
        .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
    };

    InstanceInfo instanceInfo;
    assertVkResult(
        vkCreateInstance(&instanceCreateInfo, NULL, &instanceInfo.instance),
        "Create Vulkan Instance");

    return instanceInfo;
  }

 public:
  Renderer(RendererOptions& options) { instanceInfo = createInstance(options); }

  void render() {}
};