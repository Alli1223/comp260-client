#pragma once
//! Loads and renders images in the window
/*!
This class is used for all the images in the game. It loads textures from a given file location 
and can alter the image transparency if the image is a PNG.
*/
class Texture
{
public:
	//! A constructor
	/*!
	Requires a file path to load the image from
	*/
	Texture(const std::string& fileName);
	//! A destructor
	~Texture();

	//! Loads the texture
	SDL_Texture* getTexture() { return texture; }

	//! Renders the image in the window
	void render(SDL_Renderer* renderer, int x, int y, int width, int height);
	//! Alters the alpha value of the image to make it appear transparent in the window
	void alterTransparency(int transparencyLevel);

private:
	//! The image location
	std::string fileName;
	//! Pointer to the SDL Texture
	SDL_Texture* texture;
};
