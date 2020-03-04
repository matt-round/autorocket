cmake_minimum_required(VERSION 3.14)
project(Rslr)

set(CMAKE_CXX_STANDARD 17)

# Tell cmake where Qt is located
set(Qt5_DIR "~/Qt/5.14.1/clang_64/lib/cmake/Qt5")

# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(Rslr src/main.cpp src/env/gui/MainWindow.cpp src/env/gui/MainWindow.h)

# Link the library to the executable
target_link_libraries(Rslr Qt5::Core Qt5::Widgets)