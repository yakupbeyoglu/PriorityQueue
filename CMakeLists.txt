cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0054 NEW)

set(PROJECT_NAME "PriortyQueue")

project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Bin)


option(TESTS "Enable unit tests" ON)
option(DOCS "BUILD DOCS" OFF)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# Include Source directory as a subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Add Source directory to include paths
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

get_target_property(INCLUDE_DIRS ${PROJECT_NAME} INCLUDE_DIRECTORIES)
message("Include directories for ${PROJECT_NAME}: ${INCLUDE_DIRS}")
if(TESTS)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Tests/)
enable_testing()
endif(TESTS)

if(DOCS)
find_package(Doxygen REQUIRED)
find_package(Doxygen REQUIRED dot)

set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Docs/)

  set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
  set(DOXYGEN_CALL_GRAPH YES)
  set(DOXYGEN_CALLER_GRAPH YES)
  set(DOXYGEN_WARN_AS_ERROR YES)
  set(DOXYGEN_SOURCE_BROWSER YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_SORT_MEMBER_DOCS NO)
  set(DOXYGEN_FILE_PATTERNS *.cpp *.h *.hpp)
  set(DOXYGEN_EXCLUDE_PATTERNS */Bin/* */build/* */Tests/* *.cc main.cpp)

  doxygen_add_docs(
      doxygen_doc
      ALL
      ${CMAKE_CURRENT_LIST_DIR}
      COMMENT "Generate doxygen documentation for ${PROJECT_NAME}"
  )
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Docs/)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_EXTRACT_ALL YES)
message("Doxygen output directory: ${DOXYGEN_OUTPUT_DIRECTORY}")

doxygen_add_docs(
    doc
    ${CMAKE_SOURCE_DIR}/Source/priority_queue.hpp
    COMMENT "Generating API documentation with Doxygen"
)
endif(DOCS)
