cmake_minimum_required(VERSION 3.16)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all>=2.1)

# Add executable
add_executable(space_shooter 
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Bullet.cpp
)

# Include directories
target_include_directories(space_shooter PRIVATE include ${SFML_INCLUDE_DIRS})

# Link SFML
target_link_libraries(space_shooter ${SFML_LIBRARIES})

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})