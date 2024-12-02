cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(SFML_DIR "C:/SFML/SFML-2.6.2")

project ("Quizz")

# Définir le fichier de police
set(FONT_FILES ${PROJECT_SOURCE_DIR}/fonts/arial.ttf)

# Copier le fichier de police dans le répertoire de construction
foreach(FONT_FILE ${FONT_FILES})
    configure_file(${FONT_FILE} ${CMAKE_BINARY_DIR}/fonts/ COPYONLY)
endforeach()

# Inclure les répertoires d'en-tête
include_directories(src)
include_directories("${SFML_DIR}/include")
link_directories("${SFML_DIR}/lib")

# Collecter tous les fichiers source dans le dossier src
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Ajouter l'exécutable
add_executable(Quizz ${SOURCES})

# Lier les bibliothèques SFML
set(SFML_LIBRARIES sfml-graphics-d sfml-window-d sfml-system-d)
target_link_libraries(Quizz ${SFML_LIBRARIES})


# Spécifier la version C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Quizz PROPERTY CXX_STANDARD 20)
endif()
