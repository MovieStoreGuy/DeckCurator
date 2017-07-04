#include "../include/Deck.hpp"

namespace dc = DeckCurator;
// Setting 8 as the max mana cost be default
uint8_t dc::Deck::MAX_MANA_COST = 8;

dc::Deck::Deck() {
    // Kept blank until further notice
}

dc::Deck::~Deck() {
    deck.clear();
}

void dc::Deck::addCard(std::shared_ptr<dc::Card> card) {
    if (card == nullptr) {
        throw std::invalid_argument("Card can not be null");
    }
    deck.push_back(card);
}

void dc::Deck::shuffle() {
    std::random_shuffle(deck.begin(), deck.end());
}

const std::shared_ptr<dc::Card> dc::Deck::getCardAt(size_t index) const {
    return (index < deck.size()) ? deck[index] : nullptr;
}

void dc::Deck::removeCardAt(size_t index) {
    if (index < deck.size()) {
        deck.erase(std::remove(deck.begin(), deck.end(), getCardAt(index)), deck.end());
    }
}

size_t dc::Deck::size() const {
    return deck.size();
}

uint8_t dc::Deck::averageCMC() const {
    if (size() == 0) {
        return 0;
    }
    uint32_t sum = 0;
    for (size_t i = 0; i < size(); ++i) {
        sum += getCardAt(i)->convertedManaCost();
    }
    return std::ceil(sum / size());
}

dc::Deck::iterator dc::Deck::begin() const{
    return deck.begin();
}

dc::Deck::iterator dc::Deck::end() const {
    return deck.end();
}

std::shared_ptr<dc::Deck> dc::Deck::filterByType(enum dc::Card::Type type) {
    std::shared_ptr<dc::Deck> deck(new dc::Deck());
    for (const auto& card : *this) {
        if (card->isType(type)) {
            deck->addCard(card);
        }
    }
    return deck;
}

std::shared_ptr<dc::Deck> dc::Deck::filterByColour(enum dc::Card::Colour colour) {
    std::shared_ptr<dc::Deck> deck(new dc::Deck());
    for (const auto& card : *this) {
        if (card->isColour(colour)) {
            deck->addCard(card);
        }
    }
    return deck;
}

std::vector<uint32_t> dc::Deck::getManaCurve() {
    // The additional one is required as we need [0, max_mana] space
    // This assignment means other instance can modify MAX_MANA_COST without
    // affecting other running computation.
    const uint8_t max_mana = MAX_MANA_COST + 1;
    std::vector<uint32_t> cost(max_mana, 0);
    for (const auto& card : *this) {
        // Any CMC that is greater than the max mana cost will
        // be added to the last element in the array
        cost.at(std::min(card->convertedManaCost(), max_mana))++;
    }
    return cost;
}

std::ostream& DeckCurator::operator<<(std::ostream& os, DeckCurator::Deck& deck) {
    for (size_t i = 0; i < deck.size(); ++i) {
        os << deck.getCardAt(i) << std::endl;
    }
    return os;
}
