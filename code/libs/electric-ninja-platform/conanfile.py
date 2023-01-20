from conans import ConanFile, CMake, tools

class AppConan(ConanFile):
    name = "electricninjaplatform"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False],
               "port": ["micromint-lincoln60"],
               "build_tests": [True, False]}
    default_options = {"shared": True,
                       "port": "micromint-lincoln60",
                       "build_tests": False}
    generators = "cmake_find_package"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["PORT"] = self.options.port
        cmake.definitions["BUILD_TESTS"] = self.options.build_tests
        cmake.configure()
        cmake.build()
