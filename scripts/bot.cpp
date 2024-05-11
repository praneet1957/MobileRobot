//#include "ros/ros.h"
#include <iostream>
#include <vector>
//#include 

class pose{
	public:
		float x;
		float y;
		float theta;



};


class command{
	public:
		float u;
		float v;
};




class Bot{
	private:
		float L;
	public:
		vector<float> g_map;
	    pose pos;
		command cmd;
	    float encoder[4];
	    vector<vector <float>> lidar_data;                     
	    vector<vector <float>> camera_frame;                 
	    float imu[3];                   //ax, ay, wz

	
	void sense(){
		// trigger a serrvice to get all the sensor data 
		// We can add a new variable to check if the sensor has updated or not 
		// based on that we can extend to multiple sampling frequenct filter.



		// pos = ;
		// cmd = ;
		// encoder = ;
		// lidar_data =;
		// camera_frame =;


	}


};




