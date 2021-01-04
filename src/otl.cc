/* OpenCSV - CSV Library for C++
 * 
 * Author: Gabriel D. Azevedo
 * Date: 2020-10-20
 */

#include "otl.h"

otl::CSV::CSV(const std::string &pFileName) {
  this->mFileStream = std::fstream();
  this->mFileName = pFileName;
}

otl::CSV::~CSV() {}

int otl::indexOf(const std::string &pString, const std::string &pSearch) {
  std::size_t searchPosition = pString.find(pSearch);
  if (searchPosition == std::string::npos) return -1;
  return (int) searchPosition;
}

int otl::countChar(const std::string &pString, const char &pChar) {
  int charCount = 0;
  const char* charArray = pString.c_str();
  for (int i = 0; i < pString.length(); i++) {
    if (*charArray == pChar) ++charCount;
    ++charArray;
  }

  return charCount;
}

std::vector<std::string> otl::splitString(const std::string &pString, const char &pDivider) {
  std::vector<std::string> divisions;
  std::string substring;

  // Checks if the last character
  // is a separator and removes it
  if (pString.at(pString.size()-1) == pDivider) {
    substring = pString.substr(0, pString.size()-1);
  } else { substring = pString; }

  // If the last character was a divider
  // then there is no divider left,
  // so the indexOf will return -1
  int divider = indexOf(substring, std::to_string(pDivider));

  while (divider > -1) {
    std::string sequence = substring.substr(0, divider);
    divisions.push_back(sequence);
    substring = substring.substr(divider + 1);
    divider = indexOf(substring, std::to_string(pDivider));
  }

  divisions.push_back(substring);
  return divisions;
}

std::string otl::joinString(std::vector<std::string> pStringList, const char &pDivider) {
  std::string joinedString = "";
  for (auto &s: pStringList) joinedString += s + pDivider;
  joinedString = joinedString.substr(0, joinedString.size()-1);
  return joinedString;
}

std::vector<std::string> otl::CSV::GetHeaders() {
  return this->mHeaders;
}

void otl::CSV::PushHeader(const std::string &pHeader) {
  this->mHeaders.push_back(pHeader);
}

std::string otl::CSV::PopHeader() {
  std::string lastHeader = this->mHeaders.back();
  this->mHeaders.pop_back();
  return lastHeader;
}

std::string otl::CSV::GetHeader(int pIndex) {
  return this->mHeaders.at(pIndex);
}

int otl::CSV::GetHeaderIndex(const std::string &pHeader) {
  for (int i = 0; i < this->mHeaders.size(); i++) {
    if (this->mHeaders.at(i) == pHeader) return i;
  }
  return -1;
}

void otl::CSV::PushLine(const std::string &pLine) {
  this->mLines.push_back(pLine);
}

std::string otl::CSV::PopLine() {
  std::string lastLine = this->mLines.back();
  this->mLines.pop_back();
  return lastLine;
}

std::vector<std::string> otl::CSV::GetLines() {
  return this->mLines;
}

std::string otl::CSV::GetLine(int pIndex) {
  return this->mLines.at(pIndex);
}

std::string otl::CSV::GetLineValue(int pLineIndex, int pColumnIndex) {
  std::string lineString = this->GetLine(pLineIndex);
  std::vector<std::string> lineColumns = otl::splitString(lineString, ',');
  return lineColumns.at(pColumnIndex);
}

void otl::CSV::Write() {
  try {
    this->mFileStream.open(this->mFileName, std::ios::out);
    this->mFileStream << otl::joinString(this->mHeaders, ',') << "\n";
    for (auto const &l: this->mLines) this->mFileStream << l << "\n";
    this->mFileStream.close();
  } catch (const char* exception) {
    std::stringstream exceptionMessage;
    std::string systemException(exception);
    exceptionMessage << "Failed to write file " << this->mFileName << ": " << systemException;
    throw exceptionMessage;
  }
}

void otl::CSV::Read() {
  try {
    this->mFileStream.open(this->mFileName, std::ios::in);
    std::string currentLine;

    if (std::getline(this->mFileStream, currentLine)) {
      this->mHeaders = otl::splitString(currentLine, ',');
    }

    std::vector<std::string> lineList;
    while (std::getline(this->mFileStream, currentLine)) {
      lineList.push_back(currentLine);
    }
    this->mLines = lineList;
    this->mFileStream.close();
  } catch (const char* exception) {
    std::stringstream exceptionMessage;
    std::string systemException(exception);
    exceptionMessage << "Failed to read file " << this->mFileName << ": " << systemException;
  }
}
