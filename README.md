## OpenCSV
Simple CSV library written in C++
## Building
Run `cmake --build .` your root folder and it will generate a file named `libotl.a`

## Linking
- Create a folder inside your C++ project named **libs**
- Put the **libotl.a** file inside your **libs** folder
- Add to your **CMakeLists.txt** the line `target_link_libraries(*TARGET_NAME* PUBLIC libs/libotl.a)` where *TARGET_NAME* is the name of your executable target.
