import unittest
from DeckCurator import *

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
        with self.assertRaises(Exception) as context:
            self.deck.addCard(None)
        self.assertEqual(len(self.deck), 0)

    def test_removal(self):
        self.test_SingleCard()
        self.deck.removeCardAt(1)
        self.assertEqual(len(self.deck), 1)
        self.deck.removeCardAt(0)
        self.assertEqual(len(self.deck), 0)

    def test_manaCurve(self):
        self.test_SingleCard()
        curve = self.deck.getManaCurve()
        self.assertEqual(len(curve), 9)
        self.assertEqual(curve[1], 1)

    def test_DefaultMaxMana(self):
        self.assertEqual(Deck.MAX_MANA_COST, 8)
