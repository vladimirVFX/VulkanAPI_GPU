#include "vulkan\vulkan.h"	//MainLibVulkan
#include <iostream>			
#include <vector>			

//
#define ASSERT_VULKAN(val)\
		if(val != VK_SUCCESS){\
			__debugbreak();\
		}
//
VkInstance instance;
VkDevice device;
//
void printStats(VkPhysicalDevice& device)
{
	//Structure_specified_of_physical_device_properties
	VkPhysicalDeviceProperties properties;	
	vkGetPhysicalDeviceProperties(device, &properties);
	std::cout << "Name: " << properties.deviceName << std::endl;
	uint32_t apiVer = properties.apiVersion;
	std::cout << "API Version: " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << std::endl;
	std::cout << "Driver Version: " << properties.driverVersion << std::endl; 
	std::cout << "Vendor ID: " << properties.vendorID << std::endl; 
	std::cout << "Device ID: " << properties.deviceID << std::endl;
	std::cout << "Device Type: " << properties.deviceType << std::endl;
	std::cout << "discreteQueuePriorities: " << properties.limits.discreteQueuePriorities <<std::endl;
	//Structure_describing_the_fine-grained_features_that_can_be_supported_by_an_implementation
	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(device, &features);
	std::cout << "Geometry Shaider: " << features.geometryShader << std::endl;
	std::cout << "Tesselkation Shaider: " << features.tessellationShader << std::endl;
	std::cout << "Sample Rate Shaider: " << features.sampleRateShading << std::endl;
	std::cout << "Shaider Clip Distance: " << features.shaderClipDistance << std::endl;
	//
	VkPhysicalDeviceMemoryProperties memProp;
	vkGetPhysicalDeviceMemoryProperties(device, &memProp);
	std::cout << "MemoryTypes: " << memProp.memoryTypes << std::endl;
	std::cout << "MemoryHeaps: " << memProp.memoryHeaps << std::endl;
	std::cout << "MemoryTypeCount : " << memProp.memoryTypeCount << std::endl;
	std::cout << "MemoryHeapCount : " << memProp.memoryHeapCount << std::endl;
	uint32_t amountOfQueueFamilies = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies,NULL);
	VkQueueFamilyProperties* familyProperties = new VkQueueFamilyProperties[amountOfQueueFamilies];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, familyProperties);
	//
	std::cout << "Amount of Queue FamilyProperties: " << amountOfQueueFamilies << std::endl;
	for (int i = 0; i < amountOfQueueFamilies; i++)
	{
		std::cout << std::endl;
		std::cout << "Queue Family # " << i << std::endl;
		std::cout << "QueueCount: " << ((familyProperties[i].queueCount)) << std::endl;
		std::cout << "VK_QUEUE_GRAPHICS_BIT: " << ((familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) << std::endl;
		std::cout << "VK_QUEUE_COMPUTE_BIT: " << ((familyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) << std::endl;
		std::cout << "VK_QUEUE_TRANSFER_BIT: " << ((familyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) << std::endl;
		std::cout << "VK_QUEUE_SPARSE_BINDING_BIT: " << ((familyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0) << std::endl;
		//std::cout << "Timestamp Valid Bits: " << familyProperties[i].minImageTransferGranularity << std::cout;
		uint32_t width = familyProperties[i].minImageTransferGranularity.width;
		uint32_t height = familyProperties[i].minImageTransferGranularity.height;
		uint32_t depth = familyProperties[i].minImageTransferGranularity.depth;
		std::cout << "Min Image Timestamp Granularity: " << width << "," << height << "," << depth << std::endl;
	}
	std::cout << std::endl;
	delete[] familyProperties;
}
//Main_function
int main()
{
	//Application
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = "VulkanTutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Super Vulkan Engine Tutorial";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	
	//
	uint32_t amountOfLayers = 0;
	vkEnumerateInstanceLayerProperties(&amountOfLayers, NULL);
	VkLayerProperties* layers = new VkLayerProperties[amountOfLayers];
	vkEnumerateInstanceLayerProperties(&amountOfLayers, layers);
	std::cout << "Amount of Instance Layers: " << amountOfLayers << std::endl;
	for (int i = 0; i < amountOfLayers; i++)
	{
		std::cout << "Name: " << layers[i].layerName << std::endl;
		std::cout << "Spec Version: " << layers[i].specVersion << std::endl;
		std::cout << "Impl Version: " << layers[i].implementationVersion << std::endl;
		std::cout << "Description: " << layers[i].description << std::endl;
		std::cout << "\n" << std::endl;
	}

	const std::vector<const char*> validationLayers = {

	};

	//Instance
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
	//
	for (int i = 0; i < amountOfPhysicalDevices; i++)
	{
		printStats(physicalDevices[i]);
	}
	//Queue
	VkDeviceQueueCreateInfo deviceQueueCreateInfo;
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.pNext = NULL;
	deviceQueueCreateInfo.flags = 0;
	deviceQueueCreateInfo.queueFamilyIndex = 0; //TODO Choose correct family index
	deviceQueueCreateInfo.queueCount = 4; //TODO Check if this amount is valid 
	deviceQueueCreateInfo.pQueuePriorities = NULL;
	//
	VkPhysicalDeviceFeatures usedFeatures = {};
	//Device
	VkDeviceCreateInfo deviceCreateInfo;
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pNext = NULL;
	deviceCreateInfo.flags = 0;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.enabledExtensionCount = 0;
	deviceCreateInfo.ppEnabledExtensionNames = NULL;
	deviceCreateInfo.pEnabledFeatures = &usedFeatures;

	//TODO pick "best device" instead of first device
	result = vkCreateDevice(physicalDevices[0], &deviceCreateInfo, NULL, &device);
	ASSERT_VULKAN(result);

	return 0;
}
