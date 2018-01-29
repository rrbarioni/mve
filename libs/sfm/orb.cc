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
	std::vector<uint8_t> image_vec = image.get()->get_data();
	this->image = cv::Mat(height, width, CV_64F, cv::Scalar(0));
	//memcpy(this->image.data, image_vec.data(), image_vec.size() * sizeof(float));
	for (int h = 0; h < this->image.rows; h++) {
		for (int w = 0; w < this->image.cols; w++) {
			this->image.data[h * this->image.cols + w] = image_vec[h * this->image.cols + w];
		}
	}
}

void
Orb::process()
{
	cv::Ptr<cv::ORB> detect = cv::ORB::create();
	std::vector<cv::KeyPoint> kp1;
	cv::Mat dc1;

	detect->detectAndCompute(this->image, cv::Mat(), kp1, dc1);

	for (int i = 0; i < kp1.size(); i++) {
		Orb::Descriptor d;
		d.x = kp1[i].pt.x;
		d.y = kp1[i].pt.y;
		descriptors.push_back(d);
	}
}

SFM_NAMESPACE_END