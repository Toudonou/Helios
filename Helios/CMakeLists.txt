cmake_minimum_required(VERSION 3.28)
project(Helios)

set(CMAKE_CXX_STANDARD 20)

# Include the third-party libraries
include_directories(third-party/include)
# Link the third-party libraries
link_directories(third-party/lib)

# Include the engine libraries
include_directories(Helios/include/)

add_executable(${PROJECT_NAME}
        third-party/src/glad.c
        main.cpp
        Helios/include/Helios/core/defines.h
        Helios/include/Helios/core/log.h
        Helios/src/Helios/core/Engine.cpp
        Helios/include/Helios/core/Engine.h
        Helios/src/Helios/core/Logger.cpp
        Helios/include/Helios/core/Logger.h
        Helios/src/Helios/core/Window.cpp
        Helios/include/Helios/core/Window.h
        Helios/src/Helios/input/Input.cpp
        Helios/include/Helios/input/Input.h
)

target_link_libraries(${PROJECT_NAME} glfw3 opengl32)

# Set a custom name for the DLL
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        OUTPUT_NAME "helios"
#        PREFIX ""  # This removes the 'lib' prefix on Unix-like systems
#)


#add_custom_command(
#        TARGET ${PROJECT_NAME}
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "E:/Dev/game-engine/Helios/Helios/cmake-build-debug/helios.dll" "E:/Dev/game-engine/Sandbox/cmake-build-debug/"
#        COMMENT "Copying specified files to destination directory after build"
#)
#
#add_custom_command(
#        TARGET ${PROJECT_NAME}
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "E:/Dev/game-engine/Helios/Helios/cmake-build-debug/helios.dll" "E:/Dev/game-engine/Sandbox/lib/"
#        COMMENT "Copying specified files to destination directory after build"
#)
#
#add_custom_command(
#        TARGET ${PROJECT_NAME}
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "E:/Dev/game-engine/Helios/Helios/include/Helios" "E:/Dev/game-engine/Sandbox/include/"
#        COMMENT "Copying header files to destination directory after build"
#)