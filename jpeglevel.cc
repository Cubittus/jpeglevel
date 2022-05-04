#include <iostream>
#include <string>
#include <list>
#include <regex>

#include <turbojpeg.h>

using std::cout, std::cerr, std::endl;
using std::string;
using std::list;

// --- JPEGFile -----------------------------------------------------------------------------------------------------------

class JPEGFile
{
private:
	JPEGFile(const JPEGFile &) = delete;
	JPEGFile(const JPEGFile &&) = delete;
	JPEGFile & operator=(const JPEGFile &) = delete;
	JPEGFile & operator=(const JPEGFile &&) = delete;

	unsigned char *file_data { nullptr };
	string file_name {};
	size_t file_size { 0 };
	bool file_loaded { false };

	bool load();

public:
	JPEGFile(const string &filename);
	~JPEGFile();

	size_t size();
};

JPEGFile::JPEGFile(const string &filename)
{
	file_name = filename;
}

JPEGFile::~JPEGFile()
{
	if (file_data)
		delete [] file_data;
}

bool JPEGFile::load()
{
	if (file_loaded)
		return true;

	// XXX

	file_loaded = true;
	return true;
}

size_t JPEGFile::size()
{
	load();
	return file_size;
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
		cout << "File : " << filename << endl;
		cout << "   Size : " << file.size() << endl;
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

