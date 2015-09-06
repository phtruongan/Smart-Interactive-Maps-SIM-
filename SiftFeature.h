//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////	Name: PHAM Truong An
////	Module: Camera Calibration
////	Goal: Extract keypoint features from images and matching between them. 
////	Algorithm: SIFT (Scale-invariant Feature Transform)	- Reference: "Object recognition from local scale-invariant features", authors: Lowe, David G.(1999)
////	Library: Opencv_contrib (Opencv v3.0)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
class CSiftFeature
{
private:
	Ptr<Feature2D> mySift;
	int patternFlag;											// for taking a image and standard and compare with other image to reduce computation cost
	vector<KeyPoint> key_img1;									// keypoints of query image
	vector<KeyPoint> key_img2;									// keypoints of training image
	Mat descriptor_pattern;										// key descriptor of training image used only when webcam mode is activated for reducing computation 
public:
	CSiftFeature();
	CSiftFeature(int nFeatures, int nOctaves, double rejectFlat, double rejectEdge, double sigmaGau);
	Mat calculateDescriptor(Mat img,int picture);				// return a matrix of descriptors
	vector<DMatch> matchSift(Mat img1, Mat img2);				// return vector of position of matched keypoint: queryIndx on image query, trainIndx on image trained
	vector<Point2f> getGoodMatches(Mat img1, Mat img2);			// get coordinate of good-matched keypoints
	Mat drawMatch(Mat img1, Mat img2);							// draw matched keypoints for displaying
	int getPatternFlag();										// to know the SIFT algorithm in webcam mode or static 2 images mode
	void setPatternFlag(int flag);								// set the webcam mode with value of 1
	vector<KeyPoint> getKeyQuery();								// get the keypoint of query image
	vector<KeyPoint> getKeyTrain();								// get the keypoint of training image
	Point2f getLocFromImg(KeyPoint p);							// return the coordination of a keypoint on the image it belongs with
	~CSiftFeature();
};

