#include "ReadImage.h"



CReadImage::CReadImage()
{
}

CReadImage::CReadImage(string path)
{
	image = imread(path.c_str(), IMREAD_COLOR);
}

CReadImage::CReadImage(Mat img)
{
	image = img;
}

Mat CReadImage::GetImage()
{
	return image;
}

Mat CReadImage::GetImageGray()
{
	Mat img_gray;
	cvtColor(image, img_gray, CV_BGR2GRAY);
	return img_gray;
}

bool CReadImage::SetImage(Mat img)
{
	image = img;
	if (image.empty())
	{
		cout << "Could not assign the image by a given image" << endl;
		return false;
	}
	return true;
}

bool CReadImage::SetImage(string path)
{
	image = imread(path.c_str(), IMREAD_COLOR);		// c_string: convert string to char* to read image
	
	// Can't read the image from the path
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return false;
	}

	return true;
}

int CReadImage::DisplayImage()
{
	namedWindow("Display window", WINDOW_NORMAL|WINDOW_KEEPRATIO);		// WINDOW_AUTOSIZE or WINDOW_NORMAL|KEEP RATIO : resize to fit the normal windows but keep ration
	imshow("Display window", image);									// Show our image inside it.

	waitKey(0);															// Wait for a keystroke in the window
	return 0;
}

CReadImage::~CReadImage()
{
}
