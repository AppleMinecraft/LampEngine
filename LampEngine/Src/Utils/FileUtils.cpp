#include "FileUtils.h"

namespace LampEngine {
	std::string FileUtils::ReadTextFile(const char* filepath) {
		std::ifstream file(filepath, std::ios::binary);
		if (file) {
			std::string contents;
			file.seekg(0, std::ios::end);
			contents.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&contents[0], contents.size());
			file.close();
			LOGdebug("A File Has Been Loaded At '{0}'.", filepath);
			return(contents);
		}
		LOGerror("File Failed To Load At '{0}'!", filepath);
		return "";
	}
}