cmake_minimum_required(VERSION 3.20)
project(TestSystem)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/")
set(GSL_ROOT_DIR "C:/cygwin64")

find_package(GSL REQUIRED)

find_package(Qt5 COMPONENTS
        Widgets
        AxContainer
        Core
        Gui
        PrintSupport
        REQUIRED)

add_executable(TestSystem
        qcustomplot.cpp qcustomplot.h
        testui.cpp testui.h
        DataStorage.cpp DataStorage.h
        IWidget.cpp IWidget.h
        MainMenu.cpp MainMenu.h
        Visualisation.cpp Visualisation.h
        Reactor.cpp Reactor.h
        Solver.cpp Solver.h
        )

target_link_libraries(TestSystem GSL::gsl GSL::gslcblas)
target_link_libraries(TestSystem Qt5::Widgets Qt5::AxContainer Qt5::Core Qt5::Gui Qt5::PrintSupport)

#[[if (WIN32)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB
            Widgets
            Core
            Gui
            PrintSupport
            )
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()]]
