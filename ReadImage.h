//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////	Name: PHAM Truong An
////	Module: General
////	Goal: Image Processing: Read Image + Convert rgb to gray image
////	Version: 1.0.0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

class CReadImage
{
private:
	Mat image;							// image of the object
public:
	CReadImage();
	CReadImage(string path);			// Read Image from a path
	CReadImage(Mat img);				// Initialize an image by copying a given image.
	Mat GetImage();						// Get image from the object
	Mat GetImageGray();
	bool SetImage(Mat img);				// Set image to the object
	bool SetImage(string path);			// Set image from the path of a file
	int DisplayImage();					// Display image of object
	~CReadImage();
};

