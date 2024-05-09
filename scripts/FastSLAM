#include "algorithms.cpp"

class FastSLAM:private Algorithm{
	private:
		int NumParticles = 100;
		float F[3][2*NumFeautrePoints+3];
		float P[2*NumFeaturePoints+3][2*NumFeaturePoints+3];
		int NumObservables = 9;
		matrix P(3,3,[0]);

        vector<vector <float>> X;  // pose
        vector<vector <float>> mu; // mean
        vector<matrix> Sig; // Covariance 
        vector<float> w; // weights
        
		

	public:
		float MotionSampling();
		float ObservationalSampling();
		float FilterAlgo();
		float Run();

    float MotionSampling(Bot &bot){
        for(int i=0;i<NumParticles;i++){
            // Sample from the motion model p(x(t) | x(t-1), u).
        }
        return 0;
	}

    float ObservationUpdate(Bot &bot){
        // observe a feature 
        // identify it is unique and to include in map
        if (feature.unique == 1){
            mu_j = //
            H = // jacob sensor model
            Sig = //
            w.pushback() // some initial weight.
        }

        else{
            // feature is j
            z_hat = // obdervation model h()
            H = //jacobian
            Q = (H*Sig[j])*H.transpose() + Q;
            K = (Sig[j]*H.transpose())*Q.inv();
            mu[j] = mu[j] + K*(z - z_hat);
            Sig[j] = (eye() - K*H)*Sig[j];
            w =            exp(-0.5*(z-z_hat).transpose()*(Q.inv())*(z-z_hat)); // exponential function completion


        }


    }

    float FASTLAM(){





    }









}