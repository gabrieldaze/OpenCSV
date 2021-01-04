/* OpenCSV - CSV Library for C++
 * 
 * Author: Gabriel D. Azevedo
 * Date: 2020-10-20
 */

#ifndef OTL_LIB
#define OTL_LIB

#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

namespace otl {
  int indexOf(const std::string &pString, const std::string &pSearch);

  int countChar(const std::string &pString, const char &pChar);

  std::vector<std::string> splitString(const std::string &pString, const char &pDivider);

  std::string joinString(std::vector<std::string> pStringList, const char &pDivider);

  class CSV {
  public:
    CSV(const std::string &pFileName);
    ~CSV();

    std::vector<std::string> GetHeaders();
    void PushHeader(const std::string &pHeader);
    std::string PopHeader();
    std::string GetHeader(int pIndex);
    int GetHeaderIndex(const std::string &pHeader);

    void PushLine(const std::string &pLine);
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
