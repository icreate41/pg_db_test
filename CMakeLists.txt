cmake_minimum_required(VERSION 3.16.3)

# Настройка компилятора: стандарт C++17
project(pg_db_test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем предупреждения компилятора
add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

# Поиск обязательной библиотеки libpq
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# Создаём исполняемый файл из исходников
add_executable(pg_db_test
    main.cpp
    src/Database.cpp
    src/Schema.cpp
)

# подключаем include пути для этого target
target_include_directories(pg_db_test PRIVATE
    include
    ${LIBPQXX_INCLUDE_DIRS}
)

# линковка с libpqxx
target_link_libraries(pg_db_test PRIVATE ${LIBPQXX_LIBRARIES})