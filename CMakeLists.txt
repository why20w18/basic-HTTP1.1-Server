CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(HTTP_SERVER)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

#PROGRAM DIZINLERININ AYARLANMASI #PROGRAM DIZINLERININ AYARLANMASI
SET(DIZIN_SRC ${CMAKE_SOURCE_DIR}/src)
SET(DIZIN_INCLUDE ${CMAKE_SOURCE_DIR}/include)

SET(PROGRAM_SRC
    ${DIZIN_SRC}/main.cpp
    ${DIZIN_SRC}/fileOpen.cpp
    ${DIZIN_SRC}/httpServer.cpp
    ${DIZIN_SRC}/serverCommands.cpp
    
)

SET(PROGRAM_INCLUDE
    ${DIZIN_INCLUDE}/fileProcess.hpp
    ${DIZIN_INCLUDE}/fileOpen.hpp
    ${DIZIN_INCLUDE}/httpServer.hpp
    ${DIZIN_INCLUDE}/serverCommands.hpp
    ${DIZIN_INCLUDE}/crossDefines.hpp

)
#PROGRAM DIZINLERININ AYARLANMASI #PROGRAM DIZINLERININ AYARLANMASI








#BOOST KUTUPHANESININ BAGLANMASI #BOOST KUTUPHANESININ BAGLANMASI
if(WIN32)
    set(BOOST_ROOT "./utils-WIN32/boost_build")
    set(CMAKE_PREFIX_PATH ${BOOST_ROOT})
    set(BOOST_INCLUDE_DIR ${BOOST_ROOT}/include)
    set(BOOST_LIBRARY_DIR ${BOOST_ROOT}/lib)

    include_directories(${BOOST_INCLUDE_DIR})   
    link_directories(${BOOST_LIBRARY_DIR})

    find_package(Boost 1.87.0 REQUIRED COMPONENTS system thread
    PATHS "./utils-WIN32/boost_build" NO_DEFAULT_PATH)

elseif(UNIX)
    find_package(Boost REQUIRED)

endif()
#BOOST KUTUPHANESININ BAGLANMASI #BOOST KUTUPHANESININ BAGLANMASI






if(WIN32)
    add_executable(
        ${PROJECT_NAME} 
        ${PROGRAM_SRC}
        )

    target_link_libraries(
        ${PROJECT_NAME}
        Boost::system
        Boost::thread
        ws2_32
    )

elseif(UNIX)
    include_directories(
        ${PROGRAM_INCLUDE}
    )

    add_executable(
            ${PROJECT_NAME} 
            ${PROGRAM_SRC}
    )

endif()