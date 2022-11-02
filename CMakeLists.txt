project( EMST )

cmake_minimum_required(VERSION 3.14)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

set(EXECUTABLE_OUTPUT_PATH "bin")

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra --pedantic -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Wextra --pedantic -O2")
set(CMAKE_CXX_FLAGS "-Wall -Wextra") 

set(CMAKE_CXX_STANDARD 14)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(EMST
  	src/Point.cpp
	src/Edge.cpp
	src/Graph.cpp
	src/AssPoints.cpp
	src/AssEdges.cpp
	src/RNG.cpp
	src/EMST.cpp
	src/PointGeneration.cpp
	src/starterEMST.cpp
	src/utils.cpp

)
target_include_directories(EMST PRIVATE include)
target_link_libraries(EMST PUBLIC CGAL::CGAL_Basic_viewer) 

enable_testing()

add_executable(test_EMST_and_RNG
  	test/AssPoints.cpp
  	test/AssEdges.cpp
  	test/utils.cpp
  	test/RNGTest.cpp
  	test/EMSTTest.cpp
  	src/Point.cpp
	src/Edge.cpp
	src/Graph.cpp
	src/AssPoints.cpp
	src/AssEdges.cpp
	src/RNG.cpp
	src/EMST.cpp
	src/PointGeneration.cpp
	src/utils.cpp
	)
target_include_directories(test_EMST_and_RNG PRIVATE include)
target_link_libraries(
  test_EMST_and_RNG
  GTest::gtest_main
  CGAL::CGAL_Basic_viewer
)

include(GoogleTest)
gtest_discover_tests(test_EMST_and_RNG)




