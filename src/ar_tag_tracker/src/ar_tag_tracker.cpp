#include "ros/ros.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "math.h"


void print_tag(const ar_track_alvar_msgs::AlvarMarkers& msg)
{
  if(msg.markers.size() >= 1){
    ROS_INFO("received tag %d, q %f %f %f %f", msg.markers[0].id ,msg.markers[0].pose.pose.orientation.x, msg.markers[0].pose.pose.orientation.y, msg.markers[0].pose.pose.orientation.z, msg.markers[0].pose.pose.orientation.w);
  }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ar_tag_tracker");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("ar_pose_marker", 10, print_tag);
  ros::Rate loop_rate(10);
  ROS_INFO("ar_tag_tracker ready");
  ros::spin();
  return 0;
}
