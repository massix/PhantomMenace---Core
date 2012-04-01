# test folder

include_directories(. ../src ../include /Users/massi/Developer/include)

file (GLOB SOURCES *.cpp)

link_directories(${PROJECT_BINARY_DIR} /Users/massi/Developer/lib)
link_libraries(PhantomMenace PmIniParser)

add_executable(validate_grammar validate_grammar.cpp)

enable_testing()
add_test(ValidateGrammar validate_grammar)

