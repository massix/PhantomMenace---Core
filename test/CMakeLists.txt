# test folder

include_directories(. ../src ../include /Users/massi/Developer/include)

file (GLOB SOURCES *.cpp)

link_directories(${PROJECT_BINARY_DIR})
link_libraries(PhantomMenace PmIniParser)

add_executable(validate_grammar validate_grammar.cpp)
add_executable(validate_tokens validate_tokens.cpp)
add_executable(print_log print_log.cpp)
add_executable(validate_string validate_string.cpp)

enable_testing()
add_test(ValidateGrammar validate_grammar)
add_test(ValidateTokens validate_tokens)
add_test(ValidateString validate_string)

