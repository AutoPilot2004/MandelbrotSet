cmake_minimum_required(VERSION 3.8)

project("Lib")

find_package(glfw3 CONFIG REQUIRED)

add_library(
    ${PROJECT_NAME}
    "Window.cpp"
    "vendor/glad/src/glad.c"
    "Core.cpp"
    "ShaderProgram.cpp"
    "VertexArray.cpp"
    "Renderer.cpp"
    "Texture1D.cpp"
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/glad/include")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)