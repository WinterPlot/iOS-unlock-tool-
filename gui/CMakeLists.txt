set(APP_SOURCES
    main.cpp
    MainWindow.cpp
    MainWindow.h
    Theme.cpp
    Theme.h
    widgets/AppButton.cpp
    widgets/AppButton.h
    widgets/Toast.cpp
    widgets/Toast.h
    widgets/StatusCard.cpp
    widgets/StatusCard.h
)

add_executable(tr4mpass-gui ${APP_SOURCES})
target_include_directories(tr4mpass-gui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tr4mpass-gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if (WIN32)
    set_target_properties(tr4mpass-gui PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if (APPLE)
    set_target_properties(tr4mpass-gui PROPERTIES MACOSX_BUNDLE TRUE)
endif()
