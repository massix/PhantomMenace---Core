# src folder

include_directories(. ../include /usr/local/include)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

add_definitions(-Wall -dynamiclib)

link_directories(${PROJECT_BIN_DIRECTORY} /usr/local/include)
link_libraries(PmIniParser)

add_library(PhantomMenace SHARED ${SOURCES})
add_library(PhantomMenace-static STATIC ${SOURCES})

install(TARGETS PhantomMenace LIBRARY DESTINATION lib)
install(TARGETS PhantomMenace-static ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
