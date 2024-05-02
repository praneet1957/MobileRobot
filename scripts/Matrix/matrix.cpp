#include "std_msgs/String.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std


class matrix{
private:
	int Rows;
	int Columns;
	float mat[Rows][Columns];




public:
	matrix(int R, int C, float data[]){
		Rows    = R
		Columns = C
		if(data!=[0]){
			for(int i=0;i<R;i++){
				for(int j=0;j<C;j++){
	               mat[i][j] = data[i][j];
				}
			}
		}

		else{
			for(int i=0;i<R;i++){
				for(int j=0;j<C;j++){
	               mat[i][j] = 0;
				}
			}
		}
	}


	matrix operator+(matrix &M){
		matrix res(Rows,Columns,[0]);


		if (Rows!=M.Rows || Columns!= M.Columns){
			cout<<"The matrix sizes are not matching";
			return 1;
			}

		else{}


		for(int i=0;i<Rows;i++){
				for(int j=0;j<Columns;j++){
	               res.mat[i][j] = mat[i][j] + M[i][j];
				}
			}

		return res; 
	}


	matrix operator-(matrix &M){
		matrix res(Rows,Columns,[0]);

		if (Rows!=M.Rows || Columns!= M.Columns){
			cout<<"The matrix sizes are not matching";
			return 1;
			}

		else{}

		for(int i=0;i<Rows;i++){
				for(int j=0;j<Columns;j++){
	               res.mat[i][j] = mat[i][j] + M[i][j];
				}
			} 

		return res;
	}


	matrix operator*(matrix &M){
		matrix res(Rows,M.Columns,[0]);

		if (Columns != M.Rows){
			cout<<"The matrix sizes are not matching";
			return 1;
			}

		else{}

		for(int i=0;i<Rows;i++){
				for(int j=0;j<Columns;j++){
	               for(int k=0;k<Columns;k++){
	               		res.mat[i][j] = res.mat[i][j] + mat[i][k]*M[k][j];
	               }
				}
			}
		return res;
	}


    

	matrix inv(){
        matrix res(Rows,Columns,[0]);

        if(Rows!=Columns){

        	cout<<"Error columns and rows are not matching"<<endl;
        }


        else
        {
        	for(int i=0;i<Rows;i++){
        		for(int j=0;j<Columns;j++){
        			matrix NewM = M.Delmat(i,j);
        			res[i][j]= pow(-1,i+j)*Cofactor(NewM);
        		}

        	}

        }
    }




    float Cofactor(matrix &M){
    	if (Rows==2){
    		cofactor = M[0][0]*M[1][1]-M[0][1]*M[1][0];
    		return cofactor
    	}
    	else{
    		for(int i=0;i<Rows;i++){
    			for(int j=0;j<Columns;j++){
    			matrix NewM = M.Delmat(i,j);
    			cofactor = cofactor + pow(-1,i+j)*M[i][j]*Cofactor(NewM);
    			}
    		}
    	}
    }


    matrix Delmat(int r,int c){
    	matrix res(Rows-1,Columns,[0]);
    	for(int i=0;i<Rows-1;i++){

    		if (i==r){
    			i=i+1;
    		}
    		else{}

    		for(int j=0;j<Columns;j++){
    			if (j==c){
    				j=j+1;
    			}

    			else{}
    			
    			res.mat[i][j] = mat[i][j];
    		}
    	}
    }



    matrix Transpose(){
    	matrix res(Columns,Rows,[0]);
    	for(int i=0;i<Rows;i++){
    			for(int j=0;j<Columns;j++){
    				res.mat[j][i] = mat[i][j];
    			}
    		}
    	return res;
    }

}


	





matrix eye(int N){
		matrix res(N,N,[0]);

		for(int i=0;i<N;i++){
			res[i][i] = 1
		}

		return res;

	}