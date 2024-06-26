
cmake_minimum_required(VERSION 3.16...3.21)
project(DetectorStilbene)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/headers)
include_directories(${PROJECT_SOURCE_DIR}/data)

file(GLOB sources ${PROJECT_SOURCE_DIR}/sources/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/headers/*.hh)
file(GLOB MACRO_FILES "*.mac")

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(Main Main.cc ${sources} ${headers})
target_link_libraries(Main ${Geant4_LIBRARIES})

add_custom_target(DetectorStilbene DEPENDS Main)

#set(CMAKE_AUTOMOC ON)

target_link_libraries(Main ${Geant4_LIBRARIES})


