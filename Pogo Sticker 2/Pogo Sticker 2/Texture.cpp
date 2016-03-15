#include "Texture.h"
#include <gl/freeglut.h>

bool gameEngine::Texture::loadTextureFromFile(std::string path)
{
	//Texture loading success
	bool textureLoaded = false;

	////Generate and set current image ID
	//ILuint imgID = 0;
	//ilGenImages(1, &imgID);
	//ilBindImage(imgID);
	////Load image
	//ILboolean success = ilLoadImage(path.c_str());

	////Image loaded successfully
	//if (success == IL_TRUE)
	//{
	//	//Convert image to RGBA
	//	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	//	if (success == IL_TRUE)
	//	{
	//		//Create texture from file pixels
	//		textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
	//	}

	//	//Delete file from memory
	//	ilDeleteImages(1, &imgID);
	//}

	////Report error
	//if (!textureLoaded)
	//{
	//	printf("Unable to load %s\n", path.c_str());
	//}

	return textureLoaded;
}
