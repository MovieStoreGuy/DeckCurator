import unittest
from DeckCurator import *

class TestCard(unittest.TestCase):
    def setUp(self):
        ''' Run before each test case '''
        self.card = Card("TestCard")

    def tearDown(self):
        self.card = None

    def test_Name(self):
        self.assertEqual(self.card.getName(), "TestCard")

    def test_NotType(self):
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

    def test_ManaCost(self):
        self.assertEqual(self.card.convertedManaCost(), 0)

    def test_UpdateManaCost(self):
        self.card.setColourCost(Card.Colourless, 3)
        self.assertEqual(self.card.convertedManaCost(), 3)
        self.assertEqual(self.card.getColourCost(Card.Colorless), 3)

    def test_CompareEqual(self):
        c = Card("TestCard")
        self.assertEqual(self.card, c)
