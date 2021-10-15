#!/usr/bin/env python3

from setuptools import setup, Extension 
from Cython.Build import cythonize
import sys

ext = Extension(
		name = "Foo",
		sources = ["src/foo.pyx",],
	)

# Use cythonize on the extension object.
setup(ext_modules=cythonize(ext, language_level="3"),
	name="RAII_EXAMPLE",
	version='0.0.1',
	author='Max Mustermann',
	author_email='max@mustermail.de',
	description='Eine kurze Beschreibung, bla bla.')
