# Create and test the conan package locally

Having conan installed locally.

## Review the project structure

Having the following structure:

```shell script
    uri_interpreter_cpp/
    ├── CMakeLists.txt
    ├── include/
    |   ├── Foo.h
    │   └── bar
    │       └── bar.h
    ├── src/
    │   ├── main.cpp
    │   └── Foo.cpp
    │   └── bar
    │       └── bar.cpp
    └── test/
        ├── CMakeLists.txt
        ├── main.test.cpp
        └── Foo.test.cpp
        └── bar/
            └── bar.test.cpp
```

The project will generate a STATIC library.

The variables that will be used are:
- Project_name: `uri_interpreter_cpp`
- Lib_name: `liburi_interpreter_cpp.a`
- Root_path: `uri_interpreter_cpp/`
- Include_path: `uri_interpreter_cpp/include`  

## Create an example package to be modified

Create a directory, e.g. `.conan/` inside the root path of the project `uri_interpreter_cpp/`
and then run from `uri_interpreter_cpp/.conan/`

    conan new <package_name>/<version> -t
    conan new uri_interpreter_cpp/0.0.1 -t

It generates the example files:

    conanfile.py
    test_package/
        CMakeLists.txt
        conanfile.py
        example.cpp

## Modify in the main conanfile.py

1. The home URL
    ```
    url= "github existing repository path"  
    url= "https://github.com:user/repo_name.git"
    ```

2. The clone instruction. Clone the repository via https:
    ```
    def source(self)
        self.run("git clone https://github.com:user/repo_name.git")
    ```

    Or for a specific branch:
    ```
    self.run("git clone -b develop --single-branch git@github.com:user/repo_name.git")
    ```

3. The root path or path to the main `CMakeLists.txt` in `source_folder`:
    ```
    def build(self):
            cmake = CMake(self)
            cmake.configure(source_folder="uri_interpreter_cpp")
   ```

4. The include path, and lib name (for windows?)
    ```
    def package(self):
            self.copy("*.h", dst="include", src="uri_interpreter_cpp/include")
            self.copy("*uri_interpreter_cpp.lib", dst="lib", keep_path=False)
    ```

5. The libs with no prefix, and no suffix
    ```
    def package_info(self):
            self.cpp_info.libs = ["uri_interpreter_cpp"]
    ```

## Modify the test_package

1. Add in the conanfile inside test_package: (not really needed)
    ```
    requires = "uri_interpreter_cpp/0.0.1"
    ```
2. Add in `def imports(self)`:
    ```
    self.copy('*.a*', dst='', src='uri_interpreter_cpp')
    ```
3. Modify the example.cpp
    - Include the main header.
    - print a message to check if the installation was successful.

## Run the demo: 

Run the conan commands the test that the package is well formed, from `uri_interpreter_cpp/.conan/`: 

    conan create . <user>/<channel>

    conan create . demo/test
    conan create . demo/test-2

It will:

1. Run the python. If Python 2 it shows a warning: `keep going [y/N]: y`

2. Export the package recipe.
3. Load the conan configurations.
4. Run the test package
    - Install the package from the local conan cache
        - clone the repo
        - build():  
            `cmake .`  
            `cmake --build .`  
        - import(): copy the lib to the example project  
    - Build the example
        `cmake .`  
        `cmake --build .`  
    - Run the example:  
        `./example`

Note: Make sure that the configuration has the proper `libstdc++` for ABI compatibility:

    compiler.libcxx=libstdc++11

The files will be stored under:

    ~/.conan/data/uri_interpreter_cpp/0.0.1/
        demo/
            test/
            test-2/

And the lib will be copied to the example's `build/` folder


## For versioning

1. Create config.yml
    ```
    versions:
      0.0.1:
        folder: versions
      0.0.2:
        folder: versions
    ```

2. Inside versions/ create conandata.yml with SHAs for each release
    ```
    sources:
      0.0.1:
        url: https://github.com/repo/v0.0.1.tar.gz
        sha256: 54BE...A13BDA
      0.0.2:
        url: https://github.com/repo/v0.0.2.tar.gz
        sha256: 54BE...A13BDB
    ```

3. Remove version from conanfile.py

---

See example: [catch2 recipe](https://github.com/conan-io/conan-center-index/tree/master/recipes/catch2)
