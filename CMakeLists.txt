cmake_minimum_required(VERSION 3.0.0)
project(GamePlate VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-findsdl/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(GamePlate main.c sources/Checker/mainChecker.c sources/Checker/checkerGame.c sources/Checker/bases.c sources/Checker/interface.c sources/Tic-Tac-Toe/Game.c sources/Tic-Tac-Toe/Logic.c sources/Tic-Tac-Toe/Rendering.c sources/base/window.c)
target_link_libraries(GamePlate ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)