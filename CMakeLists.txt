# НАСТРОЙКИ CMAKE
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# Экспортировать комманды компилятора, если проект имеет статус "Debug"
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXPORT_COMPILE_COMMANDS)
endif()


# =============================================

# Настройки проекта

project(reaction_parser LANGUAGES CXX)


add_library(reaction_parser STATIC)

# Подключение директории с исходным кодом
target_include_directories(
    reaction_parser PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
                        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
)

set_target_properties(
    reaction_parser
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED on
               CXX_EXTENSIONS off
)
# =============================================
# Добавление поддиректорий и сторонних библиотек
add_subdirectory(source)
