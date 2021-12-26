# jv_screenshot

C library to take screenshots in desktop environments. **Currently only X11 (linux) is supported.**

# How to integrate

The simplest way if you use CMake is to copy the `jv_screenshot` folder into your source repository.
Then, in your `CMakeLists.txt` file, add the line `add_subdirectory(path/to/jv_screenshot)`.
This will provide a target named `jv_screenshot` which you can use in `target_link_libraries()`.

Alternatively, you can add `jv_screenshot.c` and `jv_screenshot.h` to your sources, and when compiling,
ensure to link to X11 library (with GCC, flag `-lX11`).

# How to run the example

You will need CMake. Open a terminal in the root directory (where `README.md` is located)
and run the following commands:

```sh
mkdir build                # create a subdirectory 'build' where compilation will occur
cd build                   # move to 'build' subdirectory
cmake ..                   # configure the project with the root CMakeLists.txt
cmake --build .            # compile the project where we are (in 'build' subdirectory)
./jv_screenshot_example    # run the resulting executable
```

A file named `screenshot.ppm` should have appeared in the `build` subdirectory containing
a screenshot taken when the example was runned.

# How to contribute

Currently, only X11 is supported. If you have skills in Windows programming, a Windows port
would be appreciated. Any form of feedback is appreciated too.
