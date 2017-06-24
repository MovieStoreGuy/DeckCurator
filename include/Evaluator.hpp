#ifndef __DECK_CURATOR__EVALUATOR_H
#define __DECK_CURATOR__EVALUATOR_H

#include "Deck.hpp"
#include <cstdlib>
#include <functional>
#include <vector>

namespace DeckCurator {
    class Evaluator {
    public:
        Evaluator();
        void setDeck(DeckCurator::Deck* deck);
        void addEvaluationFunction(std::function<double(const DeckCurator::Deck*)> func);
        double evaluate();
    private:
        DeckCurator::Deck* deck;
        std::vector<std::function<double(const DeckCurator::Deck*)> > evaluators;
    };
};

#endif
