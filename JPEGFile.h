// JPEGFile.h
// © 2022 Cubittus

#pragma once

#include <string>
#include <filesystem>

// --- JPEGFile -----------------------------------------------------------------------------------------------------------

class JPEGFile // A JPEG file in memory and/or on disk
{
private:
	JPEGFile(const JPEGFile &) = delete;
	JPEGFile(const JPEGFile &&) = delete;
	JPEGFile & operator=(const JPEGFile &) = delete;
	JPEGFile & operator=(const JPEGFile &&) = delete;

	unsigned char * my_data { nullptr };
	std::filesystem::path my_name { };
	size_t my_size { 0 };
	bool my_safe { false }; // True when it is known that the data on disk == data in memory

	void freedata();

public:
	JPEGFile() { }
	JPEGFile(const std::string & filename) : my_name(filename) { }
	JPEGFile(const unsigned char * newdata, size_t newsize) { copydata(newdata, newsize); }
	~JPEGFile();

	std::string name() { return my_name; }
	void name(const std::string & filename) { my_name = filename; my_safe = false; }

	bool load();
	bool copydata(const unsigned char * newdata, size_t newsize);

	bool save(bool replace = false, bool backup = true);
	bool discard();

	bool getdata(unsigned char ** dataptr) { *dataptr = ( size() ) ? my_data : nullptr; my_safe = false; return *dataptr != nullptr; }
	bool getdata(const unsigned char ** dataptr) { *dataptr = ( size() ) ? my_data : nullptr; return *dataptr != nullptr; }

	size_t size() { if ( my_size ) return my_size; else if ( load() ) return my_size; else return 0; }
	bool safe() { return my_safe; }

};

