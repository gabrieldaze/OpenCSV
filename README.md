## OpenCSV
Simple CSV library written in C++
## Building
Run `cmake --build .` your root folder and it will generate a file named `libotl.a`

## Linking
- Create a folder inside your C++ project named **libs**
- Put the **libotl.a** file inside your **libs** folder
- Add to your **CMakeLists.txt** the line `target_link_libraries(*TARGET_NAME* PUBLIC libs/libotl.a)` where *TARGET_NAME* is the name of your executable target.

## Usage example

##### Writing a CSV file
```cpp
#include "libs/otl.h"
int main() {
  // Instantiate the CSV class with the file name
  otl::CSV *csv = new otl::CSV("MyFile.csv");

  // Initialize every column with name
  csv->PushHeader("name");
  csv->PushHeader("email");
  csv->PushHeader("job");

  // Add lines separated by comma
  csv->PushLine("John Doe,johndoe@email.com,Dummy");
  csv->PushLine("Jane Doe,janedoe@email.com,Dummy Female");
  csv->Write();

  // Free the memory you allocated for the CSV object
  delete csv;

  return 0;
}
```

##### Reading from CSV file

```cpp
#include <iostream>
#include "libs/otl.h"
int main() {
  otl::CSV *csv = new otl::CSV("MyFile.csv");
  csv->Read();

  // Print to stdout every column name first
  for (auto header: csv->GetHeaders())
    std::cout << header << "\t";
  std::cout << std::endl;

  for (int i = 0; i < csv->GetLines().size(); i++) {
    for (int j = 0; j < csv->GetHeaders().size(); j++) {
      // Print to stdout every column from current line
      std::cout << csv->GetLineValue(i, j) << "\t";
    }
    std::cout << std::endl;
  }
	
  // Free the memory you allocated for the CSV object
  delete csv;

  return 0;
}
```
