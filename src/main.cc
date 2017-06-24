#include <iostream>
#include <cstdint>
#include <memory>
#include <cmath>
#include "../include/Card.hpp"
#include "../include/Deck.hpp"
#include "../include/Evaluator.hpp"

int main(int argc, const char * argv[]) {
    uint8_t mana[COLOUR_COUNT] = {1};
    DeckCurator::Card * land = new DeckCurator::Card("Super Awesome Fun Land", mana);
    land->addType(DeckCurator::Card::Legendary);
    land->addType(DeckCurator::Card::Land);
    DeckCurator::Card * Creature = new DeckCurator::Card("Meerfolk holmes", mana);
    Creature->addType(DeckCurator::Card::Legendary);
    Creature->addType(DeckCurator::Card::Creature);
    DeckCurator::Deck deck;
    deck.addCard(land);
    deck.addCard(Creature);
    std::unique_ptr<DeckCurator::Evaluator> eval(new DeckCurator::Evaluator(&deck));
    eval->addEvaluationFunction([](const DeckCurator::Deck* deck)->double{
        return deck->size() / deck->size();
    });
    eval->addEvaluationFunction([](const DeckCurator::Deck* deck)->double{
        // Optimal Draw function
        // Calculate all shingles
        double result = 1.0;
        for (size_t i = 0; i < deck->size(); ++i) {
            double hand_weight = 0.0;
            for (size_t k = i; k < std::min(deck->size(), i + 7); ++k) {
                hand_weight += (3 - deck->getCardAt(k)->convertedManaCost()) / 3.0;
            }
            result *= hand_weight;
        }
        return result;
    });
    std::cout << eval->evaluate() << std::endl;
    return 0;
}
