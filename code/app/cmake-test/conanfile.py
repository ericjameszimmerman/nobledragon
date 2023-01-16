from conans import ConanFile, CMake, tools

class AppConan(ConanFile):
    name = "demo-app"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
