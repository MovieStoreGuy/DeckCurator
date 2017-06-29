#include "../include/Deck.hpp"

DeckCurator::Deck::Deck() {
    // Kept blank until further notice
}

DeckCurator::Deck::~Deck() {
    deck.clear();
}

void DeckCurator::Deck::addCard(Card * card) {
    if (card == nullptr) {
        // I should raise an exception here
        throw std::invalid_argument("");
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
        deck.erase(std::remove(deck.begin(), deck.end(), getCardAt(index)), deck.end());
    }
}

size_t DeckCurator::Deck::size() const {
    return deck.size();
}

uint8_t DeckCurator::Deck::averageCMC() const {
    if (size() == 0) {
        return 0;
    }
    uint32_t sum = 0;
    for (size_t i = 0; i < size(); ++i) {
        sum += getCardAt(i)->convertedManaCost();
    }
    return std::ceil(sum / size());
}

DeckCurator::Deck::iterator DeckCurator::Deck::begin() const{
    return deck.begin();
}

DeckCurator::Deck::iterator DeckCurator::Deck::end() const {
    return deck.end();
}

std::ostream& DeckCurator::operator<<(std::ostream& os, DeckCurator::Deck& deck) {
    for (size_t i = 0; i < deck.size(); ++i) {
        os << deck.getCardAt(i) << std::endl;
    }
    return os;
}
