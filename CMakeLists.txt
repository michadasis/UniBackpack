cmake_minimum_required(VERSION 3.16)
project(UniBackpack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network LinguistTools)

set(CMAKE_AUTOMOC ON) # Handles Signals/Slots
set(CMAKE_AUTORCC ON) # Handles .qrc resource files
set(CMAKE_AUTOUIC ON) # Handles .ui files

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

add_executable(UniBackpack
        # Source files
        src/main.cpp
        src/Downloader.cpp
        src/MainWindow.cpp

        # Header files
        include/MainWindow.hpp
        include/Downloader.hpp

        # UI
        ui/MainWindow.ui

        # Resources
        resources/resources.qrc
)

target_include_directories(UniBackpack PRIVATE include)

target_link_libraries(UniBackpack PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
)

# --- Internationalization (i18n) ---
# Compiles .ts -> .qm and embeds them under ":/i18n/" automatically.
# Run "cmake --build build --target update_translations" to populate .ts from tr() strings.
qt_add_translations(UniBackpack
        TS_FILES
        translations/unibackpack_en.ts
        translations/unibackpack_el.ts
)

install(TARGETS UniBackpack DESTINATION bin)

# CPack configuration to generate the Debian installer (.deb)
set(CPACK_PACKAGE_NAME "unibackpack")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_RELEASE "1")
set(CPACK_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_PACKAGE_CONTACT "Apostolos Chalis")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Qt6 downloader for software used by Greek universities")
set(CPACK_GENERATOR "DEB")
include(CPack)