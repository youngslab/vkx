
cmake_minimum_required(VERSION 3.14)

project(vkx)

find_package(Vulkan REQUIRED)
find_package(glfw REQUIRED)

add_library(vkx ./src/Create.cpp )
target_link_libraries(vkx PUBLIC Vulkan::Vulkan glfw::glfw)
target_include_directories(vkx PUBLIC ./include)
set_target_properties(vkx PROPERTIES
            CXX_STANDARD 17)

if(PRINT_LOG)
	target_compile_definitions(vkx PUBLIC -DVKX_PRINT_LOG)
endif()
