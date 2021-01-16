#include "csv.h"

ocsv::CSV::CSV(const std::string &file) {
  mFileName = file;
  mFileHandler = std::fstream();
  mSeparator = ',';
}

ocsv::CSV::CSV(const std::string &file, const char &s) {
  mFileName = file;
  mFileHandler = std::fstream();
  mSeparator = s;
}

int ocsv::CSV::index_of(const std::string &text, const std::string &search) {
  std::size_t pos = text.find(search);
  if (pos == std::string::npos) return -1;
  return (int) pos;
}

std::string ocsv::CSV::join_string(const std::vector<std::string> &list, const char &divider) {
  std::string s = "";
  for (auto &item : list) s += item + std::string(1, divider);
  s = s.substr(0, s.size() - 1);
  return s;
}

std::vector<std::string> ocsv::CSV::split_string(const std::string &text, const char &div) {
  std::vector<std::string> v;
  std::string sub, seq = "";
  const char cQuote = 0x22;
  const char cSingleQuote = 0x27;
  char quotingChar = 0x00;
  bool quoting = false;

  if (text.size() == 0) return v;
  
  if (text.at(text.size() - 1) == div) {
    sub = text.substr(0, text.size() - 1);
  } else { sub = text; }
  
  for (auto const &c: sub) {
    if (quoting) {
      if (c == quotingChar) { quotingChar = 0x00; quoting = false; }
      else { seq += std::string(1, c); }
    } else {
      if (c == cQuote || c == cSingleQuote) { quotingChar = c; quoting = true; }
      else if (c == mSeparator) { v.push_back(seq); seq = ""; }
      else { seq += std::string(1, c); }
    }
  }

  if (seq.size() > 0) v.push_back(seq);
  return v;
}


void ocsv::CSV::PushHeader(const std::string &header) {
  mHeaders.push_back(header);
}

std::string ocsv::CSV::PopHeader() {
  std::string h = mHeaders.back();
  mHeaders.pop_back();
  return h;
}

std::vector<std::string> ocsv::CSV::GetHeaders() {
  return mHeaders;
}

std::string ocsv::CSV::GetHeader(int index) {
  return mHeaders.at(index);
}

int ocsv::CSV::GetHeaderIndex(const std::string &header) {
  for (int i = 0; i < mHeaders.size(); i++)
    if (header == mHeaders.at(i)) return i;
  return -1;
}

void ocsv::CSV::PushLine(const std::string &line) {
  mLines.push_back(line);
}

std::string ocsv::CSV::PopLine() {
  std::string l = mLines.back();
  mLines.pop_back();
  return l;
}

std::vector<std::string> ocsv::CSV::GetLines() {
  return mLines;
}

std::vector<std::string> ocsv::CSV::GetLine(int index) {
  std::vector<std::string> v;
  if (index >= mLines.size())
    return v;
  v = split_string(mLines.at(index), mSeparator);
  return v;
}

std::vector<std::string> ocsv::CSV::GetLine(const std::string &line) {
  return split_string(line, mSeparator);
}

void ocsv::CSV::Read() {
  mFileHandler.open(mFileName, std::ios::in);
  std::string line;

  mHeaders.clear();
  mLines.clear();
  std::getline(mFileHandler, line);
  mHeaders = split_string(line, mSeparator);

  while (std::getline(mFileHandler, line))
    mLines.push_back(line);
  mFileHandler.close();
}

void ocsv::CSV::Write() {
  mFileHandler.open(mFileName, std::ios::out);
  mFileHandler << join_string(mHeaders, mSeparator) << "\n";
  for (auto &l : mLines) mFileHandler << l << "\n";
  mFileHandler.close();
}
