#include "sfm/orb.h"

SFM_NAMESPACE_BEGIN

Orb::Orb(Options const& options)
	: options(options)
{
	
}

void
Orb::set_image(mve::ByteImage::ConstPtr image)
{
	int width = image.get()->width();
	int height = image.get()->height();
	int channels = image.get()->channels();
	std::vector<uint8_t> image_vec = image.get()->get_data();
	this->image = cv::Mat(height, width, CV_8UC3);
	
	/*
	std::cout << "image_vec.size(): " << image_vec.size() << std::endl;
	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;
	std::cout << "orig_channels: " << image.get()->channels() << std::endl;
	std::cout << "channels: " << this->image.channels() << std::endl;
	*/

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			// Things may be BGR
			int bi = h * width * channels + w * channels;
			int gi = h * width * channels + w * channels + 1;
			int ri = h * width * channels + w * channels + 2;

			this->image.data[ri] = image_vec[bi];
			this->image.data[gi] = image_vec[gi];
			this->image.data[bi] = image_vec[ri];
		}
	}

	//cv::imshow("eae", this->image);
	//cv::waitKey(0);
}

void
Orb::process()
{
	cv::Ptr<cv::ORB> detect = cv::ORB::create(10000);
	std::vector<cv::KeyPoint> kp;
	cv::Mat dc;

	detect->detectAndCompute(this->image, cv::Mat(), kp, dc);

	int dc_width = dc.cols;
	int dc_height = dc.rows;

	//cv::imshow("eae", dc);
	//cv::waitKey(0);

	for (int h = 0; h < dc_height; h++) {
		Orb::Descriptor d;
		d.x = kp[h].pt.x;
		d.y = kp[h].pt.y;
		for (int w = 0; w < dc_width; w++) {
			d.data[w] = (float)dc.data[h * dc_width + w] / 255.f;
		}
		descriptors.push_back(d);
	}
}

SFM_NAMESPACE_END