#include "ros/ros.h"
#include <ros/console.h>
#include "geometry_msgs/Twist.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <string>
#include <tf/tf.h>
#include <std_msgs/String.h>

ros::Publisher tts_pub;
ros::Publisher velocity_pub;
bool tts_blocked = false;
ros::Timer tts_blocker;

void tts_blocker_cb(const ros::TimerEvent&){
    ROS_INFO("timer cb");
    tts_blocked = false;
}
void send_movement(geometry_msgs::Point pos){
    geometry_msgs::Twist msg;
    ROS_INFO("x: %f, y: %f, z: %f", pos.x, pos.y, pos.z);
    
    if(pos.x > 0.03){
        msg.linear.y = 1;
    } else if(pos.x < -0.03){
        msg.linear.y = -1;
    }
    velocity_pub.publish(msg);
}
void sound_alert(){
    if(!tts_blocked){
        std_msgs::String text;
        text.data = "Watch your step!";
        tts_pub.publish(text);

        tts_blocked = true;
        ROS_INFO("starting timer");
        tts_blocker.setPeriod(ros::Duration(2));
        tts_blocker.start();
    }
}
auto arposecallback(ar_track_alvar_msgs::AlvarMarkers markers)
{
    if (markers.markers.size() > 0){
        auto current_marker = markers.markers[0];
        ROS_INFO("got tag %d", current_marker.id);
        
        if(current_marker.id == 8){ //paying attention
            sound_alert();
        } else if(current_marker.id == 7){ //on phone
            sound_alert();
        } else if(current_marker.id == 2){ //with headphones
            send_movement(current_marker.pose.pose.position);
        }
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "ar_nav_node");
    ROS_INFO("starting ar nav");

    ros::NodeHandle n;
    tts_blocker = n.createTimer(ros::Duration(2), tts_blocker_cb, true, false);
    ros::Subscriber alvar_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1000, arposecallback);
    velocity_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    tts_pub = n.advertise<std_msgs::String>("tts_text", 1);
    ros::spin();

    return 0;
}
