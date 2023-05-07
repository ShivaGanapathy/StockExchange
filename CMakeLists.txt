cmake_minimum_required(VERSION 3.16)

project(tcp_app)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# Add source files for server
set(SERVER_SOURCES
    ../src/side.cpp
    ../src/order.cpp
    ../src/orderBook.cpp
    ../src/clientHandler.cpp
    ../src/matchingEngine.cpp
    ../src/server.cpp
)

# Add executable for server
add_executable(server ${SERVER_SOURCES})
target_link_libraries(server PRIVATE ${Boost_LIBRARIES} Boost::system)

# Add source files for client
set(CLIENT_SOURCES
    ../src/client.cpp
)

# Add executable for client
add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} Boost::system)
