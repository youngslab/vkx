# VKX

This library is a RAII wrapper and provides some utiltiies.

The goal of this library is minimum impact on modifying existing application. You can easily change vulkan types as following steps.

1. Change the types.
2. Change the create functions (*almost all are same with parameters except for a few functions).
3. Delete destroy functions.

For example,

```cpp
VkInstanceCreateInfo createInfo = {};

// Before
vkInstance instance;
VkResult result = vkCreateInstance(&createInfo, pAllocator, &instance);
vkDestroyInstance(instance, pAllocator);

// After
// 1. Change a type.
vkx::Instance instance;
// 2. Change a create function.
VkResult result = vkx::CreateInstance(&createInfo, pAllocator, &instance);
```

## Dependency Management

Each RAII objects has its own dependencies. For example, `VkDescriptorSet` depends on `VkDescriptorPool` which means that `VkDescriptorSet` should be removed before removing `VkDescirptorPool`. VKX make its dependency when the wrapper object create. Unfortunately, for a few cases, original Create function's parameters are not enough to make all the dependencies. So VKX might requires more parameters than vulkan create functions for the special case.

```cpp
VkResult AllocateDescriptorSets(
	Device const &device,
	DescriptorPool const &descriptorPool,   // An additional paramenter
	const VkDescriptorSetAllocateInfo *pAllocateInfo,
	DescriptorSet *pDescriptorSets);

VkResult vkAllocateDescriptorSets(
    VkDevice                                    device,
    const VkDescriptorSetAllocateInfo*          pAllocateInfo,
    VkDescriptorSet*                            pDescriptorSets);
```

## Specify multiple objects in CreateInfo structure

When specify multiple objects to pass vulkan functions, we need to convert wrapper objects to vulkan objects. For example, Let's see the `VkSumitInfo`.  We have couple of  command buffers and  we summit one of them or all at once.

```cpp

VkSubmitInfo submitInfo = {};
submitInfo.pCommandBuffers = ??
```

### Case 1.  Submissions of one command buffer

We can specify the pointer from wrapper object like below.

```cpp
vkx::CommandBuffer cmdBuff;

// Case1. There is only one command buffer to summit.
submitInfo.pCommandBuffers = cmdBuff.GetPointer();
```

or we can convert it as a vector
```cpp
vkx::CommandBuffer cmdBuff;
std::vector<VkCommandBuffer> nativeBuffers = vkx::ToNativeVector(cmdBuff);
submitInfo.pCommandBuffers = nativeBuffers.data(); 
```



### Case 2. Multiple command buffers

In this case, we have to specify the array pointer of the vulkan type. To do that, we could convert our vector of the wrapper object to vulkan object. VKX provides a helper function namely `ConvertNative` .

```cpp
std::vector<vkx::CommandBuffer> cmdBuffs;
std::vector<VkCommandBuffer> nativeBuffers = vkx::ConvertNative(cmdBuffs);
submitInfo.pCommandBuffers = nativeBuffers.data();
```

# WSI

VKX abstract its platform as `vkx::Window` (`GLFW*` type) by using GLFW. VKX adds new Window APIs like below. Each APIs call glfw functions at last. This window type's lifetime is also managed by VKX. You don't need to specify delete functions for the window.

- `vkx::CreateWindow`  → glfwCreateWindow
- `vkx::CreateSurfaceKHR` → glfwCreateWindowSurface

```cpp
// vkx::Window => vkx::Object<GLFWwindow*>;
vkx::Window window;

glfwInit();
glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

vkx::CreateWindow(width, height, appName, &window);

while (!glfwWindowShouldClose(window)) {
  glfwPollEvents();
  // render loop
}

glfwTerminate();
```

# How to build

```
mkdir build
cmake -B ./build -DCMAKE_EXPORT_COMPILE_COMMANDS=y -GNinja -DCMAKE_BUILD_TYPE=Debug
ninja -C ./build
```
