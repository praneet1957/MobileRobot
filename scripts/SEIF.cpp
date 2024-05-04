#include "algorithms.cpp"

class SparseExtendedInformationFilter:private Algorithm{
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
        matrix Xi();
        matrix lambda();
        matrix phit();
        matrix kappa();
        matrix eps();
		

	public:
		float MotionPrediction();
		float MeasurementUpdate();
		float SEIFUpdateEstimate();
		float SEIFSparsification();
		float Run();


    float MotionUpdate(Bot &bot){
		matrix Jacob_motion(3,3,data);
    	P_bar = ((Jacob_motion*P)*Jacob_motion.Transpose()) + (F.Transpose()*R)*F; 
        //going according to the slides
        Xi = F.transpose()*((eye(3) + Jacob_motion).inv()+ - eye(3) )*F;
        //lambda t
        lamba  = Xi.transpose()*Omega + Omega*Xi + Xi.transpose()*Omega*Xi;
        //phit
        phit = Omega + lambda;
        //kappa
        kappa = (phit*F.transpose())*(((R.inv()+ (F*phit)*F.transpose()).inv())*(F*phit));
        //Finally Information matrix update
        Omega = phit - kappa;
        //Information vector update
        eps = eps + (lambda-kappa)*X.ss.pose() + Omega*F.transpose()*motionupdatevec;
        //Motion update
        motionmodel(bot);
        X = bot.ss.pose();
	}

    float MeasurementUpdate(Bot &bot){
        //Need to update the information vector and information matrix based on observations

		return 0;
	}


    float SEIFUpdateEstimate(Bot &bot){
        X = Omega.inv()*eps;  //need to comment it to form an optimization problem
        return 0;
    }


    float SEIFSparsification(Bot &bot){
        //sparsification
        // m+ active, m0 active to passive, m- passive
        // F_m0, F_xm0, F_x are projection matrices
        Omega_t0 = (F_x_m0_mp*F_x_m0_mp.transpose())*(Omega*(F_x_m0_mp*F_x_m0_mp.transpose()));
        // Removing links between passive links O - O1
        S_Omega = Omega - ((Omega_t0*F_m0)*(F_m0.transpose()*(Omega_t0*F_m0)).inv())*(F_m0.transpose()*Omega_t0) + ((Omega_t0*F_x_m0)*(F_x_m0.transpose()*(Omega_t0*F_x_m0)).inv())*(F_x_m0.transpose()*Omega_t0) - ((Omega_t0*F_x)*(F_x.transpose()*(Omega_t0*F_x)).inv())*(F_x.transpose()*Omega_t0);
        S_eps = eps + (S_Omega - Omega)*X;

        return 0
    }

















}
