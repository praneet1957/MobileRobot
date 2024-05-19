#include "algorithms.cpp"

class ParticleFilter:private Algorithm{
	private:
		int NumSamples = 100;
		//float F[3][2*NumFeautrePoints+3];
		//float X[2*NumFeaturePoints+3];
		// int NumObservables = 9;
		// matrix P(3,3,[0]);
        matrix Q;

        vector<vector <float>> X;
        vector<vector <float>> X_bar;
        vector<float> W;
		

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

    float ObservationalSampling(){
        // Update weights based on observations
        vector<float> obs;
        obs =  // bot actual sensor 
        for(int j=0; j<NumSamples; j++)
        {
            vector<float> x = X_bar[j];
            Bot bot;
            bot.Initialize(X_bar[j]);
            vector<float> gx = bot.sensor_model();
            // sampling P(z|x_j) which should come from sensor model
            variance = Q;
            prob =  1/sqrt((2*3.1415)^(variance.numrows())*variance.determinant())*exp(-(obs - gx).transpose()*(variance.inv()*(obs - gx)));
            W.push_back(prob);
        }
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

    float FilterAlgo(Bot &bot){
        // The final sampling place for all points
        X_bar.clear()
        W.clear()
        
        // sampling P(x|u,x-) which comes from the motion model
        MotionSampling();

        // sampling P(z|x_j) which should come from sensor model
        ObservationalSampling();
       
        //clearing all previous sampled points, can store if needed.
        X.clear();

        // Resample the points according to w
        ReSampling();

        return X;
    }

    float Initialize(Bot &bot){
        
        //distribute all the bots randomly in the workspace ...
        



        return X;
    }


    

    







}