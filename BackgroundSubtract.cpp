#include "BackgroundSubtract.h"



CBackgroundSubtract::CBackgroundSubtract()
{
}

void CBackgroundSubtract::runTraining(string file)
{
	string file_name;
	ifstream in;

	in.open("background_subtract.txt");				// open file for collection of path to static files to train
	while (!in.eof)
	{
		getline(in, file_name);
		trainStaticImages(file_name);				// train this background
		time++;							
	}

	in.close();
}

void CBackgroundSubtract::trainStaticImages(string file)
{
	Mat img = imread(file);
	int rows = img.rows;
	int cols = img.cols;
	CCodeWord* word;
	float rgb[3] = {0,0,0};
	int bright = 0;

	// allocate the codebook for all pixels of the image only one time
	if (time == 1)
	{
		number = rows*cols;
		codeBook = new vector<CCodeWord>[number];
	}
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			rgb[0] = img.at<cv::Vec3b>(i, j)[2];
			rgb[1] = img.at<cv::Vec3b>(i, j)[1];
			rgb[2] = img.at<cv::Vec3b>(i, j)[0];

			// Calculate the brightness of the pixel by R G B: bright = R + G + B
			bright = rgb[0] + rgb[1] + rgb[2];							

			// create a new temp codeword
			word = new CCodeWord(rgb,bright,bright,1,time-1,time,time);
			
			// if not find the codeword in the codebook
			if (!trainCodeBook(*word, i*cols + j))
			{
				cout << "Added new codeword!!!!!!!!!!" << endl;
			}
			delete word;
		}
	}
}


void CBackgroundSubtract::trainRealTime()
{
}

bool CBackgroundSubtract::searchOnCodeBook(CCodeWord newWord,int idx, int type)
{
	for (int i = 0; i < codeBook[idx].size(); i++)
	{
		if (codeBook[idx].at(i).compareCodeWord(newWord))
		{
			// update the codeword by some information of this newword
			codeBook[idx].at(i).updateCodeWord(newWord);
			return true;
		}
	}

	// add new codeword to our codebook of this pixel idx
	if(type == 1)
		codeBook[idx].push_back(newWord);
	return false;
}

Mat CBackgroundSubtract::subtractBackground(Mat img)
{
	int rows = img.rows;
	int cols = img.cols;
	CCodeWord* word;
	float rgb[3] = { 0,0,0 };
	int bright = 0;
	Mat bgk_sub = Mat::zeros(rows,cols,CV_32F);

	// we consider test image as a tranining image but just updating the RGB and 6-tuple information, not adding
	time++; 

	// allocate the codebook for all pixels of the image only one time
	if (time == 1)
	{
		number = rows*cols;
		codeBook = new vector<CCodeWord>[number];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			rgb[0] = img.at<cv::Vec3b>(i, j)[2];
			rgb[1] = img.at<cv::Vec3b>(i, j)[1];
			rgb[2] = img.at<cv::Vec3b>(i, j)[0];

			// Calculate the brightness of the pixel by R G B: bright = R + G + B
			bright = rgb[0] + rgb[1] + rgb[2];

			// create a new temp codeword
			word = new CCodeWord(rgb, bright, bright, 1, time - 1, time, time);

			// if find the codeword in the codebook
			if (searchOnCodeBook(*word, i*cols + j, 2))
			{
				bgk_sub.at<float>(i, j) = 0;
			}
			else
			{
				bgk_sub.at<float>(i, j) = 255;
			}
			delete word;
		}
	}
}

CBackgroundSubtract::~CBackgroundSubtract()
{
}
