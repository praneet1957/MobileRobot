#include "algorithms.cpp"

class ParticleFilter:private Algorithm{
	private:
		int NumSamples = 100;
		float F[3][2*NumFeautrePoints+3];
		float X[2*NumFeaturePoints+3];
		float P[2*NumFeaturePoints+3][2*NumFeaturePoints+3];
		int NumObservables = 9;
		matrix P(3,3,[0]);

        vector<vector <float>> X;
        vector<vector <float>> X_bar;
		

	public:
		float MotionSampling();
		float ObservationalSampling();
		float FilterAlgo();
		float Run();


    float MotionSampling(){
        // Sample according to the motion model of the bot
        

    }

    float ObservationalSampling(){
        // Update weights based on observations


    }

    float FilterAlgo(Bot &bot){
        // The final sampling place for all points
        X_bar.clear()
        for(int j=0;j<NumSamples;j++){
            vector<float> x_j;
            float w_j;
            // sampling P(x|u,x-) which comes from the motion model
            x_j = MotionSampling();

            // sampling P(z|x_j) which should come from sensor model
            w_j = ObservationalSampling();
            x_j.pushback(w_j);
            // adding to list of points
            X_bar.pushback(x_j);
        }

        //clearing all previous sampled points, can store if needed.
        X.clear();

        for(int j=0;j<NumSamples;j++){
            // draw x_i's with probability w_i
            X.pushback(x_i);
        }

        return X;
    }


    

    







}