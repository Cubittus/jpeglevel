// JPEGFile.cc
// © 2022 Cubittus

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "JPEGFile.h"

namespace fs = std::filesystem;

using std::string;
using std::cerr, std::endl;

JPEGFile::~JPEGFile()
{
	freedata();
}

void JPEGFile::freedata()
{
	if ( my_data ) {
		if ( ! my_safe ) {
			cerr << "Warning: Unsaved JPEGFile data deleted";
			if ( my_name.empty() )
				cerr << " - no file name given";
			else
				cerr << " - original loaded from file " << my_name;
			cerr << endl;
		}
		delete [] my_data;
	}
	my_data = nullptr;
	my_size = 0;
}

bool JPEGFile::copydata(const unsigned char * newdata, size_t newsize)
{
	if ( ! newdata || ! newsize )
		return false;
	freedata();
	my_size = newsize;
	my_data = new unsigned char [ my_size + 1 ];
	std::memcpy( my_data, newdata, my_size );
	my_data[ my_size ] = 0;
	my_safe = false;
	return true;
}

bool JPEGFile::load()
{
	if ( my_safe )
		return true;

	freedata();

	if ( my_name.empty() )
		return false;

	if ( ! fs::is_regular_file( my_name ) )
		return false;

	my_size = fs::file_size( my_name );

	if ( my_size == 0 )
		return false;

	std::ifstream ifs( my_name, std::ios::in | std::ios::binary );
	my_data = new unsigned char [ my_size + 1 ];
	ifs.read( reinterpret_cast< char * >( my_data ), my_size );

	my_safe = true;

	return true;
}

bool JPEGFile::save( bool overwrite /*= false*/ )
{
	if ( my_safe )
		return true;

	if ( my_name.empty() )
		return false;

	if ( my_size == 0 || ! my_data)
		return false;

	if ( fs::exists( my_name ) ) {
		if ( ! overwrite )
			return false;
		// XXX Back up existing file ?
		// XXX Remove existing file ?
	}

	// XXX Save

	my_safe = true;
	return true;
}

