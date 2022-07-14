// Debug.h
// © 2022 Cubittus

#pragma once

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>

class Debug final
{
private:
	Debug(const Debug &) = delete;
	Debug(const Debug &&) = delete;
	Debug & operator=(const Debug &) = delete;
	Debug & operator=(const Debug &&) = delete;

	static bool initdone;
	static unsigned long int flags;
	static void init() { char *d = std::getenv("DEBUG"); if (d) flags = atoi(d); initdone = true; }

	static constexpr const char *tc_r { "\e[0m\e[K" };
	static constexpr const char *tc_c[] {
		"\e[38;2;150;150;0;48;2;30;30;0m",
		"\e[38;2;200;100;0;48;2;40;20;0m",
		"\e[38;2;210;60;60;48;2;42;12;12m",
		"\e[38;2;220;20;120;48;2;44;4;24m",
		"\e[38;2;180;30;180;48;2;36;6;36m",
		"\e[38;2;160;60;255;48;2;35;12;60m",
		"\e[38;2;120;120;255;48;2;25;25;70m",
		"\e[38;2;50;150;250;48;2;10;30;50m",
		"\e[38;2;30;180;180;48;2;6;36;36m",
		"\e[38;2;20;220;120;48;2;4;44;24m",
		"\e[38;2;60;210;60;48;2;12;42;12m",
		"\e[38;2;100;200;0;48;2;20;40;0m",
	};
	static constexpr const int tc_cn { 12 };

	unsigned long int flag { 0 };
	unsigned int flagbit { 0 };
	bool flagset { false }, head { false }, output { false };

public:
	Debug(unsigned long int f = 1) : flag(f) { if (!initdone) init(); flagset = ( flags & flag ); flagbit = static_cast<unsigned int>(std::log2(flag)); }
	~Debug() { if (output) std::cerr << tc_r << std::endl; }

	template<class T>
		Debug & operator<< ( const T &msg ) {
			if (flagset) {
				if (!head)
					std::cerr << tc_c[flagbit%tc_cn] << "Debug : " << std::setw(2) << flagbit << " : ";
				head = true;
				std::cerr << msg;
				output = true;
			}
			return *this;
		}
};

