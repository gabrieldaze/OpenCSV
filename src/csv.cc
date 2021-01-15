#include "csv.hh"

CSV::CSV(const str &file) {
  filename = file;
  filehandler = cfile();
  separator = ',';
}

CSV::CSV(const str &file, const char &s) {
  filename = file;
  filehandler = cfile();
  separator = s;
}

int CSV::index_of(const str &text, const str &search) {
  std::size_t pos = text.find(search);
  if (pos == std::string::npos) return -1;
  return (int) pos;
}

str CSV::join_string(const vec<str> &list, const char &divider) {
  str s = "";
  for (auto &item : list) s += item + str(1, divider);
  s = s.substr(0, s.size() - 1);
  return s;
}

vec<str> CSV::split_string(const str &text, const char &div) {
  vec<str> v;
  str sub, seq;

  if (text.at(text.size() - 1) == div) {
    sub = text.substr(0, text.size() - 1);
  } else { sub = text; }

  int divider = index_of(text, std::string(1, div));
  while (divider > -1) {
    seq = sub.substr(0, divider);
    sub = sub.substr(divider + 1);
    v.push_back(seq);
    divider = index_of(sub, str(1, div));
  }

  v.push_back(sub);
  return v;
}


void CSV::PushHeader(const str &header) {
  headers.push_back(header);
}

str CSV::PopHeader() {
  str h = headers.back();
  headers.pop_back();
  return h;
}

vec<str> CSV::GetHeaders() {
  return headers;
}

str CSV::GetHeader(int index) {
  return headers.at(index);
}

int CSV::GetHeaderIndex(const str &header) {
  for (int i = 0; i < headers.size(); i++)
    if (header == headers.at(i)) return i;
  return -1;
}

void CSV::PushLine(const str &line) {
  lines.push_back(line);
}

str CSV::PopLine() {
  str l = lines.back();
  lines.pop_back();
  return l;
}

vec<str> CSV::GetLines() {
  return lines;
}

vec<str> CSV::GetLine(int index) {
  vec<str> v;
  if (index >= lines.size())
    return v;
  v = split_string(lines.at(index), separator);
  return v;
}

vec<str> CSV::GetLine(const str &line) {
  return split_string(line, separator);
}

void CSV::Read() {
  filehandler.open(filename, std::ios::in);
  str line;

  headers.clear();
  lines.clear();
  std::getline(filehandler, line);
  headers = split_string(line, separator);

  while (std::getline(filehandler, line))
    lines.push_back(line);
  filehandler.close();
}

void CSV::Write() {
  filehandler.open(filename, std::ios::out);
  filehandler << join_string(headers, separator) << "\n";
  for (auto &l : lines) filehandler << l << "\n";
  filehandler.close();
}
