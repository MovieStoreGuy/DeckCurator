import unittest
import pytest

from DeckCurator import *

class TestImport(unittest.TestCase):

    def test_libraries(self):
        import DeckCurator
        self.assertTrue('Card' in dir(DeckCurator))
        self.assertTrue('Deck' in dir(DeckCurator))
        self.assertTrue('Evaluator' in dir(DeckCurator))
        self.assertTrue('CommanderEvaluator' in dir(DeckCurator))
