cmake_minimum_required (VERSION 2.8.11)
project (Mesosphere)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)


add_library(mesos
						src/lib/mesos.cpp)
add_executable(mesos_exec src/prog/mesos_exec.cpp)

target_link_libraries(mesos_exec mesos)
