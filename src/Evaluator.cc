#include "../include/Evaluator.hpp"

DeckCurator::Evaluator::Evaluator(const DeckCurator::Deck* deck) {
    if (deck == nullptr) {
        abort();
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
    double metric = 1.0;
    // Will need to make this parallel for faster results
    for (auto& func : evaluators) {
        metric *= func(this->deck);
    }
    return metric;
}
