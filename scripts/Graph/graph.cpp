#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <matrix>
#include <cstdlib> 
#include <matrix>

using namespace std;
const int k = 2;

struct Node
{
    float point[k];
    Node *left, *right;
}

struct Node* newNode(int arr[]){
    struct Node* temp = new Node;
    for(int j=0; j<k; j++){
        temp->point[i] = arr[i];
    }

    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Node *insertRecursive(Node *root, float point[], int depth){
    if (root == NULL){
        return newNode(point);
    }

    int cd = depth % k; // to comapre the co-ordinates

    if (point[cd]< root->point[cd]){
        root->left = insert(root->left, point, depth+1);
    }
    else{
        root->right = insert(root->right, point, depth+1);
    }

    return root;
}


Node *insertNode(Node *root, float point[]){
    return insert(root, point ,0);
}

bool searchRecursive(Node *root, int point[], int depth){
    if (root == NULL){
        return false;
    }

    if(samePoints(root-> point, point)){
        return true;
    }

    int cd = depth % k;

    if (point[cd] < root->point[cd]){
        return searchRecursive(root->left, point, depth+1);
    }
    else{
        return searchRecursive(root->right, point, depth+1);
    }

    return false;
}


bool search(Node *root, int point[]){
    return searchRecursive(root,point,0);
}


