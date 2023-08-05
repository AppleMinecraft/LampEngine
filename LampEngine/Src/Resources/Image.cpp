#include "Image.h"

namespace LampEngine {
	Image::Image(std::string filepath, bool flip) :
		from_stbi(true)
	{
		LOGinfo("Loading Image at '{}'", filepath);
		stbi_set_flip_vertically_on_load(flip);
		const char* path = filepath.c_str();
		m_Data = stbi_load(path, &m_Width, &m_Height, nullptr, 4);
		if (m_Data == nullptr)
			LOGerror("Failed To Load Texture '{0}'!", filepath);
		else
			LOGdebug("Texture Had Been Loaded At '{0}' With Size Of {1}x{2}", filepath, m_Width, m_Height);
	}
	Image::Image(uint16_t width, uint16_t height, unsigned char* data):
		m_Width(width),
		m_Height(height),
		m_Data(data),
		from_stbi(false)
	{
	}
	Image::~Image() {
		free();
	}
	Image* Image::GenerateWhiteImage() {
		unsigned char* DATA = new unsigned char[1] { 0xff };
		return new Image(1, 1, DATA);
	}
	void Image::setData(const char* data) {
		data = data;
	}
	uint8_t* Image::getData() const {
		return m_Data;
	}
	glm::vec2 Image::getSize() const {
		return glm::vec2(m_Width, m_Height);
	}
	uint16_t Image::getWidth() const {
		return m_Width;
	}
	uint16_t Image::getHeight() const {
		return m_Height;
	}
	void Image::free() {
		if (from_stbi)
			stbi_image_free(m_Data);
		else
			delete m_Data;
	}
}