#! /usr/bin/env python -dOt

import unittest
import pytest

from DeckCurator import *

GLOBAL_RUNTIME = 10

class TestCard(unittest.TestCase):
    def setUp(self):
        ''' Run before each test case '''
        self.card = Card("TestCard")

    def tearDown(self):
        self.card = None

    def test_name(self):
        self.assertEqual(self.card.getName(), "TestCard")

    def test_notType(self):
        self.assertFalse(self.card.isType(Card.Land))
        self.assertFalse(self.card.isType(Card.Legendary))
        self.assertFalse(self.card.isType(Card.Creature))
        self.assertFalse(self.card.isType(Card.Instant))
        self.assertFalse(self.card.isType(Card.Sorcery))

    def test_TypeAddition(self):
        self.card.addType(Card.Legendary)
        self.card.addType(Card.Land)
        self.assertTrue(self.card.isType(Card.Land))
        self.assertTrue(self.card.isType(Card.Legendary))
        self.assertFalse(self.card.isType(Card.Creature))
        self.assertFalse(self.card.isType(Card.Instant))
        self.assertFalse(self.card.isType(Card.Sorcery))

    def test_manacost(self):
        self.assertEqual(self.card.convertedManaCost(), 0)

    def test_updateManaCost(self):
        self.card.setColourCost(Card.Colourless, 3)
        self.assertEqual(self.card.convertedManaCost(), 3)
        self.assertEqual(self.card.getColourCost(Card.Colorless), 3)

class TestDeck(unittest.TestCase):

    def setUp(self):
        self.deck = Deck()

    def tearDown(self):
        self.deck = None

    def test_EmptyDeck(self):
        self.assertEqual(len(self.deck), 0)
        self.assertEqual(self.deck.size(), 0)
        self.assertEqual(self.deck.getCardAt(0), None)
        self.deck.shuffle()
        self.deck.removeCardAt(0)
        self.assertEqual(self.deck.averageCMC(), 0)

    def test_SingleCard(self):
        self.assertEqual(len(self.deck), 0)
        c = Card("TestCard")
        self.deck.addCard(c)
        self.assertEqual(len(self.deck), 1)
        self.assertEqual(self.deck.getCardAt(0), c)
        c.setColourCost(Card.Colorless, 1)
        self.assertEqual(self.deck.averageCMC(), 1)

    def test_NullCard(self):
        self.assertEqual(len(self.deck), 0)
        self.deck.addCard(None)
        self.assertEqual(len(self.deck), 0)

    def test_removal(self):
        self.test_SingleCard()
        self.deck.removeCardAt(1)
        self.assertEqual(len(self.deck), 1)
        self.deck.removeCardAt(0)
        self.assertEqual(len(self.deck), 0)

class TestEvaluator(unittest.TestCase):

    def setUp(self):
        self.eval = Evaluator()

    def tearDown(self):
        self.eval = None

    @pytest.mark.timeout(2, method='thread')
    def test_addFunc(self):
        self.eval.addEvaluationFunction(lambda x : x.size() * 1.0)
        self.assertEqual(self.eval.evaluate(), 0.0)

    @pytest.mark.timeout(2, method='thread')
    def test_blankevalation(self):
        self.assertEqual(self.eval.evaluate(), 0.0)

    @pytest.mark.timeout(2, method='thread')
    def test_NoEvalFunc(self):
        d = Deck()
        self.eval.setDeck(d)
        self.assertEqual(self.eval.evaluate(), 1.0)

if __name__ == '__main__':
    unittest.main()
