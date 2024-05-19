#include <iostream>
#include <vector>
#include "ros/ros.h"
// #include "slam/"
#include <cstdlib>
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/LaserScan"
#include "sensor_msgs/Image"
#include "sensor_msgs/Imu"
//#include 

class pose{
	public:
		float x;
		float y;
		float theta;
		float vx;
		float vy;
		float w;
};


class command{
	public:
		float v;
		float steer;
};


class Bot{
	private:
		float L;
	public:
		vector<float> g_map;
	    pose pos;
		pose prev_pos;
	    pos.x = 0;
	    pos.y = 0;
	    pos.theta = 0;
		pos.vx = 0;
		pos.vy = 0;
		pos.w = 0;

		command cmd;
		cmd.v = 0;
		cmd.u = 0;

	    LaserScan lidar_data;
	    Image camera_frame;
	    Imu imu;

	
	void sense(){
		// trigger a serrvice to get all the sensor data 
		// We can add a new variable to check if the sensor has updated or not 
		// based on that we can extend to multiple sampling frequenct filter.

        int argc = 1;
        char **argv=2;                  // need to figure out why
		
		ros::init(argc, argv, "client");
    	ros::NodeHandle bot;
    	ros::ServiceClient botsenseclient = bot.serviceClient<slam::FetchSensor>("fetch_sensor");

    	//slam::FetchSensor srv;

    	slam::FetchSensor::Request requs;
    	slam::FetchSensor::Response resps;

    	bool success_sense = botsenseclient.call(requs,resps);

    	if (success_sense){
//			encoder      = ;                    // will do this later
			lidar_data   = resps.laser;
			camera_frame = resps.img;
			imu 		 = resps.inertia;
    	}

    	else{
    		ROS_ERROR("Failed to call service add_two_ints");
    	}

		
		//ros::init(argc, argv, "bot_cmd_client");
    	//ros::NodeHandle command;
    	ros::ServiceClient botcommandclient = bot.serviceClient<slam::FetchCommand>("fetch_command");

    	slam::FetchCommand::Request requc;
    	slam::FetchCommand::Response respc;

    	bool success_command = botcommandclient.call(requc,respc);

    	if (success_command){
    		cmd.u          = respc.u;
			cmd.v          = respc.v;
    	}

    	else{
   
    	}
	}


	float Initialize(vector<float> vec){
		pos.x = vec[0];
	    pos.y = vec[1];
	    pos.theta = vec[2];
		pos.vx = vec[3];
		pos.vy = vec[4];
		pos.w = vec[5];
		
		return 0;
	}

	vector<float> ss(){
		vector<float> ss_vec;
		ss_vec.push_back(pos.x);
		ss_vec.push_back(pos.y);
		ss_vec.push_back(pos.theta);
		ss_vec.push_back(pos.vx);
		ss_vec.push_back(pos.vy);
		ss_vec.push_back(pos.w);

		return ss_vec;
	}
};









