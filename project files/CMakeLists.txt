cmake_minimum_required(VERSION 3.24)
project(a89_Rares1707)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.5.0\\mingw_64\\lib\\cmake\\")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Charts
        Widgets
        REQUIRED)

include_directories(.)

add_executable(a89_Rares1707
        AdoptionList.cpp
        AdoptionList.h
        "assemble the application.cpp"
        CSV_AdoptionList.cpp
        CSV_AdoptionList.h
        Dog.cpp
        Dog.h
        DogValidator.cpp
        DogValidator.h
        FileAdoptionList.cpp
        FileAdoptionList.h
        HTML_AdoptionList.cpp
        HTML_AdoptionList.h
        RepositoryExceptions.cpp
        RepositoryExceptions.h
        Services.cpp
        Services.h
        TextFileRepository.cpp
        TextFileRepository.h
        AdministratorGUI.cpp AdministratorGUI.h SelectModeGUI.cpp SelectModeGUI.h SelectModeGUI.ui UserModeGUI.cpp UserModeGUI.h UserModeGUI.ui)

target_link_libraries(a89_Rares1707
        Qt::Core
        Qt::Gui
        Qt::Charts
        Qt::Widgets)

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
