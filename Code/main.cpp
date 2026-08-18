#define GLFW_INCLUDE_VULKAN
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "vulkan/vulkan.h"

#include <iostream>

int main()
{
	// Test glm
	glm::vec3 testVec(1.0f, 2.0f, 3.0f);
	std::printf("Test glm::vec3: (%f, %f, %f)\n", testVec.x, testVec.y, testVec.z);

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_API_VERSION_1_4;
	appInfo.pApplicationName = "Vulkan App";

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	VkInstance instance;
	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	if (result != VK_SUCCESS)
	{
		std::cerr << "Failed to create Vulkan instance: " << result << std::endl;
		return -1;
	}

	std::cout << "Vulkan instance created successfully." << std::endl;
	return 0;
}