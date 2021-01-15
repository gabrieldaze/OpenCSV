#ifndef __LIB_CSV_H__
#define __LIB_CSV_H__

#include <fstream>
#include <string>
#include <vector>

template <typename T>
using vec = std::vector<T>;
using cfile = std::fstream;
using str = std::string;

class CSV {
private:
  str filename;
  cfile filehandler;
  char separator;
  
  vec<str> headers;
  vec<str> lines;

  str join_string(const vec<str> &list, const char &divider);
  vec<str> split_string(const str &text, const char &divider);
  int index_of(const str &text, const str &search);
  
public:
  CSV(const str &filename);
  CSV(const str &filename, const char &divider);

  void PushHeader(const str &header);
  str PopHeader();
  vec<str> GetHeaders();
  str GetHeader(int index);
  int GetHeaderIndex(const str &header);

  void PushLine(const str &line);
  str PopLine();
  vec<str> GetLines();
  vec<str> GetLine(int index);
  vec<str> GetLine(const str &line);

  void Read();
  void Write();
};

#endif
