#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

auto drive_forward(double t) {
	geometry_msgs::Twist msg;
	if (t < 3.0) {
		msg.linear.x = 1.0;
	}
	return msg;
}

int main(int argc, char **argv) {	
	ros::init(argc, argv, "move_to_center");
	ros::NodeHandle n("~");
	ros::Publisher velocity_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
	ros::Rate loop_rate(10);

	auto t = 0.0;
	while (ros::ok() && t < 3.0){ //TODO change to move until tag is centered
		geometry_msgs::Twist robot_vel = drive_forward(t);
		t += 0.1;

		velocity_pub.publish(robot_vel);
		loop_rate.sleep();
	}

	return 0;
}