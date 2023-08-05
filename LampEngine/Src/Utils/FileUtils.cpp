#include "FileUtils.h"
#include <fstream>
#include <sstream>
#include "Core/Logger.h"

namespace LampEngine {
	std::string FileUtils::ReadTextFile(std::string filePath) {
		LOGdebug("Loading A File At '{0}'.", filePath);
		std::ifstream file(filePath, std::ios::binary);
		if (file) {
			std::string contents;
			file.seekg(0, std::ios::end);
			contents.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&contents[0], contents.size());
			file.close();
			return(contents);
		} 
		LOGerror("File Failed To Load At '{0}'!", filePath);
		return ""; // Return empty string if file failed to load.
	}
	std::string FileUtils::GetFileExtension(std::string filePath) {
		size_t fileExtensionPosition = filePath.find_last_of(".");
		if (fileExtensionPosition == std::string::npos)
			return ""; // Return empty string if file does not have a extension.
		std::string fileExtension = filePath.substr(fileExtensionPosition + 1);
		return fileExtension;
	}
	bool FileUtils::FileExists(std::string filePath) {
		std::ifstream file(filePath);
		return file.good();
	}
}