// FileData.h
// © 2022 Cubittus

#pragma once

#include <string>
#include <filesystem>

// --- FileData -----------------------------------------------------------------------------------------------------------

class FileData // A file in memory and/or on disk
{
private:
	FileData(const FileData &) = delete;
	FileData(const FileData &&) = delete;
	FileData & operator=(const FileData &) = delete;
	FileData & operator=(const FileData &&) = delete;

	unsigned char * my_data { nullptr };
	std::filesystem::path my_name { };
	size_t my_size { 0 };
	bool my_safe { false }; // True when it is known that the data on disk == data in memory

	void freedata();

public:
	FileData() { }
	FileData(const std::string & filename) : my_name(filename) { }
	FileData(const unsigned char * newdata, size_t newsize) { usedata(newdata, newsize); }
	virtual ~FileData();

	virtual std::string name() const final { return my_name; }
	virtual void name(const std::string & filename) final { my_name = filename; my_safe = false; }

	virtual bool load() final;
	virtual bool usedata(const unsigned char * newdata, size_t newsize) final;

	virtual bool save(bool replace = false, bool backup = true) final;
	virtual void discard() final { my_safe = true; freedata(); }

	virtual size_t size() final { if ( my_size ) return my_size; else if ( load() ) return my_size; else return 0; }
	virtual unsigned char *readdata() final { if (my_data) return my_data; else if ( load() ) return my_data; else return nullptr; }
	virtual unsigned char *data() final { my_safe = false; if (my_data) return my_data; else if ( load() ) return my_data; else return nullptr; }

	virtual bool safe() const final { return my_safe; }

};

