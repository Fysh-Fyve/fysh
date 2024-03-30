# https://lesleylai.info/en/unit-test-with-cmake/
set(DOCTEST_INCLUDE_DIR ../doctest)
add_library(DocTest INTERFACE)
target_include_directories(DocTest INTERFACE ${DOCTEST_INCLUDE_DIR})

add_executable(
	tests
	test_Fysh.cc
	test_Lexer.cc
	test_Parser.cc
	test_main.cc
)
target_link_libraries(tests DocTest common)
