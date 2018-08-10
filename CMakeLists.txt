#minimalna wersja cmake
cmake_minimum_required(VERSION 3.8)

#nazwa projektu
project(neuralNetwork)

#wgląd w wykonywane polecenia w pliku compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)

#lista plików źródłowych
set(SOURCE_FILES
        src/main.cpp src/Input.cpp src/Neuron.cpp src/Layer.cpp src/Network.cpp)

add_library(Library ${SOURCE_FILES})
set_target_properties(Library PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


#co ma być zbudowane i z czego
add_executable(neuralNetwork ${SOURCE_FILES})

#add libraries from 'Library' project
set_target_properties(neuralNetwork PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(neuralNetwork PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)



#Sekcja testów
find_package(Boost COMPONENTS unit_test_framework REQUIRED)


set(SOURCE_TEST_FILES test/master.cpp test/InputTest.cpp)
include_directories(${Boost_INCLUDE_DIRS})

#Test sprawdzajacy klase Input
add_executable(InputTest ${SOURCE_TEST_FILES})
target_link_libraries(InputTest Library ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} -lboost_date_time -lstdc++)
add_test(Test InputTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )





#add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
#        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})



enable_testing()