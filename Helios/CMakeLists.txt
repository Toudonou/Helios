cmake_minimum_required(VERSION 3.28)
project(Helios)

set(CMAKE_CXX_STANDARD 20)

# Include the third-party libraries
include_directories(third-party/include/)
# Link the third-party libraries
link_directories(third-party/lib)

add_library(Helios SHARED
        third-party/src/glad.c
        Helios/core/defines.h
        Helios/core/log.h
        Helios/core/Engine.cpp
        Helios/core/Engine.h
        Helios/core/Logger.cpp
        Helios/core/Logger.h
        Helios/core/Window.cpp
        Helios/core/Window.h
        Helios/input/Input.cpp
        Helios/input/Input.h
        Helios/maths/Vector2.cpp
        Helios/maths/Vector2.h
        Helios/maths/maths.h
        Helios/maths/Vector3.cpp
        Helios/maths/Vector3.h
        Helios/maths/Vector4.cpp
        Helios/maths/Vector4.h
        Helios/maths/Matrix4.cpp
        Helios/maths/Matrix4.h
        Helios/2D/Transform2D.cpp
        Helios/2D/Transform2D.h
        Helios/asset/Asset.h
        Helios/asset/AssetsManager.cpp
        Helios/asset/AssetsManager.h
        Helios/2D/Renderer2D.cpp
        Helios/2D/Renderer2D.h
        Helios/shader/Shader.cpp
        Helios/shader/Shader.h
        Helios/utils/FileUtils.cpp
        Helios/utils/FileUtils.h
        Helios/maths/Color.h
        Helios/maths/Size.h
        Helios/2D/node/Node2D.h
        Helios/2D/node/Sprite2D.cpp
        Helios/2D/node/Sprite2D.h
        Helios/asset/Texture.cpp
        Helios/asset/Texture.h
        Helios/maths/Color.cpp
)

target_link_libraries(Helios glfw3 opengl32)

# This line ensures that the directory containing the Helios.dll source files
# is added to the include path for both the Helios.dll target and any other
# targets that link against Helios.dll.
target_include_directories(Helios PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# Add custom command to copy DLL after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-build-debug/Sandbox/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)
