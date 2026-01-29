cmake_minimum_required(VERSION 3.19)
project(library-management-system LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

qt_add_executable(library-management-system
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    loginscreen.h loginscreen.cpp loginscreen.ui
    menuscreen.h menuscreen.cpp menuscreen.ui
    userrepository.h
    userentity.h
    userrepository.cpp
    usermapper.h
    state.h
    schema.h
    controller.h
    controller.cpp

    screenid.h
    booksindexscreen.h booksindexscreen.cpp booksindexscreen.ui
    readercardsscreen.h readercardsscreen.cpp readercardsscreen.ui
    bookrepository.h
    bookentity.h
    entity.h
    bookmapper.h
    bookrepository.cpp
    readercardentity.h
    readercardmapper.h
    readercardrepository.h
    readercardrepository.cpp
    seed.h
    borrowingsscreen.cpp
    borrowingsscreen.h
    borrowingsscreen.ui







)

target_link_libraries(library-management-system
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

include(GNUInstallDirs)

install(TARGETS library-management-system
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET library-management-system
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
