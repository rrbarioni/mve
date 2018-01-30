#ifndef SFM_ORB_HEADER
#define SFM_ORB_HEADER

#include <iostream>
#include <vector>

#include "math/vector.h"
#include "mve/image.h"
#include "sfm/defines.h"

#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"

SFM_NAMESPACE_BEGIN

class Orb
{
public:

	struct Options
	{
		Options (void);
	};

	struct Keypoint
	{
		float x;
		float y;
	};

	struct Descriptor
	{
		float x;
		float y;
		float scale;
		float orientation;
		math::Vector<float, 32> data;
	};

public:
	typedef std::vector<Keypoint> Keypoints;
	typedef std::vector<Descriptor> Descriptors;

public:
	explicit Orb (Options const& options);

	void set_image (mve::ByteImage::ConstPtr image);

	void process (void);

	Keypoints const& get_keypoints (void) const;

	Descriptors const& get_descriptors (void) const;

protected:
	struct Octave
	{

	};

protected:
	typedef std::vector<Octave> Octaves;

private:
	Options options;
	cv::Mat image;
	Octaves octaves;
	Keypoints keypoints;
	Descriptors descriptors;
};

/* ---------------------------------------------------------------- */

inline
Orb::Options::Options(void)
{
}

inline Orb::Keypoints const&
Orb::get_keypoints(void) const
{
	return this->keypoints;
}

inline Orb::Descriptors const&
Orb::get_descriptors(void) const
{
	return this->descriptors;
}

SFM_NAMESPACE_END

#endif /* SFM_ORB_HEADER */