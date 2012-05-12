# test folder

include_directories(../include)

file (GLOB SOURCES *.cpp)

link_directories(${PROJECT_BINARY_DIR})

add_executable(validate_grammar validate_grammar.cpp)
add_executable(validate_tokens validate_tokens.cpp)
add_executable(print_log print_log.cpp)
add_executable(validate_string validate_string.cpp)

target_link_libraries(validate_grammar PhantomMenace)
target_link_libraries(validate_tokens PhantomMenace)
target_link_libraries(print_log PhantomMenace)
target_link_libraries(validate_string PhantomMenace)

enable_testing()
add_test(ValidateGrammar validate_grammar)
add_test(ValidateTokens validate_tokens)
add_test(ValidateString validate_string)

