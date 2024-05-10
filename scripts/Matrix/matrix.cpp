// #include "std_msgs/String.h"
#include <bits/stdc++.h>
#include <iostream>
#include <vector>


using namespace std;


class matrix{
	public:
		vector<vector<float>> mat;
		
		int rows(){
			int numrow = mat.size();
			return numrow;
		}

		int columns(){
			int numcol = mat[0].size();
			return numcol;
		}

		matrix operator+(matrix &M){
			matrix res;

			if (rows()!=M.rows() || columns()!= M.columns()){
				cout<<"The matrix sizes are not matching";
				return res;
				}

			else{}

			for(int i=0;i<rows();i++){
			vector<float> row_vec;
					for(int j=0;j<columns() ;j++){
					row_vec.push_back(mat[i][j] + M.mat[i][j]);
					}
				res.mat.push_back(row_vec); 
			}
			return res; 
		}


		matrix operator-(matrix &M){
			matrix res;

			if (rows()!=M.rows() || columns()!= M.columns()){
				cout<<"The matrix sizes are not matching";
				return res;
				}

			else{}

			for(int i=0;i<rows();i++){
				vector<float> row_vec;
					for(int j=0;j<columns() ;j++){
					row_vec.push_back(mat[i][j] - M.mat[i][j]);
					}
				res.mat.push_back(row_vec); 
			}
			return res; 
		}


		matrix operator*(matrix &M){
			matrix res;

			if (columns() != M.rows()){
				cout<<"The matrix sizes are not matching";
				return res;
				}

			else{}

			for(int i=0;i<rows();i++){
					vector<float> row_vec;
					for(int j=0;j<columns();j++){
						float res_ij=0;
						for(int k=0;k<columns();k++){
							res_ij = res_ij + mat[i][k]*M.mat[k][j];
						}
						row_vec.push_back(res_ij);
					}
					res.mat.push_back(row_vec);
				}
			return res;
		}

		//inverse is remaining.
		matrix inv(){
			matrix res;

			if(rows()!=columns()){
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

		// till here.

		matrix delrowcol(int r_start,int r_end,int c_start, int c_end){
			matrix res;
			for(int i=0;i<rows();i++){
				if (i>=r_start && i<= r_end){
					//skip
				}
				else{
					vector<float> row_vec;
					for(int j=0;j<columns();j++){
						if (j>=c_start && j<= c_end){
							//skip
						}
						else{
							row_vec.push_back(mat[i][j]);
						}
					}
					res.mat.push_back(row_vec);
				}
			}
			return res;
		}



		matrix Transpose(){
			matrix res;
			for(int i=0;i<rows();i++){
				vector<float> row_vec;
				for(int j=0;j<columns();j++){
					row_vec.push_back(mat[j][i]);
				}
				res.mat.push_back(row_vec);
			}
			return res;
		}

};


	





matrix eye(int N){
		matrix res;

		for(int i=0;i<N;i++){
			vector<float> row_vec;
			for(int j=0;j<N;j++){
				if (i!=j){
					row_vec.push_back(0.0);}
				else{
					row_vec.push_back(1.0);
				}
			}
			res.mat.push_back(row_vec);
    	}

		return res;

	}