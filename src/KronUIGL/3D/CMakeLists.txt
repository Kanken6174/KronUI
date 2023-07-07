set(CMAKE_CXX_STANDARD 17)

set(3D_SRC
    ./entity.hpp
    ./modelEntity.cpp
    ./modelEntity.hpp)

set(glm_DIR /usr/include/glm)
find_package(glm REQUIRED)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(Assimp_DIR /usr/lib/x86_64-linux-gnu/cmake/assimp-5.2/)
find_package(assimp REQUIRED)

add_library(3D ${3D_SRC})

add_subdirectory(Vision)
add_subdirectory(Elements)

set_target_properties(3D PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(3D PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(3D GLEW)
target_link_libraries(3D glfw)
target_link_libraries(3D assimp)
target_link_libraries(3D vision)
target_link_libraries(3D elements)