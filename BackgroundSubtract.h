//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////	Name: PHAM Truong An
////	Module: Background Subtraction
////	Goal: subtract the scene for obtaining the hand or pointing device on the image captured by camera.
////	Algorithm: Codebook -  Reference: "Background modeling and subtraction by codebook construction", authors: Kyungnam Kim et al.	
////	Version: 1.0.0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "CodeWord.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace std;
using namespace cv;

class CBackgroundSubtract
{
private:
	vector<CCodeWord>* codeBook;					// codebook is a vector of codewords
	int time = 1;									// time t of each picture
	int number = 0;									// number of pixels on the scene
public:
	CBackgroundSubtract();						
	void runTraining(string file);
	void trainStaticImages(string file);								// Train from several static images listed in text file path 
	void trainRealTime();												// Train in real time through webcam : not implemented yet
	
	bool searchOnCodeBook(CCodeWord newWord, int idx, int type);		// true: means update existing codeword. false: means plus one more codeword
	
	Mat subtractBackground(Mat img);									// testing subtract backgrounds
	~CBackgroundSubtract();
};

