cmake_minimum_required(VERSION 4.1)
project(Fracture)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
		Hollow
		GIT_REPOSITORY https://github.com/V3rdantM0ss/Hollow.git
		GIT_TAG 0.1.3.0
		GIT_SHALLOW ON
		EXCLUDE_FROM_ALL
		SYSTEM
)
FetchContent_Declare(
		SFML
		GIT_REPOSITORY https://github.com/SFML/SFML.git
		GIT_TAG 3.0.2
		GIT_SHALLOW ON
		EXCLUDE_FROM_ALL
		SYSTEM
)
FetchContent_MakeAvailable(Hollow)
FetchContent_MakeAvailable(SFML)
add_library(Fracture STATIC
		source/Fracture.cpp
		source/Logic.cpp
)
target_include_directories(Fracture PUBLIC include)
target_link_libraries(Fracture PUBLIC
		Hollow
		SFML::Graphics)
add_executable(FractureTest TestFracture.cpp)
target_link_libraries(FractureTest PUBLIC
		Hollow
		Fracture
		SFML::Graphics
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)