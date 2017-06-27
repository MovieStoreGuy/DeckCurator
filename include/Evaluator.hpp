#ifndef __DECK_CURATOR__EVALUATOR_H
#define __DECK_CURATOR__EVALUATOR_H

#include "Deck.hpp"
#include <cstdlib>
#include <future>
#include <functional>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

namespace DeckCurator {
    class Evaluator {
    public:
        Evaluator();
        /*
         *  Evaluator - setDeck
         *
         *  @param deck The deck to evaluate
         */
        void setDeck(DeckCurator::Deck* deck);
        /*
         *  Evaluator - addEvaluationFunction
         *
         *  @param func The function to add to the evaluation step
         */
        void addEvaluationFunction(std::function<double(const DeckCurator::Deck*)> func);
        /*
         *  Evaluator - evaluate
         *
         *  @return the metric of how well the deck did,
         *              value should be in the range [0,1]
         */
        double evaluate();
    private:
        DeckCurator::Deck* deck;
        std::vector<std::future<double> > evaluators;
    };
};

#endif
