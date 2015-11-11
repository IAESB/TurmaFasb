project(AppTurmaFasb)
find_package(Boost REQUIRED COMPONENTS program_options system)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC)
aux_source_directory(src/entity ENTITY)
aux_source_directory(src/controller CONTROLLER)
aux_source_directory(src/model MODEL)
aux_source_directory(src/repository REPOSITORY)
list(APPEND FULL_SRC
        ${SRC}
        ${ENTITY}
        ${CONTROLLER}
        ${MODEL}
        ${REPOSITORY} )

set(MONGOOSE "${CMAKE_CURRENT_BINARY_DIR}/mongoose-cpp")
set(SOCI "${CMAKE_CURRENT_BINARY_DIR}/soci")

include_directories(src
                    ${MONGOOSE}/include
                    ${Boost_INCLUDE_DIRS}
                    ${MONGOOSE_INCLUDE}
                    ${SOCI}/include)
link_directories(${LINK_DIRECTORIES}
                    ${MONGOOSE}/lib
                    ${SOCI}/lib)
add_executable(${PROJECT_NAME} ${FULL_SRC})
target_link_libraries(${PROJECT_NAME}
                      ${Boost_LIBRARIES}
                      pthread
                      _mongoose
                      soci_core
                      jsoncpp
                      ws2_32 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include(ExternalProject)
ExternalProject_Add (
    mongoose-cpp
    URL  "file://C:/Users/Andre/workspace/mongoose-cpp"
#    URL  "http://github.com/Caimbe/mongoose-cpp/archive/master.zip"
    UPDATE_COMMAND ""
    CMAKE_ARGS
        "-DENABLE_SESSION_BOOST_ANY=ON"
        "-G${CMAKE_GENERATOR}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_INSTALL_PREFIX=${MONGOOSE}" )
add_definitions("-DENABLE_SESSION_BOOST_ANY")
add_dependencies(${PROJECT_NAME} mongoose-cpp)

ExternalProject_Add (
    soci
    URL  "https://github.com/SOCI/soci/archive/master.zip"
    UPDATE_COMMAND ""
    CMAKE_ARGS
        "-G${CMAKE_GENERATOR}"
        "-DSOCI_CORE_TARGET_OUTPUT_NAME=soci_core"
        "-DSOCI_TESTS=OFF"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_INSTALL_PREFIX=${SOCI}" )
add_dependencies(${PROJECT_NAME} soci)
