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
        return;
    }
    // Forces the all functions to be run asynchronously
    evaluators.push_back(std::async(func,deck));
}

double DeckCurator::Evaluator::evaluate() {
    if (deck == nullptr) {
        std::cerr << "Deck is not set" << std::endl;
        return 0.0;
    }
    double metric = 1.0;
    for (auto& func : evaluators) {
        // halts progress untill function returns
        metric *= func.get();
    }
    return std::abs(std::min(std::max(metric, 0.0), 1.0));
}
