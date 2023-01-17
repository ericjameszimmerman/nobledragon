from conans import ConanFile, CMake, tools

class AppConan(ConanFile):
    name = "chip-lpc-175x-6x"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
