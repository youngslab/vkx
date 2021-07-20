

#include <vkx/Enumerate.hpp>
#include <vulkan/vulkan_core.h>

namespace vkx {

auto EnumeratePhysicalDevices(VkInstance instance)
    -> std::vector<VkPhysicalDevice> {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  return devices;
}

auto EnumerateInstanceExtensionProperties(const char *pLayerName)
    -> std::vector<VkExtensionProperties> {
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(pLayerName, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(pLayerName, &extensionCount,
					 extensions.data());

  return extensions;
}

auto EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
					const char *pLayerName)
    -> std::vector<VkExtensionProperties> {

  uint32_t extensionCount = 0;
  vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName,
				       &extensionCount, nullptr);

  // Populate list of extensions
  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName,
				       &extensionCount, extensions.data());

  return extensions;
}

auto EnumerateInstanceLayerProperties() -> std::vector<VkLayerProperties> {

  // Get number of validation layers to create vector of appropriate size
  uint32_t validationLayerCount = 0;
  vkEnumerateInstanceLayerProperties(&validationLayerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(validationLayerCount);
  vkEnumerateInstanceLayerProperties(&validationLayerCount,
				     availableLayers.data());

  return availableLayers;
}
} // namespace vkx
