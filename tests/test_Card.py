import unittest
from DeckCurator import *

class TestCard(unittest.TestCase):
    def setUp(self):
        ''' Run before each test case '''
        self.card = Card("TestCard")

    def tearDown(self):
        self.card = None

    def test_Name(self):
        '''
            Ensuring we can actually set the name of the card
        '''
        self.assertEqual(self.card.getName(), "TestCard")

    def test_NamedInstanceArguments(self):
        '''
            Testing to see if named arguments work
        '''
        c = Card(Name="TestCard")

    def test_NamedParams(self):
        # Ignoring the Colour parameter as that should be set to Colourless by default
        self.card.setColourCost(Cost = 1)
        self.assertEqual(self.card.getColourCost(), 1)

    def test_DefaultName(self):
        '''
            Ensuring the default name is always an empty string,
            never null
        '''
        c = Card()
        self.assertEqual(c.getName(),'')

    def test_NotType(self):
        '''
            Ensuring a card has no type when first created
        '''
        self.assertFalse(self.card.isType(Card.Land))
        self.assertFalse(self.card.isType(Card.Legendary))
        self.assertFalse(self.card.isType(Card.Creature))
        self.assertFalse(self.card.isType(Card.Instant))
        self.assertFalse(self.card.isType(Card.Sorcery))

    def test_TypeAddition(self):
        '''
            Can add new types so an instance of a card
        '''
        self.card.addType(Card.Legendary)
        self.card.addType(Card.Land)
        self.assertTrue(self.card.isType(Card.Land))
        self.assertTrue(self.card.isType(Card.Legendary))
        self.assertFalse(self.card.isType(Card.Creature))
        self.assertFalse(self.card.isType(Card.Instant))
        self.assertFalse(self.card.isType(Card.Sorcery))

    def test_ManaCost(self):
        '''
            Ensuring the CMC of a card is 0 by default
        '''
        self.assertEqual(self.card.convertedManaCost(), 0)

    def test_UpdateManaCost(self):
        '''
            Can correctly update the Mana cost of a card
        '''
        self.card.setColourCost(Card.Colourless, 3)
        self.assertEqual(self.card.convertedManaCost(), 3)
        self.assertEqual(self.card.getColourCost(Card.Colorless), 3)

    def test_CompareEqual(self):
        '''
            Testing that equality operator holds true for like cards
        '''
        c = Card("TestCard")
        self.assertEqual(self.card, c)
        self.assertEqual(c, self.card)

    def test_CompareSelf(self):
        '''
            Ensuring an object is equal to itself
        '''
        self.assertEqual(self.card, self.card)

    def test_CompareNone(self):
        '''
            Ensuring that instance of an Card does not equal null
        '''
        self.assertFalse(self.card == None)
        self.assertFalse(None == self.card)
