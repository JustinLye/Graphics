#include<sys/types.h>
#include<sys/stat.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#if !defined(__JLG_FREADER_HEADER__)
#define __JLG_FREADER_HEADER__


namespace jlg {
	void FileContentToString(const char* filepath, std::string& content);
	inline static bool existing_file(const char* filepath) {
		struct stat buf;
		return !(stat(filepath, &buf) < 0);
	}
};

#endif