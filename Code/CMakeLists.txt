cmake_minimum_required(VERSION 3.20)
project(VulkanFramework)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Automatically include the source files in the project
aux_source_directory(. SRC_LIST)

# fetch the vulkan sdk path from the environment variable
set(VULKAN_SDK_PATH $ENV{VULKAN_SDK})

# find header files 
include_directories(
	SYSTEM ${VULKAN_SDK_PATH}/include
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLFW/include
)

# find library files
link_directories(
	${VULKAN_SDK_PATH}/lib
	${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLFW/lib
)

# Add the executable target
add_executable(VulkanFramework ${SRC_LIST})
target_link_libraries(VulkanFramework 
	vulkan-1.lib
	glfw3.lib
)