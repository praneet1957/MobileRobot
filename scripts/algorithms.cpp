#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <vector>
#include "lidar_model.h"
#include "camera.h"
#include <map>

using namespace std

class Algorithm{
	Public:
		float motion_model();
        float sensor_model();
		float jacob_motion_model();
		float jacob_sensor_model();
        float T;


	Private:
		float lidar_model();
		float camera_model();
		float imu_model();
		float encoder_model();
}



// state space will be X = [x,y,theta ]

float Algorithm::motion_model(Bot &bot){
	bot.x = bot.x + command_v*T*cos(bot.theta);
	bot.y = bot.y + command_v*T*sin(bot.theta);
	bot.theta = bot.theta + command_v*T*tan(bot.command_steer)/bot.L;
    
    return bot;
// Need to add noise

}



float Algorithm::sensor_model(Bot &bot){
	float Xc,Xi,Xe,Xl;
	Xc = this-> camera_model(&bot);
	Xi =this-> imu_model(&bot);
	Xe = this-> encoder_model(&bot);
	Xl = this-> lidar_model(&bot);

	//should output the observation variables either h(x)
	return h_x;

}




float Algorithm::camera_model(Bot &bot){
    frame_feature_points = bot.camera_frame();
    
}




float Algorithm::imu_model(Bot &bot){
    imu_pose = bot.imu_reading();



}

float Algorithm::lidar_model(Bot &bot){
   



}


float Algorithm::jacob_motion_model(Bot &bot){
// need to hardcode the jacob model y = C_x

}


float Algorithm::jacob_sensor_model(Bot &bot){
// need to hardcode the sensor model

}


