#include "ReadFile.h"

ReadFile::ReadFile(std::string filename)
{
	filePath = filename;
}

ReadFile::~ReadFile(void)
{
}

int ReadFile::readData()
{
	map.open(filePath);
	while (!map.eof())
	{
		int next;
		char dummy;
		map >> next;
		map >> dummy;
		data.push_back(&next);
	}
	map.close();
	return 0;
}

std::list<int*> ReadFile::getData() const {
	return data;
}
