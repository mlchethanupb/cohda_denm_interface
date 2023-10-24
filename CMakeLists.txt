cmake_minimum_required(VERSION 3.5.2)
project(cohda_denm_interface)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  etsi_its_msgs
  ros_collision_detection
  # Add other necessary dependencies
)

## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS roscpp std_msgs etsi_its_msgs ros_collision_detection# Add other necessary dependencies
)

## Build the node
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  flatbuffers/include
)

add_executable(cohda_denm_interface src/denm_send.cpp src/udp_socket.cpp)
add_dependencies(cohda_denm_interface etsi_its_msgs_generate_messages_cpp  ros_collision_detection_generate_messages_cpp)
target_link_libraries(  cohda_denm_interface 
                        ${catkin_LIBRARIES} )
