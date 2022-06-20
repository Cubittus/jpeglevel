// JPEG.h
// © 2022 Cubittus

#include "FileData.h"

class JPEG : private FileData
{
private:
	JPEG(const JPEG &) = delete;
	JPEG(const JPEG &&) = delete;
	JPEG & operator=(const JPEG &) = delete;
	JPEG & operator=(const JPEG &&) = delete;

public:
	JPEG() : FileData() { }
	JPEG(const std::string & filename) : FileData(filename) { }
	JPEG(const unsigned char * newdata, size_t newsize) : FileData(newdata, newsize) { }

	using FileData::name, FileData::size;

	bool valid() { return size() > 0; /* XXX */ }
};

