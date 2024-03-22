#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <termios.h>


int main(int argc, char **argv){
	ros::init(argc, argv, "control_keyboard");
	ros::NodeHandle control_keyboard_node;

	ros::Publisher cmd_move=control_keyboard_node.advertise<geometry_msgs::Twist>("/cmd_vel",1000);
	ros::Rate loop_rate(10);

	int count=0;
	while(ros::ok())
		{
			geometry_msgs::Twist velocity;
			char key;
			key = getchar();

			std::stringstream ss;
			ss<<"Key pressed is"<<key<<"/n";

			std_msgs::String msg;
			msg.data = ss.str();
			ROS_INFO("%s", msg.data.c_str());

			velocity.angular.z = 0;

			cmd_move.publish(velocity);
			ros::spinOnce();

			loop_rate.sleep();
			++count;
		}

	return 0;


}