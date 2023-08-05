//////////////////////////////////////////
//              Image.h                 //
// ------------------------------------ //
// This Image class contains the data   //
// of the image like the pixels not to  //
// be confused with "Texture.h" that is //
// a OpenGL specific class.             //
//////////////////////////////////////////
#pragma once

#include <cstdint>
#include <stb/stb_image.h>
#include <glm/glm.hpp>

#include "Core/Logger.h"

namespace LampEngine {

	// The Image class loads an image using stb_image or can accept manually provided raw data.
	class Image {
	public:

		Image() = default;
		/*
		* This constructor load the image using stb_image.
		* @param filepath: The path for the image to be loaded.
		* @param flip: If set to true, it flips the image. This is required because OpenGL UVs cause the image to be flipped.
		*/

		Image(std::string filepath, bool flip = false);
		/*
		* This constructor load the image using manaual data.
		* @param width: The width of the image.
		* @param height: The height of the image.
		* @param data: The raw pixel data, which can be set to null as it can be later modified using Image::setData
		*/
		Image(uint16_t width, uint16_t height, unsigned char* data = nullptr);
		~Image();
		
		// Returns a white image with a size of 1x1. This is used if no image is provided in the material for the mesh.
		static Image* GenerateWhiteImage();

		/*
		Sets the image data with the provided data.
		@param data: The data to be set.
		*/
		void setData(const char* data);

		// Return the image data.
		uint8_t*  getData() const;
		// Return the image size.
		glm::vec2 getSize() const;
		// Return the image width.
		uint16_t  getWidth() const;
		// Return the image height.
		uint16_t  getHeight() const;
	private:
		uint8_t* m_Data;
		int m_Width, m_Height;
		bool from_stbi;

		// This method frees the image data from memory, it is called on distructor
		void free();
	};
}
