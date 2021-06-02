from conans import ConanFile, CMake, tools

class UriiConan(ConanFile):
    name = "urii"
    version = "0.0.1"
    license = "MIT"
    author = "Juan Jose Castellanos juanchocaste@gmail.com"
    url = "https://github.com/spjuanjoc/uri_interpreter_cpp"
    description = "Interpreter to lex and parse URI"
    topics = ("conan","URI", "interpreter", "lex", "parse")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/spjuanjoc/uri_interpreter_cpp")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="uri_interpreter_cpp")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="uri_interpreter_cpp/include")
        self.copy("*uri_interpreter_cpp.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["uri_interpreter_cpp"]
