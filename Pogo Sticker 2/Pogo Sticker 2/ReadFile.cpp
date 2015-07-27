#include "ReadFile.h"

ReadFile::ReadFile(std::string filename)
{
	filePath = filename;
}

ReadFile::~ReadFile(void)
{
}

//TODO: Divide into functions
int ReadFile::readData()
{
	fileStream.open(filePath);
	std::string line;

	std::getline(fileStream, line);

	if (line == "[header]")
	{
		while (line != "[layer]")
		{
			std::getline(fileStream, line);
			int number = 0;

			std::size_t pos = line.find("=");
			std::string value = line.substr(pos + 1);
			std::string key = line.substr(0, pos);

			number = atoi(value.c_str());

			dataContext.insert(std::make_pair(key, number));
			//dataContext[&key] = &number;
		}
	}
	if (line == "[layer]")
	{
		std::getline(fileStream, line);
		std::getline(fileStream, line);

		while (!fileStream.eof())
		{
			int next;
			char dummy;
			fileStream >> next;
			fileStream >> dummy;
			data.push_back(next);
		}
	}		
	fileStream.close();
	return 0;
}

std::list<int> ReadFile::getData() const {
	return data;
}
