cmake_minimum_required(VERSION 3.21.2)

project(SProject VERSION 0.0.1)

set(VKMGL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party/vkmGL)

add_subdirectory(${VKMGL_DIR})

set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/action_handle/action_handle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/all_handle/all_handle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/define_handle/define_handle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/solve_handle/solve_handle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/string_handle/string_handle.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/src/string_handle/string_handle.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/src/common/file/file_handle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/post.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/string_array.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/src/render/ui/console/console.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/ui/contoller/controller.cpp

	main.cpp
)

set(HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/action_handle
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/all_handle
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/define_handle
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_handle/solve_handle
	${CMAKE_CURRENT_SOURCE_DIR}/src/string_handle

	${CMAKE_CURRENT_SOURCE_DIR}/src/common/file
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/hash_map
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/pair
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/stack
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/tree
	${CMAKE_CURRENT_SOURCE_DIR}/src/common

	${CMAKE_CURRENT_SOURCE_DIR}/src/render/renderer
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/ui/console
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/ui/contoller
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/ui
	${CMAKE_CURRENT_SOURCE_DIR}/src/render
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
	${VKMGL_DIR}/common
	${VKMGL_DIR}/common/error
	${VKMGL_DIR}/core

	${HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	vkmGL
)
