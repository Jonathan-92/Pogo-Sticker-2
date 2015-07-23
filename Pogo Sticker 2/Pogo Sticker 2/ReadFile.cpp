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
	map.open(filePath);
	std::string line;

	std::getline(map, line);

	if (line == "[header]")
	{
		while (line != "[layer]")
		{
			std::getline(map, line);
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
		std::getline(map, line);
		std::getline(map, line);

		while (!map.eof())
		{
			int next;
			char dummy;
			map >> next;
			map >> dummy;
			data.push_back(next);
		}
	}		
	map.close();
	return 0;
}

std::list<int> ReadFile::getData() const {
	return data;
}
