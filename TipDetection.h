////////////////////////////////////////////////////////////////////////////////////
////	Name: PHAM Truong An
////	Goal: This class is used for detecting pointing tip of a human hand
////	Algorithm: J. Segen and S. Kumar in the paper: "Shadow Gestures: 3D Hand Pose Estimation using a Single Camera"
////	version: 1.0.0
////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ReadImage.h"

using namespace std;
using namespace cv;

class CTipDetection
{
private:
	Point2f tip;
	int threshold_peak=20;
public:
	CTipDetection();
	vector<vector<Point>> contourDetect(Mat img);						// detect the contour (geometry) of human hand
	vector<Point2f> extractExtrema(vector<vector<Point>> contours);		// extract peaks and valleys in convexhull shape of human hand
	void searchTip(Mat img);
	~CTipDetection();
};

