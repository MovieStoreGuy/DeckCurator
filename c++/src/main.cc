#include <iostream>
#include <cstdint>
#include <memory>
#include <cmath>
#include "../include/Card.hpp"
#include "../include/Deck.hpp"
#include "../include/Evaluator.hpp"

int main(int argc, const char * argv[]) {
    DeckCurator::Card * land = new DeckCurator::Card("Super Awesome Fun Land");
    land->setColourCost(DeckCurator::Card::Colourless, 1);
    land->addType(DeckCurator::Card::Legendary);
    land->addType(DeckCurator::Card::Land);
    DeckCurator::Card * Creature = new DeckCurator::Card("Meerfolk holmes");
    Creature->addType(DeckCurator::Card::Legendary);
    Creature->addType(DeckCurator::Card::Creature);
    Creature->setColourCost(DeckCurator::Card::Colourless, 4);
    Creature->setColourCost(DeckCurator::Card::Red, 1);
    DeckCurator::Deck deck;
    deck.addCard(land);
    deck.addCard(Creature);
    std::unique_ptr<DeckCurator::Evaluator> eval(new DeckCurator::Evaluator());
    eval->setDeck(&deck);
    eval->addEvaluationFunction([](const DeckCurator::Deck* deck)->double{
        // Optimal Draw function
        // Calculate all shingles
        const size_t hand_size = 7;
        double result = 1.0;
        for (size_t i = 0; i < deck->size(); ++i) {
            double hand_weight = 0.0;
            for (size_t k = i; k < std::min(deck->size(), i + hand_size); ++k) {
                hand_weight += (3 - deck->getCardAt(k)->convertedManaCost()) / 3.0;
            }
            result *= hand_weight;
        }
        // Keeping the result within [0,1]
        return std::min(std::max(result, 0.0), 1.0);
    });
    std::cout << eval->evaluate() << std::endl;
    return 0;
}
