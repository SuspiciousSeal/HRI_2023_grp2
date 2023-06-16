#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <string>
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include <tf/tf.h>
#include <ros/console.h>
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

ros::Publisher velocity_pub;
auto arposecallback(ar_track_alvar_msgs::AlvarMarkers markers)
{ 
    if (markers.markers.size() > 0)
    {
        auto marker = markers.markers.front();
        auto pos = marker.pose.pose.position;
        
        geometry_msgs::Twist msg;
         if (pos.z > 0.3) {
            if (pos.x > 0.4) {
                msg.angular.z = -1;
            } else if (pos.x < 0.2) {
                msg.angular.z = 1;
            } else {
                msg.angular.z = 0;
            }
            msg.linear.x = 1;
        } else {
            msg.linear.x = 0;
        }
        velocity_pub.publish(msg);
        
        // x = left-right left=+, right=-
        // y = up-down, down=+, up=-
        // z = close-far close=0, far= >0
        ROS_INFO("x: %f, y: %f, z: %f", pos.x, pos.y, pos.z);
        // moveto(pos.x, pos.y);
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "ar_nav_node");
    ROS_INFO("starting ar nav");

    ros::NodeHandle n;
    ros::Subscriber alvar_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1000, arposecallback);
    velocity_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);   
    ros::spin();

    return 0;
}