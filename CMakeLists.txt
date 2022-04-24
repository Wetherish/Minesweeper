#    cmake_minimum_required(VERSION 3.21)
#    project(Saper)
#
#    set(CMAKE_CXX_STANDARD 11)
#
#    add_compile_options(-Wall -Wextra)
#    add_executable(untitled main.cpp MinesweeperBoard.cpp MinesweeperBoard.h MSBoardTextView.cpp MSBoardTextView.h MSTextController.cpp MSTextController.h)

    cmake_minimum_required(VERSION 3.11)
    # Proszę zmienić wymaganą wersję CMake na niższą - wystarczy 3.11

    project(Saper)

    set(CMAKE_VERBOSE_MAKEFILE ON)
    set(CMAKE_CXX_STANDARD 14)
    add_compile_options(-Wall -Wextra)

    # ustawienia SFML-a dla Linuksa/MacOS i Windows - proszę zostawić obie konfiguracje,
    # CMake automatycznie użyje właściwej
    if (UNIX)
        # konfiguracja dla systemów Unix/Linux/MacOS
        # proszę nie modyfkować pierwszego wpisu, można dopisać kolejne katalogi
        # wpis dla antycznego Ubuntu (dla SFML 2.4)
        set ( CMAKE_MODULES_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULES_PATH})

        # katalog, w którym jest plik SFMLConfig.cmake
        # nowe Ubuntu (SFML 2.5)
        # NIE ZMIENIAĆ, NIE KASOWAĆ !!!
        set ( CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})

        # dla MacOS lub innej dystrybucji Linuksa - można dopisać DODATKOWY CMAKE_PREFIX_PATH
        # set ( CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})
    endif(UNIX)

    if (WIN32)
        # próbujemy linkować statycznie (nie trzeba kopiować plików dll do katalogu projektu)
        set( SFML_STATIC_LIBRARIES TRUE )

        # Jeśli zainstalowaliście w innym miejscu to trzeba tu zmienić katalog na właściwy
        set ( SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML/")
    endif(WIN32)


    find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

    add_executable(untitled main.cpp MinesweeperBoard.cpp MinesweeperBoard.h MSBoardTextView.cpp MSBoardTextView.h MSTextController.cpp MSTextController.h MSSFMLView.cpp MSSFMLView.h MSSFMLCONTROL.cpp MSSFMLCONTROL.h)
    target_link_libraries(untitled sfml-graphics sfml-audio)