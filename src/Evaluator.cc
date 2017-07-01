#include "../include/Evaluator.hpp"

namespace dc = DeckCurator;

dc::Evaluator::Evaluator() {
    this->deck = nullptr;
}

void dc::Evaluator::setDeck(std::shared_ptr<DeckCurator::Deck> deck) {
    if (deck == nullptr) {
        throw std::invalid_argument("Can not have null deck");
    }
    this->deck = deck;
}

void dc::Evaluator::addEvaluationFunction(std::function<double(const std::shared_ptr<dc::Deck>)> func) {
    if (func == nullptr) {
        return;
    }
    // Forces the all functions to be run asynchronously
    evaluators.push_back(std::async(std::launch::deferred,func,deck));
}

double dc::Evaluator::evaluate() {
    if (deck == nullptr) {
        return 0.0;
    }
    double metric = 1.0;
    for (auto& func : evaluators) {
        // halts progress untill function returns
        metric *= func.get();
    }
    return std::abs(std::min(std::max(metric, 0.0), 1.0));
}
