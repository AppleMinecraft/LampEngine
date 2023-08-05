#pragma once
#include <string>
#include <vector>

namespace LampEngine {

	// StringUtils class provides useful function related to string
	class StringUtils {
	public:
		// Returns the first token/word of given str.
		// Example: GetFirstToken("This is a Example string") returns "This"
		static std::string GetFirstToken(std::string str);

		// Returns the str but leaving the first word/token from it.
		// Example: GetTail("This is a Example string") returns "is a Example string"
		// Mostly used in ObjLoader.
		static std::string GetTail(std::string str);

		// Splits the string into a array of string, it splits the string from token
		// Example: Split("This is a Example string", (std::vector of std::string), " ") sets the (std::vector of std::string) to ["This", "is", "a", "Example", "string"]
		static void Split(std::string str, std::vector<std::string>& outStr, std::string token);
	};
}

