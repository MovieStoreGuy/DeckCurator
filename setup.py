#! /usr/bin/env python -dOt

# Example taken from: https://github.com/pybind/python_example/blob/master/setup.py

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import os , sys
import setuptools

cpp_args = ['-std=c++11',
            '-stdlib=libc++',
            '-Wall',
            '-Wextra',
            '-Werror',
            '-Wstrict-prototypes',
            '-O2',
            '-fvisibility=hidden',
            '-mmacosx-version-min=10.8']

ext_modules = [
    Extension(
        'DeckCurator',
            ['src/' + f for f in os.listdir('src/')],
            include_dirs=['pybind11/include'],
        language='c++',
        extra_compile_args = cpp_args,
    ),
]

setup(name='DeckCurator',
      version='0.2',
      description='Python bindings for DeckCurator',
      url='http://github.com/RenegadeTech/DeckCurator',
      author='Sean Marciniak',
      author_email='seanmarciniak@gmail.com',
      license='MIT',
      headers=['include/' + f for f in os.listdir('include/')],
      install_requires=['pybind11>=1.7'],
      ext_modules=ext_modules,
      test_requires=['pytest'],
      test_suite='test.my_module_suite',
      zip_safe=False)
