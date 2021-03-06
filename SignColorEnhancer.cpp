// SignEnhancer.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <filesystem>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "white_balance.h"
#include "color_enhance.h"

namespace fs = std::experimental::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Usage: SignColorEnhancer [input_path]" <<endl;
		return 0;
	}

	fs::path inputDir = argv[1];

	fs::path outputDir = inputDir;
	outputDir.concat("output/");
	fs::create_directory(outputDir);
	for (fs::path inputImageFp : fs::directory_iterator(inputDir))
	{
		if (!inputImageFp.has_extension())
		{
			continue;
		}

		cv::Mat image = cv::imread(inputImageFp.string(), cv::IMREAD_UNCHANGED);

		cv::Mat whitebalance_fixed;
		FixWhiteBalance(image, whitebalance_fixed);
		
		float s_thresh_percentile = 0.45;
		cv::Mat color_enhanced;
		EnhanceColor(whitebalance_fixed, color_enhanced, s_thresh_percentile);

		fs::path outputImageFp = outputDir;
		outputImageFp.concat(inputImageFp.filename().string());
		cv::imwrite(outputImageFp.string(), color_enhanced);
	}
}

