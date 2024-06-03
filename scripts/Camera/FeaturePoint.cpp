#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <matrix>


using namespace std;

//will be using orb filter


vector<float> corner_orientation(float Image, float corners, float bounding_box){
    int numCorners = size(corners);
    int radius = bounding_box/2;
    vector<float> orientations;
    vector<vector <float>> result;
    for(int i=0;i<numCorners; i=i+1){
        //Calculate the moments 
        x = corners[i][0];
        y = corners[i][1];
        float Moo = 0;
        float Moi = 0;
        float Mio = 0;

        for(int k=-radius; k<= radius; k++){
            for(int l=-radius; l<= radius;l++){
                float dist = k*k + l*l;
                if (dist < (radius+0.5)*(radius+0.5)){
                    Moo = Moo + Image[x+k][y+l];
                    Moi = Moi + l*Image[x+k][y+l];
                    Mio = Mio + k*Image[x+k][y+l];
                }
                else{
                }
            }
        }

        // Calculate angle using tan inverse
        float theta = atan2(Moi,Mio);
        float centroid = {Mio/Moo ,Moi/Moo};

        orientations.push_back(theta);
        result.push_back({Mio/Moo ,Moi/Moo, theta});    
    }

    return result;
}


vector<float> oFAST(float Image, float N){
    // implementing the FAST-12 algorithm
    float bounding_box = 7;
    float threshold    = 0.1; // intensity threshold
    int Npoints = 12;
    int Rows = size(Image);
    int Cols = size(Image[0]);
    int radius = bounding_box/2;
    vector<vector<float>> keypoints;


    // Detecting the keypoints
    for(int i=radius+1;i<Rows-radius-1;i++){
        for(int j=radius+1;j<Cols-radius-1;j++){

            // Hardcoding the circle for now
            float listPoints = {{0,-3},{0,3},{3,0},{-3,0},{-3,-1},{-3,1},{-2,-2},{-2,2},{-1,-3},{-1,3},{1,-3},{1,3},{2,-2},{2,2},{3,-1},{3,1}};
            int prio = {0,1,2,3};

            int bright=0; 
            int dim=0;
            for(int k=0;k<4;k++){
                if (Image[i+listPoints[k]][j+listPoints[k]] > Image[i][j] + threshold){
                    bright = bright +1 ;
                }
                else if(Image[i+listPoints[k]][j+listPoints[k]] < Image[i][j] - threshold){
                    dim = dim +1;
                }
                else{
                }
            }

            if (bright>=3 || dim>=3){
                //check for all pixels
                for(int k=4;k<16;k++){
                if (Image[i+listPoints[k]][j+listPoints[k]] > Image[i][j] + threshold){
                    bright = bright +1 ;
                }
                else if(Image[i+listPoints[k]][j+listPoints[k]] < Image[i][j] - threshold){
                    dim = dim +1;
                }
                else{}

                if (bright>=Npoints || dim>= Npoints){
                    keypoints.push_back({i,j});
                }
                else{}
            }

            else{
                //skip
            }
        }
    }
    // The corners are given orientation by corner_orientation function
    return keypoints;
}


float rBRIEF(){





}

float FAST(){






}


float ORB(){



}


