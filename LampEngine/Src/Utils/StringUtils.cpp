#include "StringUtils.h"

namespace LampEngine {
	std::string StringUtils::GetFirstToken(std::string str) {
		if (!str.empty()) {
			size_t tokenStartPosition = str.find_first_not_of(" \t");
			size_t tokenEndPosition = str.find_first_of(" \t", tokenStartPosition);
			if (tokenStartPosition != std::string::npos && tokenEndPosition != std::string::npos)
				return str.substr(tokenStartPosition, tokenEndPosition - tokenStartPosition);
			else if (tokenStartPosition != std::string::npos)
				return str.substr(tokenStartPosition);
		}
		return ""; // Return empty string if input is empty.
	}
	std::string StringUtils::GetTail(std::string str) {
		if (!str.empty()) {
			size_t tokenStartPosition = str.find_first_not_of(" \t");
			size_t spaceStartPosition = str.find_first_of(" \t", tokenStartPosition);
			size_t tailStartPosition = str.find_first_not_of(" \t", spaceStartPosition);
			size_t tailEnd = str.find_last_not_of(" \t");
			if (tailStartPosition != std::string::npos && tailEnd != std::string::npos)
				return str.substr(tailStartPosition, tailEnd - tailStartPosition + 1);
			else if (tailStartPosition != std::string::npos)
				return str.substr(tailStartPosition);
			return ""; // Return empty string if only one word/token
		}
		return ""; // Return empty string if str is empty
	}
	void StringUtils::Split(std::string str, std::vector<std::string>& outStr, std::string token) {
		// Clear any existing data of outStr
		outStr.clear();
		// Temporary string
		std::string temp;

		// Looping throught the str word by word
		for (int i = 0; i < str.size(); i++) {
			// Current word plus next x words, x = size of token
			std::string test = str.substr(i, token.size());

			// If token found
			if (test == token) {
				if (!temp.empty()) {
					outStr.push_back(temp);
					temp.clear();
					i += token.size() - 1;
				} else outStr.push_back("");
			} else if (i + token.size() >= str.size()) {
				temp += str.substr(i, token.size());
				outStr.push_back(temp);
				break;
			} else temp += str[i];
		}
	}
}