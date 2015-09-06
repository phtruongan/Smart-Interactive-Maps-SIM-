#include "SiftFeature.h"
#include "SiftFeature.h"


CSiftFeature::CSiftFeature()
{
	// create a sift mechanism for extracting sift features from an image
	// 0 : nFeatures: number of best features to retain: ranked by their scores
	// 3 : nOctaveLayers: octave 1: sigma (std); octave 2: 2 sigma (std); octave 3: 3 sigma (std)
	// 0.04: contrastThreshold: or a threshold for eliminating the uniform region (flat region). Based on DoG < 0.04
	// 10: edgeThreshold: or a threshold for rejecting edges: According to Hessian matrix: r= alpha/ beta (alpha > Beta) alpha and beta is basic gradient: r < 10 means rejects edge because gradient in one direction if r > 10
	// 1.6: sigma standard deviation for gaussian mask.
	mySift = xfeatures2d::SIFT::create(100, 3, 0.04, 10, 1.6);
	patternFlag = 0;
}

CSiftFeature::CSiftFeature(int nFeatures, int nOctaves, double rejectFlat, double rejectEdge, double sigmaGau)
{
	mySift = xfeatures2d::SIFT::create(nFeatures, nOctaves, rejectFlat, rejectEdge, sigmaGau);
	patternFlag = 0;
}

Mat CSiftFeature::calculateDescriptor(Mat img,int picture)
{
	// Step 1: Detect the keypoint
	vector<KeyPoint> *keypoint = new vector<KeyPoint>();
	mySift->detect(img, *keypoint);

	// Step 2: Calculate descriptors (feature vectors)
	Mat * descriptors = new Mat();
	mySift->compute(img, *keypoint, *descriptors);

	if (picture == 1)
	{
		key_img1 = *keypoint;
	}
	else
		key_img2 = *keypoint;

	return *descriptors;
}

vector<DMatch> CSiftFeature::matchSift(Mat img1, Mat img2)
{
	// Calculate descriptors for each each image
	Mat descriptor_1 = calculateDescriptor(img1,1);
	if(patternFlag != 1)
		descriptor_pattern = calculateDescriptor(img2,2);

	// Using Brute Force matcher
	BFMatcher matcher;
	vector<DMatch> *matches= new vector<DMatch>();
	// descriptor_pattern: train descriptor
	// descriptor_1: query descriptor
	matcher.match(descriptor_1,descriptor_pattern,*matches);

	return *matches;
}

vector<Point2f> CSiftFeature::getGoodMatches(Mat img1, Mat img2)
{
	int max_dst = 0;
	int min_dst = 100;
	vector<Point2f>* goodMatches = new vector<Point2f>();
	vector<DMatch> matches = matchSift(img1, img2);
	// find the minimum distance and maximum distance  
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance > max_dst)
		{
			max_dst = matches[i].distance;
		}
		if (matches[i].distance < min_dst)
		{
			min_dst = matches[i].distance;
		}
	}
	// select matches that have the distance less than 2 * min_distance
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < 2 * min_dst)
		{
			goodMatches->push_back(getLocFromImg(key_img1[matches[i].queryIdx]));
			goodMatches->push_back(getLocFromImg(key_img2[matches[i].trainIdx]));
		}
	}
	return *goodMatches;
}

Mat CSiftFeature::drawMatch(Mat img1, Mat img2)
{
	Mat img_matched;
	// Match keypoints of two images
	vector<DMatch> matches = matchSift(img1, img2);
	// draw these keypoints of two images
	drawMatches(img1, key_img1, img2, key_img2, matches, img_matched, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	return img_matched;
}

vector<KeyPoint> CSiftFeature::getKeyQuery()
{
	return key_img1;
}

vector<KeyPoint> CSiftFeature::getKeyTrain()
{
	return key_img2;
}

int CSiftFeature::getPatternFlag()
{
	return patternFlag;
}

void CSiftFeature::setPatternFlag(int flag)
{
	patternFlag = flag;
}

Point2f CSiftFeature::getLocFromImg(KeyPoint p)
{
	return p.pt;		
}

CSiftFeature::~CSiftFeature()
{
}
