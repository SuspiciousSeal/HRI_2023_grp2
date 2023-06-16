cmake_minimum_required(VERSION 2.8.3)
project(main_temoto_config)

# use c++11 standard
add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  temoto_action_assistant
  temoto_process_manager
  temoto_robot_manager
  temoto_component_manager
)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
# Build component manager client
add_executable(main_cmi_client
  src/main_cmi_client.cpp
)

add_dependencies(main_cmi_client 
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_link_libraries(main_cmi_client 
  ${catkin_LIBRARIES}
)
# Build process manager client
add_executable(main_pmi_client
  src/main_pmi_client.cpp
)

add_dependencies(main_pmi_client 
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_link_libraries(main_pmi_client 
  ${catkin_LIBRARIES}
)
# Robot Manager Node
add_executable(main_robot_manager
  src/main_robot_manager.cpp
)

add_dependencies(main_robot_manager 
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_link_libraries(main_robot_manager 
  ${catkin_LIBRARIES}
)