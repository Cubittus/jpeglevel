// jpeglevel.cc
// © 2022 Cubittus

#include <iostream>
#include <list>

#include <turbojpeg.h>

#include "FileData.h"

using std::string;
using std::cout, std::cerr, std::endl;
using std::list;

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
		FileData file(filename);
		file.load();
		cout << "File : " << file.name() << endl;
		cout << "   Saved : " << file.safe() << endl;
		cout << "    Size : " << file.size() << endl;
		file.name("lena-new.jpg");
		file.save(true);
	}
	return 0;
}

// --- main ---------------------------------------------------------------------------------------------------------------

static bool is_jpeg_filename(string &s)
{
	return s.ends_with(".jpg") || s.ends_with(".jpeg") || s.ends_with(".JPG") || s.ends_with(".JPEG");
}

int main(int ac, char *av[])
{
	if (ac < 2)
		return syntax(1, "You must specify an action");

	string action { av[1] };
	if (action == "-h" || action == "--help")
		return syntax(0);

	int i { 2 };
	if (is_jpeg_filename(action)) {
		action = "info";
		i = 1;
	}

	list<string> filenames {};
	list<string> options {};
	for ( ; i < ac; i++) {
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

