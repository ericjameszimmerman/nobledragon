#!/usr/bin/env python3

import os
import sys
import subprocess
import time
import pathlib


def _execute_command(cmd, cwd):
    p = subprocess.Popen(cmd, cwd=str(cwd), shell=True)
    exit_code = p.wait()
    return exit_code


class Cli:
    def __init__(self) -> None:
        self.script_path = pathlib.Path(os.path.realpath(os.path.dirname(__file__)))

    def execute(self):
        self.build()

    def build(self):
        _execute_command('conan install . --install-folder build-debug8 -pr=armcortexm3', self.script_path)
        _execute_command('conan build . --build-folder build-debug8', self.script_path)


def cli_main():
    cli = Cli()
    cli.execute()


if __name__ == '__main__':
    cli_main()
