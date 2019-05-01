//Main_lib
#include "vulkan\vulkan.h"
#include <iostream>

//
#define ASSERT_VULKAN(val)\
		if(val != VK_SUCCESS){\
			__debugbreak();\
		}

//
VkInstance instance;

//
void printStats(VkPhysicalDevice& device)
{
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(device, &properties);

	std::cout << "Name: " << properties.deviceName << std::endl;
	uint32_t apiVer = properties.apiVersion;
	std::cout << "API Version: " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << std::endl;
	std::cout << "Driver Version: " << properties.driverVersion << std::endl;
	std::cout << "Vendor ID: " << properties.vendorID << std::endl;
	std::cout << "Device ID: " << properties.deviceID << std::endl;
	std::cout << "Device Type: " << properties.deviceType << std::endl;

	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(device, &features);
	std::cout << "Geometry Shaider: " << features.geometryShader << std::endl;
	std::cout << "Tesselkation Shaider: " << features.tessellationShader << std::endl;
	std::cout << "Sample Rate Shaider: " << features.sampleRateShading << std::endl;
	std::cout << "Shaider Clip Distance: " << features.shaderClipDistance << std::endl;

	VkPhysicalDeviceMemoryProperties memProp;
	vkGetPhysicalDeviceMemoryProperties(device, &memProp);
	std::cout << "MemoryTypes: " << memProp.memoryTypes << std::endl;
	std::cout << "MemoryHeaps: " << memProp.memoryHeaps << std::endl;
	std::cout << "MemoryTypeCount : " << memProp.memoryTypeCount << std::endl;
	std::cout << "MemoryHeapCount : " << memProp.memoryHeapCount << std::endl;
	std::cout << std::endl;
}

//Main_function
int main()
{
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = "VulkanTutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Super Vulkan Engine Tutorial";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	//
	VkInstanceCreateInfo InstanceInfo = {};
	InstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceInfo.pNext = NULL;
	InstanceInfo.flags = 0;
	InstanceInfo.pApplicationInfo = &appInfo;
	InstanceInfo.enabledLayerCount = 0;
	InstanceInfo.ppEnabledLayerNames = NULL;
	InstanceInfo.enabledExtensionCount = 0;
	InstanceInfo.ppEnabledExtensionNames = NULL;

	//
	VkResult result = vkCreateInstance(&InstanceInfo, NULL, &instance);

	//
	ASSERT_VULKAN(result);
	uint32_t amountOfPhysicalDevices = 0;
	result = vkEnumeratePhysicalDevices(instance, &amountOfPhysicalDevices, NULL);
	ASSERT_VULKAN(result);

	//
	VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];

	//
	result = vkEnumeratePhysicalDevices(instance, &amountOfPhysicalDevices, physicalDevices);
	ASSERT_VULKAN(result)

		//
		std::cout << amountOfPhysicalDevices;

	for (int i = 0; i < amountOfPhysicalDevices; i++)
	{
		printStats(physicalDevices[i]);
	}

	return 0;
}
