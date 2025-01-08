#!/bin/bash

export VULKAN_SDK=${VULKAN_SDK:-~/VulkanSDK/1.3.296.0/macOS}
export PATH=$VULKAN_SDK/bin:$PATH
export DYLD_LIBRARY_PATH=$VULKAN_SDK/lib:$DYLD_LIBRARY_PATH
export VK_ICD_FILENAMES=$VULKAN_SDK/share/vulkan/icd.d/MoltenVK_icd.json
export VK_LAYER_PATH=$VULKAN_SDK/share/vulkan/explicit_layer.d

echo "VULKAN_SDK: $VULKAN_SDK"
echo "DYLD_LIBRARY_PATH: $DYLD_LIBRARY_PATH"
echo "VK_ICD_FILENAMES: $VK_ICD_FILENAMES"
echo "VK_LAYER_PATH: $VK_LAYER_PATH"