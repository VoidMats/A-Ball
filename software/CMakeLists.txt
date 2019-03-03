project(sfml)

# AnvÃ¤nd C++ 14.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# PÃ¥ skolans Linux-system finns tvÃ¥ versioner av SFML. Se vilken som anvÃ¤nds:
if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/6.1.0.*"))
    set(CMAKE_CXX_COMPILER /sw/gcc-6.1.0/bin/g++)

    if (DEFINED ENV{SFML_ROOT})
        list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/share/SFML/cmake/Modules")
    endif()
endif()

# VÃ¤lj vilka delar av SFML som ska anvÃ¤ndas.
set(SFML_MODULES network graphics window system)

# FÃ¶rsÃ¶k att hitta SFML genom att anropa 'FindSFML.cmake'.
find_package(SFML 2 COMPONENTS ${SFML_MODULES})
include_directories(${SFML_INCLUDE_DIR})

# Om det inte gick hoppas vi att det Ã¤r installerat i alla fall.
if (NOT (${SFML_FOUND} STREQUAL "TRUE"))
    set(SFML_LIBRARIES "")
    foreach(i ${SFML_MODULES})
        list(APPEND SFML_LIBRARIES "sfml-${i}")
    endforeach(i)
endif()

# Ange kÃ¤llfiler, lÃ¤gg till de filer som ni behÃ¶ver!

set(SOURCE_FILES Base_Object.cpp Base_Object.h Solid_Object.cpp Solid_Object.h Game_Engine.cpp Game_Engine.h
        Brick.h Brick.cpp Ball.h Ball.cpp Key_Input.h Key_Input.cpp Play_State.h Play_State.cpp Shot.cpp Shot.h
        Textures.h Textures.cpp Score.h Score.cpp Menu_State.h Menu_State.cpp HighScore_State.cpp HighScore_State.h
        Credit_State.h Credit_State.cpp GameOver_State.h GameOver_State.cpp Duo_State.h Duo_State.cpp
        Box.h Box.cpp Player.h Player.cpp Power_Up.h Power_Up.cpp main.cpp)

# SÃ¤g till CMake att skapa en kÃ¶rbar fil som heter 'sfml'.
add_executable(sfml ${SOURCE_FILES})

# LÃ¤nka med biblioteken som vi hittade tidigare.
target_link_libraries(sfml ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
