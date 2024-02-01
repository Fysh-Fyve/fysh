# https://lesleylai.info/en/unit-test-with-cmake/
set(DOCTEST_INCLUDE_DIR .)
add_library(DocTest INTERFACE)
target_include_directories(DocTest INTERFACE ${DOCTEST_INCLUDE_DIR})

add_executable(tests Lexer_test.cc)
target_link_libraries(tests DocTest common)
