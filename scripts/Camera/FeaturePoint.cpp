#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <matrix>
#include <cstdlib> 


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



vector<float> NonMaximalSuppression(vector<vector<float>> keypoints, vector<float> scores){
    int NumKeyPoints = size(keypoints);
    int MaxSuppress = 3;

    vector<vector<float>> Newkeypoints = keypoints;

    for(int j=0;j<NumKeyPoints;j++){
        for(int p=j;p<NumKeyPoints;p++){
            float dist = abs(keypoints[j][0] - keypoints[p][0]) + abs(keypoints[j][1] - keypoints[p][1]);
            if (dist < MaxSuppress){
                if (score[j] < score[p]){
                    int elementToRemove = j; 

                    // Remove the element using erase function and iterators 
                    auto it = find(Newkeypoints.begin(), Newkeypoints.end(), 
                                        elementToRemove); 
                
                    // If element is found found, erase it 
                    if (it != Newkeypoints.end()) { 
                        Newkeypoints.erase(it); 
                    } 
                }
                else
                {
                    int elementToRemove = j; 
                    // Remove the element using erase function and iterators 
                    auto it = find(Newkeypoints.begin(), Newkeypoints.end(), 
                                        elementToRemove); 
                
                    // If element is found found, erase it 
                    if (it != Newkeypoints.end()) { 
                        Newkeypoints.erase(it); 
                    }
                }
            }

            else{
                Newkeypoints.push_back(keypoints[j])
            }
        }
    }

    return Newkeypoints;

}






vector<float> oFAST(float Image, float N){
    // implementing the FAST-12 algorithm
    int Rows = size(newImage);
    int Cols = size(newImage[0]);
    float bounding_box = 7;
    float threshold    = 0.1; // intensity threshold
    int Npoints = 12 ;
    int radius = bounding_box/2;
    int MaxSuppress = 3;
    float OldImage[Rows][Cols] = Image;

    vector<vector<float>> keypoints;
    vector<float> scores;
    float scales = {1,2,4,8};

    // Detecting the keypoints
    for(int s=0; s<3;s++){
        int scale = scales[0];

        // Downscaling the image from prev one
        int newRows = Rows/scale;
        int newCols = Cols/scale;

        float newImage[newRows][newCols];

        for(int i=0;i<newRows;i++){
            for(int j=0;j<newCols;j++){
                newImage[i][j] = (OldImage[2*i][2*j] + OldImage[2*i+1][2*j] + OldImage[2*i][2*j+1] + OldImage[2*i+1][2*j+1])/4;
            }
        }



        for(int i=radius+1;i<Rows-radius-1;i++){
            for(int j=radius+1;j<Cols-radius-1;j++){

                // Hardcoding the circle for now
                float listPoints = {{0,-3},{0,3},{3,0},{-3,0},{-3,-1},{-3,1},{-2,-2},{-2,2},{-1,-3},{-1,3},{1,-3},{1,3},{2,-2},{2,2},{3,-1},{3,1}};
                int prio = {0,1,2,3};

                int bright=0; 
                int dim=0;
                float VScore = 0;
                
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
                    }

                    if (bright>=Npoints || dim>= Npoints){
                        keypoints.push_back({i*scale,j*scale});

                        for(int k=0;k<16;k++){
                            VScore += abs(Image[i][j] - Image[i+listPoints[k]][j+listPoints[k]])
                            }
                        scores.push_back(VScore);     
                    }
                    else{
                    }
                }

                else{
                    //skip
                }
            }
        }

        float OldImage[newRows][newCols] = newImage;
    }
    // The corners are given orientation by corner_orientation function
    // Non Maximal suppresion

    vector<vector<float>> Modkeypoints = NonMaximalSuppression(keypoints, scores);


    return Modkeypoints;
}


float rBRIEF(float SmoothImage, int N, int patchSize, vector<vector<float>> keypoints){
    // generating N random pairs i.e binary tests for descriptors
    int imgWidth = size(SmoothImage);
    int imgHeight = size(SmoothImage[0]);
    int indices = patchSize*patchSize;

    vector<int[]> binaryTests;
    // generation from random integers
    for(int i=0; i<N; i++){
        int random_num1 = rand() % indices;
        int random_num2 = rand() % indices;

        if (random_num2 == random_num1){
            random_num2 = rand() % indices;
        }
        else{}

        binaryTests.push_back({random_num1, random_num2});
    }

    //Get the orientation of each keypoint
    vector<float> Orientations = corner_orientation(SmoothImage, keypoints,  bounding_box);

    //Generate descriptor for every keypoint

    int numPoints = keypoints.size();
    float descriptor[numPoints][N];
    for(int k=0; k<numPoints; k++){

        //extract patch from image
        float patch[(patchSize+1)*(patchSize+1)];
        int x= keypoints[k][0];
        int y= keypoints[k][1];


        float theta = Orientations[k][0];
        //rotate the patches in main Image
        
        for(int p=0;p<=patchSize,p++){
            for(int q=0;q<=patchSize,q++){
                int xg = p+x-patchSize/2;
                int yg = q+y-patchSize/2;
                int xr = xg*cos(theta)-yg*sin(theta);
                int yr = xg*sin(theta)+yg*cos(theta);
                patch[p*(patchSize+1) + q] = SmoothImage[xr][yr] ;
            }
        }
        
        //Run binary tests on rotated patch
        for(int t=0;t<N;t++){
            if (patch[binaryTests[t][0]] > patch[binaryTests[t][1]]){
                descriptor[k][t] = 1;
            }
            else{
                descriptor[k][t] = 0;
            }
        }
    }

    return descriptor;

}

float match(float descriptor1, float descriptor2, float keypoints1, float keypoints2){
    float thresh = 10; // need to figure out
    //using hamming distance 
    int N1 = size(descriptor1);
    int N2 = size(descriptor2);

    int length = size(descriptor[0]);
    vector<int> matches;
    vector<int> matchPoses;

    for(int i=0;i<N1;i++){
        for(int j=0;j<N2;j++){
            int dist = 0;
            for(int k=0;k<length;k++){
                if (descriptor1[i][k]!= descriptor2[j][k]){
                    dist += 1;
                }
                else{}
            }
            if (dist<thresh){
                matches.push_back({i,j});
                matchPoses.push_back({keypoints1[i],keypoints2[j]});
            }
            else{}
        }
    }
    return matchPoses;

}


float ORB(){



}


