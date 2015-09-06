#include "Ransac.h"
#include <time.h>
#include <iostream>

using namespace std;

CRansac::CRansac()
{
}

CRansac::CRansac(vector<Point2f> keys)
{
	keypoints = keys;
	size = keypoints.size();
}

Mat CRansac::getHomography(Mat matrix1, Mat matrix2, int type) 
{
	Mat solutions;
	// solve the equation Ax = b (A is an invertible matrix)
	if (type == NON_SVD)
		solve(matrix1, matrix2, solutions, DECOMP_NORMAL);
	else
		solve(matrix1, matrix2, solutions, DECOMP_SVD);	// if the case of Ax = 0, avoid the trivial solution x = 0
	return solutions;
}


Mat CRansac::inversion(Mat matrix)
{
	// DECOMP_SVD: singular decomposition : for the case of no invertible matrices
	return matrix.inv(DECOMP_SVD); 
}

Mat CRansac::run(int iterTimes)
{
	Mat * homography = new Mat(3,3,CV_32F,Scalar(0));
	int win = 0;				// probability of inliers
	// put key vector into the following matrix
	Mat A = Mat::zeros(10,9,CV_32F);
	int idx[5];
	
	for (int i = 0; i < iterTimes; i++)
	{
		srand(time(0)); // for getting the random
		idx[0] = rand() % (size / 2);
		idx[1] = rand() % (size / 2);
		idx[2] = rand() % (size / 2);
		idx[3] = rand() % (size / 2);
		idx[4] = rand() % (size / 2);
		for (int j = 0; j < 5; j++)
		{
			// first row
			A.at<float>(j * 2, 0) = -1 * keypoints[idx[j]].x;
			A.at<float>(j * 2, 1) = -1 * keypoints[idx[j]].y;
			A.at<float>(j * 2, 2) = -1;
			A.at<float>(j * 2, 6) = keypoints[idx[j]+1].x * keypoints[idx[j]].x;
			A.at<float>(j * 2, 7) = keypoints[idx[j]].y * keypoints[idx[j]+1].x;
			A.at<float>(j * 2, 8) = keypoints[idx[j]+1].x;

			// second row
			A.at<float>(j * 2 + 1, 3) = -1 * keypoints[idx[j]].x;
			A.at<float>(j * 2 + 1, 4) = -1 * keypoints[idx[j]].y;
			A.at<float>(j * 2 + 1, 5) = -1;
			A.at<float>(j * 2 + 1, 6) = keypoints[idx[j] + 1].y * keypoints[idx[j]].x;
			A.at<float>(j * 2 + 1, 7) = keypoints[idx[j]].y * keypoints[idx[j] + 1].y;
			A.at<float>(j * 2 + 1, 8) = keypoints[idx[j] + 1].y;
		} 
		for (int rows = 0; rows < 10; rows++)
		{
			for (int cols = 0; cols < 9; cols++)
			{
				cout << A.at<float>(rows, cols) << " ; ";
			}
			cout << endl;
		}
		Mat solutions = getHomography(A, Mat::zeros(9,1,CV_32F), SVD);
		Mat homo_temp = Mat::zeros(3, 3, CV_32F);
		
		float vecs[9];
		for (int k = 0; k < 9; k++)
		{
			vecs[k] = solutions.at<float>(k, 0);
		}
		// build the matrix 3x3 transformation
		for (int z = 0; z < 3; z++)
		{
			for (int y = 0; y < 3; y++)
			{
				homo_temp.at<float>(z, y)= solutions.at<float>(z*3+y,0);
			}
		}

		// multiply this matrix with training image keypoints index+1 = estimated query image keypoints index
		Mat temp_u = Mat::ones(3, 1, CV_32F);
		Mat temp_v = Mat::ones(3, 1, CV_32F);
		Mat est_v = Mat::zeros(3, 1, CV_32F);
		int probability = 0;
		for (int m = 0; m < size / 2; m++)
		{
			temp_u.at<float>(0,0) = keypoints[m*2 + 1].x;
			temp_u.at<float>(1,0) = keypoints[m*2 + 1].y;
			temp_v.at<float>(0, 0) = keypoints[m*2].x;
			temp_v.at<float>(1, 0) = keypoints[m*2].y;

			for (int z = 0; z < 3; z++)
			{
				for (int y = 0; y < 3; y++)
				{
					cout << homo_temp.at<float>(z, y) << ";";
				}
				cout << endl;
			}
			cout << temp_u.at<float>(0, 0) << endl << temp_u.at<float>(1,0);
			// calculate the distance between estimated query image keypoints with real keypoints query
			est_v = homo_temp * temp_u;//multiply(homo_temp, temp_u, est_v, 1.0, -1);

			// Calculate the norm (magnitude) of distance between the query webcam screen with estimated one by euclidian method NORM_L2
			if (norm(est_v - temp_v,NORM_L2) < 15)
			{
				probability++;
			}
		}

		// if find a better homography matrix
		if (probability > win)
		{
			win = probability;
			*homography = homo_temp;
		}
		
	}
	
	return *homography;
}


CRansac::~CRansac()
{
}
