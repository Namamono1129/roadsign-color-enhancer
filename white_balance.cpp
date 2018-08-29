#include "stdafx.h"
#include "calc_bound.h"
#include "opencv2/opencv.hpp"

#include <string>


using namespace std;
using namespace cv;


/*** public method ***/
void FixWhiteBalance(const Mat src_image, Mat& dest_image)
{
	/*** チャネル分割 ***/
	vector<Mat> channels;
	cv::split(src_image, channels);

	/*** パラメータ(設定改善の余地あり/オケーションに合わせる) ***/
	float mean_intensity = cv::mean(src_image.reshape(1))[0];
	float portion = mean_intensity * mean_intensity / 120000.0;

	// 先にこのへんの値を計算しておくことで高速化する
	const int num_bins = 256;
	const int num_pixels = src_image.rows * src_image.cols;	// ヒストグラムの全ビンの合計値と同じ
	const int histSize[] = { num_bins, num_pixels };
	const float range[] = { 0, 255 };
	const float* ranges[] = { range, range, range };
	const int channel_to_calc[] = { 0 };
	
	// ワンループで全処理を済ませたいのでチャネルごと処理をまとめている
	for (int i = 0; i < 3; i++)
	{
		/*** ヒストグラム計算 ***/
		Mat hist;
		cv::calcHist(&channels[i], 1, channel_to_calc, Mat(),
			hist, 1, histSize, ranges,
			true, false);

		/*** ヒストグラムから上界と下界を求める ***/
		uchar lower_bound = CalcLowerBound(hist, num_pixels, portion);
		uchar higher_bound = CalcUpperBound(hist, num_pixels, portion);

		float scale_factor = (255.0 / (higher_bound - lower_bound));

		cv::subtract(channels[i], lower_bound, channels[i]);
		cv::multiply(channels[i], scale_factor, channels[i]);
	}

	cv::merge(channels, dest_image);

}