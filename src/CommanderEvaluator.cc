#include "../include/CommanderEvaluator.hpp"

namespace dc = DeckCurator;

dc::CommanderEvaluator::CommanderEvaluator(std::shared_ptr<Deck> deck) : dc::Evaluator() {
    this->setDeck(deck);
    // Commander Deck must have 100 cards
    addEvaluationFunction([](const auto deck)->double {
        return (deck->size() == 100) ? 1.0 : 0.0;
    });

    // All cards must be a colour of the commander
    addEvaluationFunction([](const auto deck)->double {
        // Assume the Comander is card 0 in the deck to begin with
        const auto& commander = deck->getCardAt(0);
        double result = 1.0;
        for (size_t i = 1; i < deck->size(); ++i) {
            // Need to check the colour of each card
            const auto& card = deck->getCardAt(i);
            for (auto colour : card->getColours()) {
                // Ignore colourless
                if (colour == dc::Card::Colourless) {
                    continue;
                }
                // if the colour cost is zero,
                // then we know we have a card we shouldn't have
                result *= static_cast<double>(commander->getColourCost(
                    (enum DeckCurator::Card::Colour)colour));
            }
        }
        return result;
    });

    // Must only have one copy of each non basic land
    addEvaluationFunction([](const auto deck)->double {
        double result = 1.0;
        for (size_t i = 0; i < deck->size(); ++i) {
            if (deck->getCardAt(i)->isType(dc::Card::Basic_Land)) {
                continue;
            }
            double count = 0.0;
            for (size_t j = 0; j < deck->size(); ++j) {
                count += static_cast<double>(*(deck->getCardAt(i)) == *(deck->getCardAt(j)));
            }
            result *= (count == 1.0) ? 1.0 : 0.0;
        }
        return result;
    });

    // Commander must be a Legendary creature
    addEvaluationFunction([](const auto deck)->double{
        return (deck->getCardAt(0)->isType(dc::Card::Legendary)
            && deck->getCardAt(0)->isType(dc::Card::Creature)) ? 1.0 : 0.0;
    });
}
