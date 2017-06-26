import unittest
import test_library

def my_module_suite():
    loader = unittest.TestLoader()
    suite = loader.loadTestsFromModule(test_library)
    return suite
