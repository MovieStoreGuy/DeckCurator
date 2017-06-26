#! /usr/bin/env python -dOt
import os
from setuptools import setup
from setuptools.dist import Distribution

class BinaryDistribution(Distribution):
    def is_pure(self):
        return False

setup(name='DeckCurator',
      version='0.2',
      description='Python bindings for DeckCurator',
      url='http://github.com/RenegadeTech/DeckCurator',
      author='Sean Marciniak',
      author_email='seanmarciniak@gmail.com',
      license='MIT',
      include_package_data=True,
      distclass=BinaryDistribution,
      zip_safe=False)
