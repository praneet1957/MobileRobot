#include "std_msgs/String.h"
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <math>
#include <matrix>


class distribution{
    Private:
        matrix mean;
        matrix variance;






    Public:
        float sample(float x){
            p_x = 1/sqrt((2*3.1415)^(variance.numrows())*variance.determinant())*exp(-(x-mean).transpose()*(variance.inv()*(x-mean)))
            
        }
    

}

class Gaussian::private distribution {


}

class Normal::private distribution{


}

class Poison::private distribution{


}


class Bernoulli::private distribution{



}

class Beta::private distribution{

}

class Gamma::private distribution{

}