
CMakeLists.txt
```
add_subdirectory(/path/to/lib)
add_executable(test_ext_proc your_program.cpp)
target_link_libraries(test_ext_proc external_processes)
```
