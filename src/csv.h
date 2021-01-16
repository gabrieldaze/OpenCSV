#ifndef __LIB_CSV_H__
#define __LIB_CSV_H__

#include <fstream>
#include <string>
#include <vector>

namespace ocsv {
  class CSV {
  private:
    std::string              mFileName;
    std::fstream             mFileHandler;
    char                     mSeparator;
    std::vector<std::string> mHeaders;
    std::vector<std::string> mLines;

    std::string join_string(const std::vector<std::string> &list, const char &divider);
    std::vector<std::string> split_string(const std::string &text, const char &divider);
    int index_of(const std::string &text, const std::string &search);
  
  public:
    CSV(const std::string &mFileName);
    CSV(const std::string &mFileName, const char &divider);

    void PushHeader(const std::string &header);
    std::string PopHeader();
    std::vector<std::string> GetHeaders();
    std::string GetHeader(int index);
    int GetHeaderIndex(const std::string &header);

    void PushLine(const std::string &line);
    std::string PopLine();
    std::vector<std::string> GetLines();
    std::vector<std::string> GetLine(int index);
    std::vector<std::string> GetLine(const std::string &line);

    void Read();
    void Write();
  };
}

#endif
