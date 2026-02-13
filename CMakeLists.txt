cmake_minimum_required(VERSION 3.16)
project(core-utils VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_UTILS_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(core-utils STATIC ${CORE_UTILS_SOURCES})

target_include_directories(core-utils
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

target_compile_features(core-utils PUBLIC cxx_std_17)

set_target_properties(core-utils PROPERTIES OUTPUT_NAME "core-utils")

include(GNUInstallDirs)
install(TARGETS core-utils
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

option(BUILD_CORE_UTILS_EXAMPLES "Build examples for core-utils" OFF)

