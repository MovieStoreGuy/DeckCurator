import unittest

from DeckCurator import *

class TestCommander(unittest.TestCase):

    def test_NullDeck(self):
        with self.assertRaises(Exception) as e:
            CommanderEvaluator(None)

    def test_CommanderIsEvaluator(self):
        d = Deck()
        commEval = CommanderEvaluator(d)
        self.assertTrue(isinstance(commEval, Evaluator))

    def test_BasicTest(self):
        d = Deck()
        c = Card("TestCommander")
        c.setColourCost(Card.Colorless, 1)
        c.setColourCost(Card.Red, 1)
        c.addType(Card.Legendary)
        c.addType(Card.Creature)
        d.addCard(c)
        for i in range(99):
            l = Card("TestLand")
            l.setColourCost(Card.Colorless, 1)
            l.setColourCost(Card.Red, 1)
            l.addType(Card.Basic_Land)
            d.addCard(l)
        self.assertEqual(d.size(), 100)
        self.assertEqual(len(d), 100)
        self.assertEqual(CommanderEvaluator(d).evaluate(), 1.0)

    def test_NonLegendaryComamander(self):
        c = Card("TestCommander")
        # Missing Legendary
        c.addType(Card.Creature)
        c.setColourCost(Card.Black, 1)
        d = Deck()
        d.addCard(c)
        for land in range(99):
            l = Card("TestLand")
            l.setColourCost(Card.Black, 0)
            l.addType(Card.Basic_Land)
            d.addCard(l)
        self.assertEqual(d.size(), 100)
        self.assertEqual(len(d), 100)
        self.assertEqual(CommanderEvaluator(d).evaluate(), 0.0)

    def test_IncorrectSize(self):
        d = Deck()
        # Incorrect Deck Size
        for _ in range(101):
            d.addCard(Card("TestCard"))
        self.assertFalse(len(d) == 100)
        self.assertEqual(CommanderEvaluator(d).evaluate(), 0.0)

    def test_NonMultiples(self):
        d = Deck()
        for _ in range(100):
            c = Card("TestCard")
            c.setColourCost(Card.Red, 10)
            c.addType(Card.Legendary)
            c.addType(Card.Creature)
            d.addCard(c)
        self.assertEqual(CommanderEvaluator(d).evaluate(), 0.0)
