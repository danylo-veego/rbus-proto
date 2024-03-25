cmake_minimum_required(VERSION 3.13)
project(rbus_proto)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE rbus)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
