#include "algorithms.cpp"

class FastSLAM:private Algorithm{
	private:
		int NumParticles = 100;
		float F[3][2*NumFeautrePoints+3];
		float P[2*NumFeaturePoints+3][2*NumFeaturePoints+3];
		int NumObservables = 9;

        vector<vector <float>> X;  // pose
        vector<vector <float>> X_bar; // to store sampled points after motion update
        vector<vector <float>> mu; // mean
        vector<matrix> Cov; // Covariance 
        vector<float> W; // weights

        matrix zHat;
        matrix H;
        matrix Q;           // pre determined measurement convariance
        matrix K;
        
	public:
		float MotionSampling();
		float ObservationalSampling();
		float FilterAlgo();
		float Run();

    float MotionSampling(Bot &bot){
        // Sample according to the motion model of the bot
        vector<float> state_vector = x;
        bot.Initialize(x);
        // sampling P(z|x_j) which should come from sensor model
        motion_model(&bot);
        X_bar.push_back(bot.ss());
        return 0;
    }

    float ObservationUpdate(Bot &bot){
        // observe a feature 
        // identify it is unique and to include in map

        if (feature.unique == 1){
            mu[j]= bot.pos                                                    // need to figure out
            H.init_mat(jacob_sensor_model());  // jacob sensor model
            Cov.push_back((H.inv()*Q)*(H.inv()).transpose());
            W.push_back(); // some initial weight.
        }

        else{
            // feature is j
            zHat.init_mat(sensor_model(&bot));
            H.init_mat(jacob_sensor_model());                      
            Q      = (H*Cov[j])*H.transpose() + Q;
            //Calculate Kalman Gain
            K.mat     = (Cov[j]*H.transpose())*Q.inv();      
            //Update the avg and Convariance as in KF
            mu[j]     = mu[j] + K*(z - zHat);           // z is ?
            Cov[j]    = (eye() - K*H)*Cov[j];
            float wk  =  1/sqrt((2*3.1415)^(variance.numrows())*variance.determinant())*exp(-0.5*(z-zHat).transpose()*(Q.inv())*(z-zHat)); // exponential function completion
            W.push_back(wk);
        }
        return 0;
    }


    float ReSampling(){
        float sum_weights=0;
        vector<float> start;
        for(int j=0; j<NumSamples; j++){
            sum_weights += W[j];
            start.push_back(sum_weights);
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(0.0, 1.0);

        for(int k=0; k<NumSamples; k++){
            bool found = false;
            float randomFraction = dis(gen);
            int j=0;
            while (j<NumSamples & found==false){
                if (randomFraction < start[j]){
                    found = true;
                    X.push_back(X_bar[j])
                }
                else{
                    j=j+1;
                }
            }
        }
        return 0;
    }



    float FASTLAM(){
    // FastSLAM corespondences
        for(int j=0;j<NumSamples;j++){
            //Initialize the bot
            Bot bot;
            bot.Initialize(X[j]);
            //Sampling the bot using motion model
            MotionSampling(&bot);
            //Observational update
            ObservationUpdate(&bot);
        }


        //Resampling of the points
        ReSampling();

        return 0;
    }

}