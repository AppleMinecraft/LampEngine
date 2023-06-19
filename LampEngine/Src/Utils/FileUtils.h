#pragma once
#include <string>
#include<fstream>
#include<sstream>
#include "Core/Logger.h"

namespace LampEngine {
	class FileUtils
	{
	public:
		static std::string ReadTextFile(const char* filepath);
	};
}
