# src folder

include_directories(. ../include /usr/local/include)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

add_definitions(-Wall -dynamiclib)

link_directories(${PROJECT_BIN_DIRECTORY})

find_package(Boost REQUIRED COMPONENTS regex-mt)
find_package(PmIniParser REQUIRED)

include_directories(${PmIniParser_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
add_library(PhantomMenace SHARED ${SOURCES})
add_library(PhantomMenace-static STATIC ${SOURCES})
target_link_libraries(PhantomMenace ${PmIniParser_LIBRARY} ${Boost_LIBRARIES})
target_link_libraries(PhantomMenace-static ${PmIniParser_LIBRARY} ${Boost_LIBRARIES})

# Set the version of the library
set_target_properties(PhantomMenace PhantomMenace-static
    PROPERTIES SOVERSION 1 VERSION 1.1.22)

# Build the static library with the same name
set_target_properties(PhantomMenace-static
    PROPERTIES OUTPUT_NAME PhantomMenace)

install(TARGETS PhantomMenace LIBRARY DESTINATION lib)
install(TARGETS PhantomMenace-static ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
