#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

namespace vkx {

auto EnumeratePhysicalDevices(VkInstance instance)
    -> std::vector<VkPhysicalDevice>;

auto EnumerateInstanceExtensionProperties(const char *pLayerName)
    -> std::vector<VkExtensionProperties>;

auto EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
					const char *pLayerName)
    -> std::vector<VkExtensionProperties>;

auto EnumerateInstanceLayerProperties() -> std::vector<VkLayerProperties>;
} // namespace vkx
