#include "algorithms.cpp"

class UnscentedKalmanFilter:private Algorithm{
	private:
		int NumFeautrePoints = 1000;
        int NumSigmaPoints = 10;
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
        float alpha, beta, lambda;
        float weights_mean[2*NumSigmaPoints+1];
        float weights_covariance[2*NumSigmaPoints+1];
        Bot bots[2*NumSigmaPoints+1];
        matrix X_bar(2*NumFeautrePoints+3, 2*NumSigmaPoints+1,[0]);
        matrix St, Sigmat;
    

		

	public:
		float MotionPrediction();
		float VariancePrediction();
		float MotionUpdate();
		float VarianceUpdtae();
		float UnscentedKalmanFilter();
		float Run();


    float MotionPrediction(Bot &bot){
		motionmodel(bot);
        for(int i=0;i<2*NumSigmaPoints+1;i++){
            j = i - NumSigmaPoints;     
            bots[i].ss() = bot.ss() + sgn(j)*sqrt((NumSigmaPoints + lambda)*P[:,j]); // get jth column of P implment sgn function
            X = X + weights_mean[i]*bots[i].ss();
        }
        return 0;
	}


	float VariancePrediction(Bot &bot){
        for(int i=0;i<2*NumSigmaPoints+1;i++){
            j = i - NumSigmaPoints;   
            P = P + weights_covariance[i]*(bots[i].ss() - X)*(bots[i].ss() - X).transpose();
        }
        P = P + R;
		return 0;
	}


    float ObservationalMatrices(){
        for(int i=0;i<2*NumSigmaPoints+1;i++){
            j = i - NumSigmaPoints;     
            bots[i].ss() = X + sgn(j)*sqrt((NumSigmaPoints + lambda)*P[:,j]); // get jth column of P implment sgn function
            Z[:,i] = UnscentedKalmanFilter.sensor_model(Bot &bot);
            z_hat = z_hat + weights_mean[i]*Z[:,i] ;

        }

        for(int i=0;i<2*NumSigmaPoints+1;i++){
            St = St + weights_covariance[i]*(Z[:,i] - z_hat)*(Z[:,i] - hat).transpose();
            Sigmat = Sigmat + weights_covariance[i]*(bots[i].ss() - X)*(Z[:,i] - hat).transpose();
        }

        St = St + Q;
    }


	float KalmanUpdate(Bot &bot){
		K     = Sigmat*St.inv();
		return 0;
	}


	float MotionUpdate(Bot &bot){
        matrix z = bot.observables();
		bot.ss() = X + K*(z - z_hat);
        P = P - (K*St)*K.transpose();
        return 0;
	}


	float Run(Bot &bot){



	}

    float UnscentedKalmanFilter(){
        
        for(int i=0;i<2*NumSigmaPoints+1;i++){
            if (i==NumSigmaPoints){
                weights_mean[i]=lambda/(NumSigmaPoints+lambda);
                weights_covariance[i]=lambda/(NumSigmaPoints+lambda) + (1- alpha*alpha + beta);
            }
            else{
                weights_mean[i]=1/(2*NumSigmaPoints+lambda);
                weights_covariance[i]=1/(2*NumSigmaPoints+lambda);
            }

            
        }

        

    }






}