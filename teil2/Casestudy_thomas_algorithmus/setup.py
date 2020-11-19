#!/usr/bin/env python3
from setuptools import setup, Extension 
from Cython.Build import cythonize
from numpy import get_include
import sys

if 'linux' in sys.platform or 'darwin' in sys.platform:
	# Linux / macOS
	compile_flags = ["-std=c11", "-O3", "-march=native"]
else:
	# Windows
	compile_flags = ["/std:c11", "/O2", "/arch:AVX2"]

ext = Extension(name="cytridiag",
		sources=["src/tridiag_solve.c", "src/wrapper.pyx"],
		extra_compile_args = compile_flags,
		include_dirs=[get_include()],
		define_macros=[("NPY_NO_DEPRECATED_API", "NPY_1_7_API_VERSION")]
	)

# Use cythonize on the extension object.
setup(install_requires=["cython", "numpy"], ext_modules=cythonize(ext, language_level="3"))