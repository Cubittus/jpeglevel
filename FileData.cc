// FileData.cc
// © 2022 Cubittus

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "Debug.h"
#include "FileData.h"

namespace fs = std::filesystem;

using std::string;
using std::cerr, std::endl;

FileData::~FileData()
{
	freedata();
}

void FileData::freedata()
{
	if ( my_data ) {
		if ( ! my_sync ) {
			cerr << "Warning: Unsaved FileData deleted";
			if ( my_name.empty() )
				cerr << " - no file name given";
			else
				cerr << " - has file name " << my_name;
			cerr << endl;
		}
		delete [] my_data;
	}
	my_data = nullptr;
	my_size = 0;
}

bool FileData::usedata(const unsigned char * newdata, size_t newsize)
{
	if ( ! newdata || ! newsize )
		return false;
	freedata();
	my_size = newsize;
	my_data = new unsigned char [ my_size + 1 ];
	std::memcpy( my_data, newdata, my_size );
	my_data[ my_size ] = 0;
	my_sync = false;
	return true;
}

bool FileData::load()
{
	if ( my_sync )
		return true;

	freedata();

	if ( my_name.empty() ) {
		cerr << "Not loading FileData - no filename" <<endl;
		return false;
	}

	if ( ! fs::is_regular_file( my_name ) ) {
		cerr << "Not loading FileData " << my_name << " - file not found" <<endl;
		return false;
	}

	my_size = fs::file_size( my_name );

	if ( my_size == 0 ) {
		cerr << "Not loading FileData " << my_name << " - file is empty" <<endl;
		return false;
	}
	Debug(1) << "Loading FileData " << my_name;
	std::ifstream ifs( my_name, std::ios::in | std::ios::binary );
	my_data = new unsigned char [ my_size + 1 ];
	ifs.read( reinterpret_cast< char * >( my_data ), my_size );

	my_sync = true;

	return true;
}

static fs::path findfreepath( fs::path p, string suf )
{
	fs::path fp { p };
	fp += suf;
	unsigned int n { 0 };
	while ( fs::exists( fp ) ) {
		n++;
		fp = p;
		fp += suf;
		fp += std::to_string( n );
	}
	return fp;
}

bool FileData::save( bool replace /*= false*/, bool backup /*= true*/ )
{
	if ( my_sync )
		return true;

	if ( my_name.empty() ) {
		cerr << "Not saving FileData - no filename" << endl;
		return false;
	}

	if ( my_size == 0 || ! my_data) {
		cerr << "Not saving FileData " << my_name << " - no data" << endl;
		return false;
	}

	if ( fs::exists( my_name ) ) {
		if ( ! replace ) {
			cerr << "Not saving FileData " << my_name << " - existing file" << endl;
			return false;
		}
		if ( backup ) {
			fs::path backuppath { findfreepath( my_name, "~" ) };
			cerr << "Moving replaced file " << my_name << " to " << backuppath << endl;
			fs::rename( my_name, backuppath );
		} else {
			cerr << "Removing existing file " << my_name << endl;
			fs::remove( my_name );
		}
	}

	cerr << "Saving FileData " << my_name << endl;
	std::ofstream ofs( my_name, std::ios::out | std::ios::binary );
	ofs.write( reinterpret_cast< char * >( my_data ), my_size );
	ofs.flush();

	my_sync = true;
	return true;
}

