## OpenCSV
Simple CSV library written in **C++**

It supports **custom delimiters** and **quoting fields**

- [Writing a file](#writing-a-csv-file)
- [Custom delimiter](#custom-delimiter)
- [Reading a file](#reading-from-csv-file)
## Building
Run `cmake --build .` your root folder and it will generate a file named `libcsv.a`

## Usage example

#### Writing a CSV file
```cpp
#include "csv.h"

int main() {
  ocsv::CSV c("myfile.csv");
  c.PushHeader("name");
  c.PushHeader("job");

  c.PushLine("gabriel,programmer");
  c.PushLine("rachell,physician");
  c.Write();
  
  return 0;
}
```
The output file after writing
```
name,job
gabriel,programmer
rachell,physician
```

#### Custom delimiter
There is a second constructor that takes a second parater which is the delimiter character
```cpp
// CSV(std::string file, const char &delimiter)
ocsv::CSV c("myfile.csv", ';');
```

#### Reading from CSV file

```cpp
#include <iostream>

#include "csv.h"

int main() {
  ocsv::CSV c("myfile.csv");
  c.Read();
  for (auto &h : c.GetHeaders())
    std::cout << h << "\t";
  std::cout << "\n";

  for (auto &ln : c.GetLines()) {
    for (auto &col : c.GetLine(ln))
      std::cout << col << "\t";
    std::cout << "\n";
  }

  return 0;
}
```
##### The output will be
```
name	job
gabriel	programmer
rachell	physician
```
