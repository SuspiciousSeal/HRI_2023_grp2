cmake_minimum_required(VERSION 3.0.2)
project(hazard_bot)

find_package(catkin REQUIRED COMPONENTS
  ar_track_alvar
  geometry_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
 CATKIN_DEPENDS roscpp rospy std_msgs ar_track_alvar geometry_msgs
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(mover src/mover.cpp)
target_link_libraries(mover ${catkin_LIBRARIES})