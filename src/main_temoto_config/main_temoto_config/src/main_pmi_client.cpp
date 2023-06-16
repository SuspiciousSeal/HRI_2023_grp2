#include "ros/ros.h"
#include "temoto_process_manager/process_manager_interface.hpp"

void resourceFailureCallback(temoto_process_manager::LoadProcess load_process_msg)
{
  ROS_WARN_STREAM("The following resource stopped unexpectedly\n" << load_process_msg.request);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "main_pmi_client");

  temoto_process_manager::ProcessManagerInterface pmi(true);
  // pmi.registerUpdateCallback(resourceFailureCallback);

  ROS_INFO("Loading rqt_graph");
  pmi.loadRosResource("rqt_graph", "rqt_graph");
  ros::Duration(5).sleep();
}