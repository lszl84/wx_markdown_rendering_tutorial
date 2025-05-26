cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(wx_markdown_rendering_tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(wxBUILD_SHARED OFF)

FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG 3e6b6647628c944ba9d5e599d599081e58ad2ac4
)

FetchContent_Declare(
    cmark
    GIT_REPOSITORY https://github.com/commonmark/cmark.git
    GIT_TAG 0.31.1
)

FetchContent_MakeAvailable(wxWidgets cmark)

set(SRCS main.cpp)

if(APPLE)
    add_executable(main MACOSX_BUNDLE ${SRCS})
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # WIN32 needed for Windows to look for WinMain instead of main
    # Include manifest file for Windows builds for correct DPI scaling
    # Note: this is safe on Linux.
    add_executable(main WIN32 ${SRCS} main.exe.manifest)
endif()

target_link_libraries(main PRIVATE wxbase wxcore wxhtml cmark)


