project(TurmaFasb)
set(Boost_LIBRARY_DIR C:/boost/lib)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Boost_LIBRARY_DIR})
find_package(Boost COMPONENTS program_options system locale filesystem)
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
set(JSONCPP "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp")
set(UTILCPP "${CMAKE_CURRENT_BINARY_DIR}/utilcpp")

include_directories(src
                    ${MONGOOSE}/include
                    ${Boost_INCLUDE_DIRS}
                    ${JSONCPP}/include
                    ${SOCI}/include
                    ${UTILCPP}/include )
link_directories(${LINK_DIRECTORIES}
					${Boost_LIBRARY_DIR}
                    ${JSONCPP}/lib
                    ${MONGOOSE}/lib
                    ${SOCI}/lib )
add_executable(${PROJECT_NAME} ${FULL_SRC})
target_link_libraries(${PROJECT_NAME}
                    ${Boost_LIBRARIES}
                    _mongoose
                    soci_core
                    jsoncpp
                    ws2_32 )
					  
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(${PROJECT_NAME} 
					pthread
					iconv )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
endif()


include(ExternalProject)
ExternalProject_Add (
    jsoncpp
    URL  "http://github.com/open-source-parsers/jsoncpp/archive/master.zip"
    UPDATE_COMMAND ""
    CMAKE_ARGS
        "-G${CMAKE_GENERATOR}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_INSTALL_PREFIX=${JSONCPP}" )
add_dependencies(${PROJECT_NAME} jsoncpp)

ExternalProject_Add (
    utilcpp
    #URL  "http://github.com/Caimbe/UtilCpp/archive/master.zip"
    URL "file://C:/Users/Andre/workspace/UtilCpp"
    UPDATE_COMMAND ""
    CMAKE_ARGS
        "-G${CMAKE_GENERATOR}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_INSTALL_PREFIX=${UTILCPP}" )
add_dependencies(${PROJECT_NAME} utilcpp)

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
        "-DCMAKE_INSTALL_PREFIX=${SOCI}"
		"-DMYSQL_LIBRARIES=C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/lib/libmysql.lib" )
add_dependencies(${PROJECT_NAME} soci)
