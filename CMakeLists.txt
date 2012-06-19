# Ajustez en fonction de votre version de CMake
cmake_minimum_required (VERSION 2.8)

# Nom du projet
project (solveMath)


find_package (OpenCV REQUIRED)

# Exécutable "hello", compilé à partir du fichier helloworld.c
add_executable (solveMath main.c)

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
    set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
    #SET(CMAKE_C_FLAGS "-lccgi")
endif()

# Hello sera linké avec les bibliothèques d'OpenCV
target_link_libraries (solveMath ${OpenCV_LIBS})
