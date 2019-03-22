cmake_minimum_required(VERSION 3.2)

#if(DEFINED $ENV{TRAVIS_BUILD_NUMBER})

	project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
	
#else()
	#project(helloworld VERSION 0.0.1)
#endif()

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)

add_library(helloworld lib.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_version test_version.cpp)

set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(helloworld_cli
    helloworld
)

target_link_libraries(test_version
	${GTEST_BOTH_LIBRARIES}
   	pthread helloworld 
)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dima.friends@mail.ru)

include(CPack)

enable_testing()

add_test(test_version test_version)
