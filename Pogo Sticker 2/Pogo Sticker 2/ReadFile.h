#ifndef READFILE_H
#define READFILE_H
#include <string>
#include <fstream>
#include <list>
#include <map>

class ReadFile {
public:
	ReadFile(std::string filename);
	~ReadFile();
	int readData();
	std::list<int> getData() const;
	std::list<int> data;
	std::map<std::string, int> dataContext;
private:
	std::string filePath;
	std::ifstream fileStream;
};

#endif