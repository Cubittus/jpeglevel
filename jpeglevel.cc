#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <regex>
#include <filesystem>

#include <turbojpeg.h>

namespace fs = std::filesystem;

using std::cout, std::cerr, std::endl;
using std::string;
using std::list;

// --- JPEGFile -----------------------------------------------------------------------------------------------------------

class JPEGFile // A JPEGFile in memory
{
private:
	JPEGFile(const JPEGFile &) = delete;
	JPEGFile(const JPEGFile &&) = delete;
	JPEGFile & operator=(const JPEGFile &) = delete;
	JPEGFile & operator=(const JPEGFile &&) = delete;

	unsigned char *file_data { nullptr };
	fs::path file_name {};
	size_t file_size { 0 };
	bool data_on_disk { false }; // True when it is known that the data on disk == data in memory

public:
	JPEGFile() {}
	JPEGFile(const string &filename) { name(filename); }
	JPEGFile(const unsigned char *newd, size_t news) { newdata(newd, news); }
	~JPEGFile();

	string name() { return file_name; }
	void name(const string &filename) { file_name = filename; data_on_disk = false; }

	bool load();
	unsigned char *newdata(const unsigned char *newd, size_t news);

	bool save(bool overwrite = false);

	unsigned char *data(bool willwrite = false) { return file_data; if (willwrite) data_on_disk = false; }
	size_t size() { if (file_size) return file_size; else if (load()) return file_size; else return 0; }
	bool saved() { return data_on_disk; }

};

JPEGFile::~JPEGFile()
{
	if (file_data)
		delete [] file_data;
}

unsigned char *JPEGFile::newdata(const unsigned char *newd, size_t news)
{
	if (file_data)
		delete [] file_data;
	file_data = nullptr;
	file_size = news;
	file_data = new unsigned char [ news ];
	std::memcpy(file_data, newd, news);
	data_on_disk = false;
	return file_data;
}

bool JPEGFile::load()
{
	if (data_on_disk)
		return true;

	if (file_name.empty())
		return false;

	if (!fs::is_regular_file(file_name))
		return false;

	file_size = fs::file_size(file_name);

	if (file_size == 0)
		return false;

	if (file_data)
		delete[] file_data;

	std::ifstream fs( file_name.c_str(), std::ios::in | std::ios::binary );
	file_data = new unsigned char [ file_size + 1 ];
	fs.read(reinterpret_cast<char*>(file_data), file_size);

	data_on_disk = true;
	return true;
}

bool JPEGFile::save(bool overwrite /*= false*/)
{
	if (data_on_disk)
		return true;

	if (file_name.empty())
		return false;

	if (file_size == 0 || !file_data)
		return false;

	if (fs::exists(file_name)) {
		if (!overwrite)
			return false;
		// XXX Back up existing file ?
		// XXX Remove existing file ?
	}

	// XXX Save

	data_on_disk = true;
	return true;
}

// --- syntax -------------------------------------------------------------------------------------------------------------

static int syntax(int rc, string reason = {} )
{
	if (reason.length())
		cerr << reason << endl << endl;
	cerr << "Syntax: jpeglevel <action> [<options>] <file1.jpg> [<file2.jpg> ...]" << endl;
	cerr << "   Action / Option:" << endl;
	cerr << "      -h   --help   : Display this help" << endl;
	cerr << "      info          : Describe jpeg files" << endl;
	return rc;
}

// --- info ---------------------------------------------------------------------------------------------------------------

static int info(const list<string> &options, const list<string> &filenames)
{
	for (string option : options) {
		return syntax(1, "info option not recognised: " + option);
	}
	for (string filename : filenames) {
		JPEGFile file(filename);
		file.load();
		cout << "File : " << file.name() << endl;
		cout << "   Saved : " << file.saved() << endl;
		cout << "    Size : " << file.size() << endl;
	}
	return 0;
}

// --- main ---------------------------------------------------------------------------------------------------------------

int main(int ac, char *av[])
{
	if (ac < 2)
		return syntax(1, "You must specify an action");

	string action { av[1] };
	if (action == "-h" || action == "--help")
		return syntax(0);

	int i { 2 };
	list<string> filenames {};
	list<string> options {};
	for (i = 2; i < ac; i++) {
		string arg { av[i] };
		if (arg.ends_with(".jpg") || arg.ends_with(".jpeg") || arg.ends_with(".JPG"))
			filenames.push_back(arg);
		else if (arg.starts_with('-'))
			options.push_back(arg);
		else
			return syntax(1, "Argument not an option or jpeg filename: " + arg);
	}
	if (filenames.empty())
		return syntax(1, "No jpeg filenames specified");

	if (action == "info")
		return info(options, filenames);
	else
		return syntax(1, "No such action: " + action);

	return 0;
}

