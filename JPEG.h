// JPEG.h
// © 2022 Cubittus

#include "FileData.h"

class JPEG
{
private:
	JPEG(const JPEG &) = delete;
	JPEG(const JPEG &&) = delete;
	JPEG & operator=(const JPEG &) = delete;
	JPEG & operator=(const JPEG &&) = delete;

	FileData file {};

	bool readheader();

	bool my_valid { false };
	int my_width { 0 }, my_height { 0 }, my_subsamp { 0 }, my_colorspace { 0 };

public:
	JPEG() { }
	JPEG(const std::string & filename) : file(filename) { }
	JPEG(const unsigned char * newdata, size_t newsize) : file(newdata, newsize) { }
	virtual ~JPEG() { }

	virtual std::string name() const final { return file.name(); }
	virtual void name(const std::string & filename) final { return file.name(filename); }

	virtual size_t size() final { return file.size(); }

	bool valid();

	virtual int width() final      { if (valid()) return my_width;      else return -1; }
	virtual int height() final     { if (valid()) return my_height;     else return -1; }
	virtual int subsamp() final    { if (valid()) return my_subsamp;    else return -1; }
	virtual int colorspace() final { if (valid()) return my_colorspace; else return -1; }

	static const std::string & subsampname(int subsamp);
	static const std::string & colorspacename(int colorspace);
};

