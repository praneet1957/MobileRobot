#include "algorithms.cpp"

class ExtendedKalmanFilter:private Algorithm{
	private:
		int NumFeautrePoints = 1000;
		float F[3][2*NumFeautrePoints+3];
		float X[2*NumFeautrePoints+3];
		float P[2*NumFeautrePoints+3][2*NumFeautrePoints+3];
		int NumObservables = 9;
		matrix P(3,3,[0]);
		matrix P_bar(2*NumFeautrePoints+3,2*NumFeautrePoints+3,[0]);
		matrix H_bar(2*NumFeautrePoints+3,2*NumFeautrePoints+3,[0]);
		matrix F(3,2*NumFeautrePoints+3,[0]);
		matrix H();
		matrix K();
		

	public:
		float MotionPrediction();
		float VariancePrediction();
		float MotionUpdate();
		float VarianceUpdtae();
		float ExtendedKalmanFilter();
		float Run();



	float MotionPrediction(Bot &bot){
		motionmodel(bot);
		*(X+0) = bot.x;
		*(X+1) = bot.y;
		*(X+2) = bot.theta;
        return 0;
	}


	float VariancePrediction(Bot &bot){
		float data[3][3] = {{1,0,0},{0,1,0},{0,0,1}}
		matrix Jacob_motion(3,3,data);
		P_bar = ((Jacob_motion*P)*Jacob_motion.Transpose()) + (F.Transpose()*R)*F; 
		return 0;
	}


	float KalmanUpdate(Bot &bot){
		H_bar = (F.Transpose()*Jacob_sensor)*F;
		K     = (this->P_bar*H_bar)*((H_bar*this->P_bar)*H_bar.Transpose() + Q).inv();
		return 0;
	}


	float MotionUpdate(Bot &bot){
		matrix z = bot.observables();
		matrix h = EKF.sensormodel(bot);
		H = EKF.jacob_sensor_model(bot);
        X = X + K*(z - h);
        P = (eye(2*NumFeautrePoints+3) - (K*H))*P_bar;
        return 0;
	}


	float Run(Bot &bot){



	}






}