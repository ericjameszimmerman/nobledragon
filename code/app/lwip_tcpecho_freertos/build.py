#!/usr/bin/env python3

import os
import sys
import subprocess
import time
import pathlib


def _execute_command(cmd, cwd):
    p = subprocess.Popen(cmd, cwd=str(cwd), shell=True)

    while p.poll() is None:
        time.sleep(0.25)

    return p.returncode


class Cli:
    def __init__(self) -> None:
        self.script_path = pathlib.Path(os.path.realpath(os.path.dirname(__file__)))

    def execute(self):
        self.build()

    def build(self):
        _execute_command('conan install . --install-folder build-debug4 -pr=armcortexm3', self.script_path)
        _execute_command('conan build . --build-folder build-debug4', self.script_path)


def cli_main():
    cli = Cli()
    cli.execute()


if __name__ == '__main__':
    cli_main()
