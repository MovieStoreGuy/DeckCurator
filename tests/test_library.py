import unittest
import pytest

from DeckCurator import *

GLOBAL_RUNTIME = 10

class TestImport(unittest.TestCase):

    def test_libraries(self):
        import DeckCurator
        self.assertTrue('Card' in dir(DeckCurator))
        self.assertTrue('Deck' in dir(DeckCurator))
        self.assertTrue('Evaluator' in dir(DeckCurator))
        self.assertTrue('CommanderEvaluator' in dir(DeckCurator))

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

class TestEvaluator(unittest.TestCase):
    def setUp(self):
        self.eval = Evaluator()

    def tearDown(self):
        self.eval = None

    @pytest.mark.timeout(2, method='thread')
    def test_NoneFunction(self):
        with self.assertRaises(Exception) as e:
            self.eval(None)

    @pytest.mark.timeout(2, method='thread')
    def test_AddFunc(self):
        ''' Function should return 0 since no deck added '''
        self.eval.addEvaluationFunction(lambda x : x.size() * 1.0)
        self.assertEqual(self.eval.evaluate(), 0.0)

    @pytest.mark.timeout(2, method='thread')
    def test_Blankevalation(self):
        self.assertEqual(self.eval.evaluate(), 0.0)

    @pytest.mark.timeout(2, method='thread')
    def test_NoEvalFunc(self):
        d = Deck()
        self.eval.setDeck(d)
        self.assertEqual(self.eval.evaluate(), 1.0)

    @pytest.mark.timeout(2, method='thread')
    def test_EvalTest(self):
        d = Deck()
        self.eval.setDeck(d)
        self.eval.addEvaluationFunction(lambda x: 0.5)
        self.assertEqual(self.eval.evaluate(), 0.5)

    @pytest.mark.timeout(2, method='thread')
    def test_MetricValue(self):
        d = Deck()
        d.addCard(Card("TestCard"))
        self.eval.addEvaluationFunction(lambda x: x * -1.0)
        self.eval.setDeck(d)
        self.assertEqual(self.eval.evaluate(), 0.0)

class TestCommander(unittest.TestCase):

    def test_NullDeck(self):
        with self.assertRaises(Exception) as e:
            CommanderEvaluator(None)

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

if __name__ == '__main__':
    unittest.main()
