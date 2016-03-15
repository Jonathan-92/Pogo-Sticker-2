#ifndef TEXTURE_H
#define TEXTURE_H
#include "ViewPort.h"

namespace gameEngine
{
	class Texture
	{
		public:
			bool loadTextureFromFile(std::string path);
	};
}

#endif