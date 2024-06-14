#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <matrix>
#include <cstdlib> 
#include <matrix>
#include <graph>


using namespace std;

float transform(float PointCloud, float Rot, float trans ={0,0}){
    int numPoints = size(PointCloud);
    float newPointCloud[numPoints][2];

    for(int j=0;j<numPoints; j++){
        newPointCloud[j][0] = Rot[0][0]*PointCloud[j][0] + Rot[0][1]*PointCloud[j][1] + trans[0];
        newPointCloud[j][1] = Rot[1][0]*PointCloud[j][0] + Rot[1][1]*PointCloud[j][1] + trans[1];
    }

    return newPointCloud;
}


vector<int[2]> Association(float modPointCloud1, float modPointCloud2, float Rot, float trans ){
    //Projective Data Association

    //Calculate normals at every point in cloud 2
    int numPoints2 = size(modPointCloud2);
    float newPointCloud2 = transform(modPointCloud2,Rot, trans);

    // KD tree algorithm for modPointCloud1
    int numPoints1 = size(modPointCloud1);

    //initialize starting node
    struct Node *root = NULL;
    float rootPoint[2] = modPointCloud1[numPoints1/2];
    root = insertNode(root, rootPoint);

    //generate KD tree
    for(int i=0;i<numPoints1;i++){
        if(i!=numPoints1/2){
            float point[2] = modPointCloud1[i];
            root = insertNode(root, point);
            }
        else{
        }
    }

    
    for (int j=0;j<numPoints2;j++){
        // find a corresponding point in cloud 1
        float point[2] = newPointCloud2[j];
        int depth = 0;

        //search KD tree
        if 

        


        
    }


    // returns association between 2 point clouds
}


matrix computeTransformation(vector<int[2]> associate, float &samplPointCloud1, float &samplPointCloud2){
    // Compute transform between 2 clouds using SVD or gradient based 
    


    // returns translation and rotation matrix
    
}




float errorICP(){
    //point to plane method or closest point method
    int numPoints2 = size(modPointCloud2);
    vector<float[2]> normals;

    //spline fitting can be done now doing it linearly
    for(int i=0; i<numPoints2; i++){
        float position;

        position = modPointCloud2[i];

        float segment1[2];
        float segment2[2];

        segment1 = {modPointCloud2[i][0] - modPointCloud2[i-1][0], modPointCloud2[i][1] - modPointCloud2[i-1][1] };
        segment2 = {modPointCloud2[i+1][0] - modPointCloud2[i][0], modPointCloud2[i+1][1] - modPointCloud2[i][1] };

        float normal1[2];
        float normal2[2];

        float prop = (position[0] - segment1[0])/(segment2[0]-segment1[1]);
        float norm[2] = {-(1-prop)*segment1[1],(1-prop)*segment1[0], -(prop)*segment2[1],(prop)*segment2[0]};

        normals.push_back(norm);
    }

}


float ICP(float PointCloud1, float PointCloud2, float Rot, float trans){
    // Subsampling if necessary



    // Take intersection of clouds for Association


    // Go in loop till convergence
    float error = 1000000;
    matrix globalTransform;
    

    while(error < threshold){

    // Get the association between clouds
    vector<int[2]> associate;
    matrix transform;

    associate = Association(samplPointCloud1, samplPointCloud2);

    // Get the Rotation and translation
    transform.mat = Transformation(associate, &samplPointCloud1, &samplPointCloud2, &error);

    // save the rotation and translation
    globalTransform.mat = globalTransform.mat*transform.mat;

    }

    // Compute final rotation and translation
    

    // Update map ?



}