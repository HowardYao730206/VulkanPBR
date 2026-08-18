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

set(SLANGC ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/slang/bin/slangc.exe)

# find shader file folder
set(SHADER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(SHADER_OUTPUT_DIR ${SHADER_SRC_DIR}/spv)

file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

# slangc slang-file -entrypoint -stage -o output.spv
function(compile_slang SLANG_FILE ENTRY STAGE OUTPUT_SPV)
	add_custom_command(
		OUTPUT ${OUTPUT_SPV}
		COMMAND ${SLANGC} ${SLANG_FILE} -entry ${ENTRY} -stage ${STAGE} -o ${OUTPUT_SPV}
		DEPENDS ${SLANG_FILE}
	)

endfunction()

file(GLOB SLANG_FILES ${SHADER_SRC_DIR}/*.slang)

set(SPV_FILES)

foreach(SLANG_FILE ${SLANG_FILES})
	get_filename_component(FILE_NAME ${SLANG_FILE} NAME_WE)

	# contruct output path for vertex and fragment shader
	set(VERT_SPV ${SHADER_OUTPUT_DIR}/${FILE_NAME}_vert.spv)
	set(FRAG_SPV ${SHADER_OUTPUT_DIR}/${FILE_NAME}_frag.spv)

	# call the above function twice 
	compile_slang(${SLANG_FILE} vertMain vertex ${VERT_SPV})
	compile_slang(${SLANG_FILE} fragMain fragment ${FRAG_SPV})

	# add the output spv files to the list
	list(APPEND SPV_FILES ${VERT_SPV} ${FRAG_SPV})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SPV_FILES})

# Add the executable target
add_executable(VulkanFramework ${SRC_LIST})
target_link_libraries(VulkanFramework 
	vulkan-1.lib
	glfw3.lib
)


add_dependencies(VulkanFramework Shaders)

add_custom_command(TARGET VulkanFramework POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${SHADER_OUTPUT_DIR}
		$<TARGET_FILE_DIR:VulkanFramework>/shaders
)