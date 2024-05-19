#include "algorithms.cpp"

class FastSLAM:private Algorithm{
	private:
		int NumParticles = 100;
		float F[3][2*NumFeautrePoints+3];
		float P[2*NumFeaturePoints+3][2*NumFeaturePoints+3];
		int NumObservables = 9;
		matrix P(3,3,[0]);

        vector<vector <float>> X;  // pose
        vector<vector <float>> X_bar; // to store sampled points after motion update
        vector<vector <float>> mu; // mean
        vector<matrix> Sig; // Covariance 
        vector<float> W; // weights
        
	public:
		float MotionSampling();
		float ObservationalSampling();
		float FilterAlgo();
		float Run();

    float MotionSampling(){
        // Sample according to the motion model of the bot
        for(int j=0;j<NumSamples;j++)
        {
            vector<float> state_vector = X[j];
            Bot bot;
            bot.Initialize(X[j]);
            // sampling P(z|x_j) which should come from sensor model
            motion_model(&bot);
            X_bar.push_back(bot.ss());
        }
    }

    float ObservationUpdate(Bot &bot){
        // observe a feature 
        // identify it is unique and to include in map
        if (feature.unique == 1){
            mu_j = //
            H = jacob_sensor_model(); // jacob sensor model
            Sig = (H.inv()*Q)*(H.inv()).transpose();
            W.pushback(); // some initial weight.
        }

        else{
            // feature is j
            z_hat = // obdervation model h();
            H = jacob_sensor_model(); //jacobian;
            Q = (H*Sig[j])*H.transpose() + Q;
            K = (Sig[j]*H.transpose())*Q.inv();
            mu[j] = mu[j] + K*(z - z_hat);
            Sig[j] = (eye() - K*H)*Sig[j];
            wk =  1/sqrt((2*3.1415)^(variance.numrows())*variance.determinant())*exp(-0.5*(z-z_hat).transpose()*(Q.inv())*(z-z_hat)); // exponential function completion
            W.push_back(wk);
        }
    }

    float FASTLAM(){





    }









}