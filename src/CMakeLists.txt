# src folder

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

set(MajorVersion  1)
set(BinaryVersion 1)
set(MinorVersion  26)
set(FullVersion ${MajorVersion}.${BinaryVersion}.${MinorVersion})

add_definitions(
    -Wall
    -DMAJORVERSION=${MajorVersion}
    -DBINARYVERSION=${BinaryVersion}
    -DMINORVERSION=${MinorVersion})

link_directories(${PROJECT_BIN_DIRECTORY})

find_package(Boost REQUIRED COMPONENTS regex-mt)
find_package(PmIniParser REQUIRED)

include_directories(
    ${PhantomMenace_SOURCE_DIR}/include
    ${PmIniParser_INCLUDE_DIR} 
    ${Boost_INCLUDE_DIRS})
add_library(PhantomMenace SHARED ${SOURCES})
add_library(PhantomMenace-static STATIC ${SOURCES})
target_link_libraries(PhantomMenace ${PmIniParser_LIBRARY} ${Boost_LIBRARIES})
target_link_libraries(PhantomMenace-static ${PmIniParser_LIBRARY} ${Boost_LIBRARIES})

# Set the version of the library
set_target_properties(PhantomMenace PhantomMenace-static
    PROPERTIES SOVERSION 1 VERSION ${FullVersion})

# Build the static library with the same name
set_target_properties(PhantomMenace-static
    PROPERTIES OUTPUT_NAME PhantomMenace)

install(TARGETS PhantomMenace LIBRARY DESTINATION lib)
install(TARGETS PhantomMenace-static ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
