#include "../include/Evaluator.hpp"

DeckCurator::Evaluator::Evaluator() {
    this->deck = nullptr;
}

void DeckCurator::Evaluator::setDeck(DeckCurator::Deck* deck) {
    if (deck == nullptr) {
        return;
    }
    this->deck = deck;
}

void DeckCurator::Evaluator::addEvaluationFunction(std::function<double(const DeckCurator::Deck*)> func) {
    if (func == nullptr) {
        abort();
    }
    evaluators.push_back(func);
}

double DeckCurator::Evaluator::evaluate() {
    if (deck == nullptr) {
        std::cerr << "Deck is not set" << std::endl;
        return 0.0;
    }
    double metric = 1.0;
    // Will need to make this parallel for faster results
    for (auto& func : evaluators) {
        metric *= func(this->deck);
    }
    return metric;
}
