# CMakeList.txt : CMake project for CppMemoryExercise, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CppMemoryExercise "CppMemoryExercise.cpp" "CppMemoryExercise.h" "JsonParser.h" "JsonParser.cpp")

target_include_directories(CppMemoryExercise PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CppMemoryExercise PRIVATE winlibs)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CppMemoryExercise PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
