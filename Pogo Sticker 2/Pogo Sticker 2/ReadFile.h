#ifndef READFILE_H
#define READFILE_H
#include <string>
#include <fstream>
#include <list>

class ReadFile {
public:
	ReadFile(std::string filename);
	~ReadFile();
	int readData();
	std::list<int*> getData() const;
	std::list<int*> data;
private:
	std::string filePath;
	std::ifstream map;
};

#endif