#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <matrix>
#include <cstdlib> 
#include <matrix>
#include <graph>
#include <math>


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
            root = insertNode(root, point, i);
            }
        else{
        }
    }

    int pairs[numPoints2][2];
    for (int j=0;j<numPoints2;j++){
        // find a corresponding point in cloud 1
        float point[2] = newPointCloud2[j];
        int depth = 0;

        //search KD tree
        float res[] = searchKD(root, depth, point);

        //pairs of cloud1, cloud2
        pairs[j] = {res[0], j}  ; 
    }

    return pairs;
    // returns association between 2 point clouds
}


float searchKD(root, depth, point, minDis=100000){
    int cd = depth % 2;

    if (root-> left == NULL and root->right== NULL){

        float minDisNew=0;

        //calculate distance
        for(int i=0; i<k, i++){
        minDisNew += (root->point[i] - point[i])*(root->point[i] - point[i]) ;
        }

        float result[] = {root->index, minDisNew, depth};
        return result;
    }

    if (point[cd] < root->point[cd]){
        float resultLeft[] = searchKD(root-> left, depth + 1, point);

        if resultLeft[1] > abs(point[cd] - root->point[cd]){
            return searchKD(root-> right, depth + 1, point);
        }
        
        return resultLeft;
    }

    else{
        float resultRight[] searchKD(root-> right, depth + 1, point);

        if resultRight[1] > abs(point[cd] - root->point[cd]){
            return searchKD(root-> left, depth + 1, point);
        }

        return resultRight;
    }

    return 0;
}


matrix Rot(theta){
    matrix rotMatrix;
    rotMatrix.mat = {{cos(theta), -sin(theta)},{sin(theta), cos(theta)}};
    return rotMatrix;
}


matrix computeTransformation(vector<int[2]> associate, float &samplPointCloud1, float &samplPointCloud2){
    // Compute transform between 2 clouds using SVD or gradient based 
    int numPoint = size(samplePointCloud1);
    float err ;

    // will use gradient 
    matrix jacob;
    matrix errVec;

    //initialize parameter
    float theta=0;
    
    //jacobian calculation
    jacob.mat = {{1, 0, - sin(theta) - cos(theta)},{0 ,1 ,cos(theta)- sin(theta) }};

    matrix updateMatLeft;
    matrix updateMatRight;


    for(int i=0; i<numPoint; i++){
        updateMatLeft += jacob.transpose()*jacob;
        updateMatRight += jacob.transpose()*err ;
    }

    //calculating increment 
    matrix delta;
    delta = -updateMatLeft.inv()*updateMatRight;

    // compute error
    for(int i=0; i<numPoint; i++){
        matrix point, transVec, targetPoint;
        theta = delta.mat[2][0];
        point.mat = {{samplePointCloud2[i][0]},{samplePointCloud2[i][1]}};
        transVec.mat = {{delta.mat[0][0]},{delta.mat[1][0]}};
        targetPoint.mat = {{samplePointCloud1[associate[i]][0]},{samplePointCloud1[associate[i]][1]}};
        errVec = Rot(theta)*point + transVec - targetPoint;
        err = (errVec.transpose()*errVec).mat[0];
    }

    // returns translation and rotation parameters
    return delta;
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
    float threshold = 10;

    matrix transform;
    matrix globalTransform;
    matrix parameter;

    //Initialize parameter
    globalTransform.mat = {0,0,0};

    

    while(error < threshold){

        // Get the association between clouds
        vector<int[2]> associate;
        matrix transform;

        associate = Association(samplPointCloud1, samplPointCloud2);

        // Get the Rotation and translation 
        transform = computeTransformation(associate, &samplPointCloud1, &samplPointCloud2, &error);

        // save the rotation and translation
        globalTransform += transform;

    }

    // Compute final rotation and translation
    matrix RotMat;
    RotMat = Rot(globalTransform.mat[2][0]);
    samplPointCloud2 = transform(samplPointCloud2,RotMat,{globalTransform.mat[0][0],globalTransform.mat[1][0]});




    // Update map ?


}
