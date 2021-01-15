#include "csv.h"

ocsv::CSV::CSV(const std::string &file) {
  filename = file;
  filehandler = std::fstream();
  separator = ',';
}

ocsv::CSV::CSV(const std::string &file, const char &s) {
  filename = file;
  filehandler = std::fstream();
  separator = s;
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
  std::string sub, seq;

  if (text.at(text.size() - 1) == div) {
    sub = text.substr(0, text.size() - 1);
  } else { sub = text; }

  int divider = index_of(text, std::string(1, div));
  while (divider > -1) {
    seq = sub.substr(0, divider);
    sub = sub.substr(divider + 1);
    v.push_back(seq);
    divider = index_of(sub, std::string(1, div));
  }

  v.push_back(sub);
  return v;
}


void ocsv::CSV::PushHeader(const std::string &header) {
  headers.push_back(header);
}

std::string ocsv::CSV::PopHeader() {
  std::string h = headers.back();
  headers.pop_back();
  return h;
}

std::vector<std::string> ocsv::CSV::GetHeaders() {
  return headers;
}

std::string ocsv::CSV::GetHeader(int index) {
  return headers.at(index);
}

int ocsv::CSV::GetHeaderIndex(const std::string &header) {
  for (int i = 0; i < headers.size(); i++)
    if (header == headers.at(i)) return i;
  return -1;
}

void ocsv::CSV::PushLine(const std::string &line) {
  lines.push_back(line);
}

std::string ocsv::CSV::PopLine() {
  std::string l = lines.back();
  lines.pop_back();
  return l;
}

std::vector<std::string> ocsv::CSV::GetLines() {
  return lines;
}

std::vector<std::string> ocsv::CSV::GetLine(int index) {
  std::vector<std::string> v;
  if (index >= lines.size())
    return v;
  v = split_string(lines.at(index), separator);
  return v;
}

std::vector<std::string> ocsv::CSV::GetLine(const std::string &line) {
  return split_string(line, separator);
}

void ocsv::CSV::Read() {
  filehandler.open(filename, std::ios::in);
  std::string line;

  headers.clear();
  lines.clear();
  std::getline(filehandler, line);
  headers = split_string(line, separator);

  while (std::getline(filehandler, line))
    lines.push_back(line);
  filehandler.close();
}

void ocsv::CSV::Write() {
  filehandler.open(filename, std::ios::out);
  filehandler << join_string(headers, separator) << "\n";
  for (auto &l : lines) filehandler << l << "\n";
  filehandler.close();
}
