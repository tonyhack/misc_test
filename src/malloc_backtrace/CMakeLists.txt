if (COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

FILE(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/malloc_backtrace)
set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/malloc_backtrace)

set(MALLOC_BACKTRACE_TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/src/malloc_backtrace/main.cc
    ${PROJECT_SOURCE_DIR}/src/malloc_backtrace/malloc_backtrace.cc)
add_executable(malloc_backtrace ${MALLOC_BACKTRACE_TEST_SOURCES})
target_link_libraries(malloc_backtrace)
