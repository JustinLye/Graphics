#include"..\include\freader.h"

//Reads file content into character array. Returns nullptr if error occurs.
void jlg::FileContentToString(const char* filepath, std::string& content) {
	content.clear();
	std::ifstream fileStream;
	std::stringstream fileStringStream;

	fileStream.exceptions(std::ifstream::badbit);
	try {
		fileStream.open(filepath);
		fileStringStream << fileStream.rdbuf();
		fileStream.close();
		content = fileStringStream.str();
	} catch (std::ifstream::failure& e) {
		std::cerr << "ERROR::FILE READER::FAILED TO READ FILE TO CHAR ARRAY" << std::endl;
	}
}