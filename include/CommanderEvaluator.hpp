#ifndef __DECK_CURATOR__COMMANDER_EVALUATOR_H
#define __DECK_CURATOR__COMMANDER_EVALUATOR_H
#include "Evaluator.hpp"
#include "Deck.hpp"

#include <memory>

namespace DeckCurator {
    class CommanderEvaluator : public Evaluator {
        public:
            CommanderEvaluator(std::shared_ptr<Deck> deck);
    };
};

#endif
