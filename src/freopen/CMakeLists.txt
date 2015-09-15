if (COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

FILE(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/freopen)
set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/freopen)

set(FREOPEN_TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/src/freopen/freopen.cc)
add_executable(freopen ${FREOPEN_TEST_SOURCES})
target_link_libraries(freopen)
