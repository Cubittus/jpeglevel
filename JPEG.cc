// JPEG.cc
// © 2022 Cubittus

#include <string>

using std::string;

#include <turbojpeg.h>
#include "JPEG.h"

const string & JPEG::subsampname(int subsamp)
{
	static const string S444     { "4:4:4 (Full chrominance)" };
	static const string S422     { "4:2:2 (2x1 chrominance)" };
	static const string S420     { "4:2:0 (2x2 chrominance)" };
	static const string SGRAY    { "Gray (no chrominance)" };
	static const string S440     { "4:4:0 (1x2 chrominance)" };
	static const string S411     { "4:1:1 (4x1 chrominance)" };
	static const string SINVALID { "INVALID" };
	switch (subsamp) {
	case TJSAMP_444:  return S444;
	case TJSAMP_422:  return S422;
	case TJSAMP_420:  return S420;
	case TJSAMP_GRAY: return SGRAY;
	case TJSAMP_440:  return S440;
	case TJSAMP_411:  return S411;
	default:          return SINVALID;
	}
}

const string & JPEG::colorspacename(int colorspace)
{
	static const string SRGB     { "RGB (Red, Green, Blue)" };
	static const string SYCbCr   { "YCbCr (Luminance, Blue Chrominance, Red Chrominance)" };
	static const string SGRAY    { "Gray (Luminance)" };
	static const string SCMYK    { "CMYK (Cyan, Magenta, Yellow, Key)" };
	static const string SYCCK    { "YCCK (Luminance, Blue Chrominance, Red Chrominance, Key)" };
	static const string SINVALID { "INVALID" };
	switch (colorspace) {
	case TJCS_RGB:   return SRGB;
	case TJCS_YCbCr: return SYCbCr;
	case TJCS_GRAY:  return SGRAY;
	case TJCS_CMYK:  return SCMYK;
	case TJCS_YCCK:  return SYCCK;
	default:         return SINVALID;
	}
}

bool JPEG::readheader()
{
	if (file.size() < 20)
		return false;

	tjhandle tjh = tjInitTransform();
	if (tjh == NULL)
		return false;

	int ret = tjDecompressHeader3(tjh, file.constdata(), file.size(), &my_width, &my_height, &my_subsamp, &my_colorspace);

	tjDestroy(tjh);

	return ret == 0;
}

bool JPEG::valid()
{
	if (my_valid)
		return true;

	if (!readheader())
		return false;

	// XXX

	my_valid = true;

	return true;
}
