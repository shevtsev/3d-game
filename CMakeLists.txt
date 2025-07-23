cmake_minimum_required(VERSION 3.10)
project(Pseudo3DGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавляем флаги компиляции
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem /Library/Developer/CommandLineTools/usr/include/c++/v1")
    include_directories(/Library/Developer/CommandLineTools/usr/include/c++/v1)
endif()

# Найти SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Добавить исходные файлы
set(SOURCES
    "${CMAKE_SOURCE_DIR}/3d-game/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/3d-game/src/Game_start.cpp"
    "${CMAKE_SOURCE_DIR}/3d-game/src/Init_game.cpp"
    "${CMAKE_SOURCE_DIR}/3d-game/src/Move_player.cpp"
)

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Добавить путь к заголовочным файлам
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3d-game/Headers
    /usr/local/include
    /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
)

# Подключить SFML
target_link_libraries(${PROJECT_NAME} 
    sfml-graphics 
    sfml-window 
    sfml-system
)