# src folder

include_directories(. ../include /usr/local/include)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

add_definitions(-Wall -dynamiclib)

link_directories(${PROJECT_BIN_DIRECTORY} /usr/local/include)

add_library(PhantomMenace SHARED ${SOURCES})
add_library(PhantomMenace-static STATIC ${SOURCES})
target_link_libraries(PhantomMenace PmIniParser boost_regex-mt)
target_link_libraries(PhantomMenace-static PmIniParser boost_regex-mt)

# Set the version of the library
set_target_properties(PhantomMenace PhantomMenace-static
    PROPERTIES SOVERSION 1 VERSION 1.1.21)

install(TARGETS PhantomMenace LIBRARY DESTINATION lib)
install(TARGETS PhantomMenace-static ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
