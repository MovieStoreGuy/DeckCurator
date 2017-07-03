import unittest
import pytest
from DeckCurator import *

TIMEOUT = 2

class TestEvaluator(unittest.TestCase):
    def setUp(self):
        self.eval = Evaluator()

    def tearDown(self):
        self.eval = None

    @pytest.mark.timeout(TIMEOUT, method='thread')
    def test_NoneFunction(self):
        with self.assertRaises(Exception) as e:
            self.eval(None)

    @pytest.mark.timeout(TIMEOUT, method='thread')
    def test_AddFunc(self):
        ''' Function should return 0 since no deck added '''
        self.eval.addEvaluationFunction(lambda x : x.size() * 1.0)
        self.assertEqual(self.eval.evaluate(), 0.0)

    @pytest.mark.timeout(TIMEOUT, method='thread')
    def test_Blankevalation(self):
        self.assertEqual(self.eval.evaluate(), 0.0)

    @pytest.mark.timeout(TIMEOUT, method='thread')
    def test_NoEvalFunc(self):
        d = Deck()
        self.eval.setDeck(d)
        self.assertEqual(self.eval.evaluate(), 1.0)

    @pytest.mark.timeout(TIMEOUT, method='thread')
    def test_EvalTest(self):
        d = Deck()
        self.eval.setDeck(d)
        self.eval.addEvaluationFunction(lambda x: 0.5)
        self.assertEqual(self.eval.evaluate(), 0.5)

    @pytest.mark.timeout(TIMEOUT, method='thread')
    def test_MetricValue(self):
        d = Deck()
        d.addCard(Card("TestCard"))
        self.eval.addEvaluationFunction(lambda x: x * -1.0)
        self.eval.setDeck(d)
        self.assertEqual(self.eval.evaluate(), 0.0)
