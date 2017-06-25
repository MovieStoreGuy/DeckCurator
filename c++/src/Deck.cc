#include "../include/Deck.hpp"

DeckCurator::Deck::Deck() {
    // Kept blank until further notice
}

DeckCurator::Deck::~Deck() {
    deck.clear();
}

void DeckCurator::Deck::addCard(Card * card) {
    if (card == nullptr) {
        return;
    }
    deck.push_back(card);
}

void DeckCurator::Deck::shuffle() {
    std::random_shuffle(deck.begin(), deck.end());
}

const DeckCurator::Card * DeckCurator::Deck::getCardAt(size_t index) const {
    return (index < deck.size()) ? deck[index] : nullptr;
}

void DeckCurator::Deck::removeCardAt(size_t index) {
    if (index < deck.size()) {
        deck.erase(deck.begin() + index);
    }
}

size_t DeckCurator::Deck::size() const {
    return deck.size();
}

uint8_t DeckCurator::Deck::averageCMC() const {
    uint32_t sum = 0;
    for (size_t i = 0; i < size(); ++i) {
        sum += getCardAt(i)->convertedManaCost();
    }
    return std::ceil(sum / size());
}

std::ostream& DeckCurator::operator<<(std::ostream& os, DeckCurator::Deck& deck) {
    for (size_t i = 0; i < deck.size(); ++i) {
        os << deck.getCardAt(i) << std::endl;
    }
    return os;
}