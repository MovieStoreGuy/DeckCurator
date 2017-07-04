import unittest
from DeckCurator import *

if __name__ == '__main__':
    loader = unittest.TestLoader()
    tests = loader.discover('.')
    testRunner = unittest.runner.TextTestRunner()
    testRunner.run(tests)
