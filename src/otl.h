/* OpenCSV - CSV Library for C++
 * 
 * Author: Gabriel D. Azevedo
 * Date: 2020-10-20
 */

#ifndef OTL_LIB
#define OTL_LIB

#include <cmath>
#include <string>
#include <vector>
#include <fstream>

namespace otl {
	int indexOf(std::string *pString, std::string pSearch);

	int countChar(std::string *pString, const char *pChar);

	std::vector<std::string> splitString(std::string pString, std::string pDivider);

	std::string joinString(std::vector<std::string> pStringList, std::string pDivider);

	class CSV {
	public:
		CSV(std::string pFileName);
		~CSV();

		std::vector<std::string> GetHeaders();
		void PushHeader(std::string pHeader);
		std::string PopHeader();
		std::string GetHeader(int pIndex);
		int GetHeaderIndex(std::string pHeader);

		void PushLine(std::string pLine);
		std::string PopLine();
		std::vector<std::string> GetLines();
		std::string GetLine(int pIndex);
		std::string GetLineValue(int pLineIndex, int pColumnIndex);

		void Write();
		void Read();

	private:
		std::fstream mFileStream;
		std::string mFileName;
		std::vector<std::string> mHeaders;
		std::vector<std::string> mLines;
	};
};

#endif
