cmake_minimum_required(VERSION 3.13)

project(graph-front-end LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)


# optimization option, see https://github.com/antlr/antlr4/pull/4237
option(ENABLE_PR4237_OPT "Enable PR#4237 optimization." OFF)
if (ENABLE_PR4237_OPT)
	message("PR#4237 optimization is enabled.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANTLR4_USE_THREAD_LOCAL_CACHE=1")
else (ENABLE_PR4237_OPT)
	message("PR#4237 optimization is disabled.")
endif (ENABLE_PR4237_OPT)


set(ANTLR4_CPP_RUNTIME ${PROJECT_SOURCE_DIR}/antlr4/runtime/Cpp/run/usr/local)
include_directories(${ANTLR4_CPP_RUNTIME}/include/antlr4-runtime)

add_executable(concurrent_perf_test
			   src/main.cpp
			   src/generated/CypherLexer.cpp
			   src/generated/CypherParser.cpp
			   src/generated/CypherVisitor.cpp
			  )

target_link_libraries(concurrent_perf_test ${ANTLR4_CPP_RUNTIME}/lib64/libantlr4-runtime.a pthread)
#target_link_libraries(concurrent_perf_test ${ANTLR4_CPP_RUNTIME}/lib/libantlr4-runtime.a pthread)

