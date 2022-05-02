#include <iostream>
#include <string>
#include <list>
#include <regex>

#include <turbojpeg.h>


using std::cout, std::cerr, std::endl;
using std::string;
using std::list;

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

static int info(const list<string> &options, const list<string> &filenames)
{
	for (string option : options) {
		return syntax(1, "info option not recognised: " + option);
	}
	for (string filename : filenames) {
		cout << "File : " << filename << endl;
	}
	return 0;
}

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

