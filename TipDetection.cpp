#include "TipDetection.h"



CTipDetection::CTipDetection()
{
}

vector<vector<Point>> CTipDetection::contourDetect(Mat img)
{
	vector<vector<Point>>* contours = new vector<vector<Point>>();
	Mat img_gray, img_sobel, img_threshold, element;
	cvtColor(img, img_gray, CV_BGR2GRAY); // convert to grayscale


											// Sobel (gray image, result sobel image, depth maps, gradient X, gradient Y, Scale, Delta )
	Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);					// CV_8U is 8bits per pixels , CV_32F is float the pixel value 0-1.0

																						// calculate the threshold
																						// img_sobel: gradient image
																						// img_threshold: resulting picture after use threshold
																						// threshold value: 0
																						// Max value: 255
																						// last: 0 : Binary (>threshold -> max value, <threshold = 0), 1: Binary inverted, 2: Threshold truncated, 3: Threshold to zero, 4:Threshold to Zero inverted
	threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);

	// build structure element like morphological structure element in Image Processing (erose, dilate)
	// MORPH_RECT: rectangle
	// MORPH_ELLIPSE: ellipse
	// MORPH_CROSS: cross-shaped
	// Size(17,3): width 17, height 3
	// Optional if it is MORPH_CROSS, Point(-1,-1): position of the anchor
	element = getStructuringElement(MORPH_RECT, Size(8, 2));

	// img_threshold: input matrix for processing
	// img_threshold: output matrix
	// CV_MOP_CLOSE: type of morphology (CLOSE or OPEN)
	// element: structure for doing erose or dilation
	morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element);

	// find the contour
	// 0 = CV_RETR_EXTERNAL: retrieve only extreme outer contours 
	// 1 = CV_CHAIN_APPROX_NONE: store absolutely all the contour points into the array. 2 = CV_CHAIN_APPROX_SIMPLE: compress and leaves only their end points (rectangle just with 4 points)
	findContours(img_threshold, *contours, 0, 1);

	return (*contours);
}

vector<Point2f> CTipDetection::extractExtrema(vector<vector<Point>> contours)
{
	vector<Point2f> extrema;

	double px1 = 0;			// previous vector
	double py1 = 0;
	double px2 = 0;			// next vector
	double py2 = 0;
	double z ;				// distance between two vectors
	double V = 200 ;		// threshold value	
	Point2f tip;
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 1; j < contours[i].size()-1; j++)
		{
			px1 = contours[i].at(j).x - contours[i].at(j - 1).x;
			py1 = contours[i].at(j).y - contours[i].at(j - 1).y;
			px2 = contours[i].at(j + 1).x - contours[i].at(j).x;
			py2 = contours[i].at(j + 1).y - contours[i].at(j).y;
			z = px1 * py2 - py1 * px2;

			if (z > V)			
			{
				tip = Point2f(i,j);				// add the position of the pixel where exist the pixel.
				extrema.push_back(tip);			
			}
		}
	}

	return extrema;
}

void CTipDetection::searchTip(Mat img)
{
	vector<vector<Point>> contours = contourDetect(img);	// find the contours of human hand
	vector<Point2f> extrema = extractExtrema(contours);		//	search all extrema as possible and find the best tip
}

CTipDetection::~CTipDetection()
{
}
