#ifndef __DECK_CURATOR__COMMANDER_EVALUATOR_H
#define __DECK_CURATOR__COMMANDER_EVALUATOR_H
#include "Evaluator.hpp"
#include "Deck.hpp"

namespace DeckCurator {
    class CommanderEvaluator : public Evaluator {
        public:
            CommanderEvaluator(Deck * deck);
    };
};

#endif
