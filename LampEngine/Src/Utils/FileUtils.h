#pragma once	
#include <string>

namespace LampEngine {

	// FileUtils class provides useful function related to files or filepaths
	class FileUtils {
	public:
		// Reads a text file and returns its content.
		static std::string ReadTextFile(std::string filePath);

		// Returns the extension of filePath.
		// Example: GetFileExtension("MyFolder/MyFile.txt") returns "txt"
		static std::string GetFileExtension(std::string filePath);

		// Returns trur if a file exists at the gives path.
		static bool FileExists(std::string filePath);
	};
}
