#include "../include/Card.hpp"

DeckCurator::Card::Card(std::string name) {
    this->name = name;
    for (size_t i = 0; i < COLOUR_COUNT; ++i) {
        mana[i] = 0;
    }
}

void DeckCurator::Card::setColourCost(enum Colour colour, uint8_t cost) {
    if (colour < COLOUR_COUNT) {
        mana[colour] = cost;
    }
}

std::string DeckCurator::Card::getName() const {
    return this->name;
}

uint8_t DeckCurator::Card::convertedManaCost() const {
    uint8_t cost = 0;
    for (int i = 0; i < COLOUR_COUNT; ++i) {
        cost += mana[i];
    }
    return cost;
}

uint8_t DeckCurator::Card::getColourCost(enum Colour colour) const {
    return (static_cast<int>(colour) < COLOUR_COUNT) ? mana[colour] : (uint8_t) -1;
}

void DeckCurator::Card::addType(enum DeckCurator::Card::Type type) {
    types.insert(type);
}

bool DeckCurator::Card::isType(enum DeckCurator::Card::Type type) const {
    return types.find(type) != types.end();
}

std::set<int> DeckCurator::Card::getTypes() const {
    return types;
}

std::ostream& DeckCurator::operator<<(std::ostream& os, DeckCurator::Card& card) {
    os << "Name: "<< card.getName() << std::endl;
    os << "Cost:";
    for (int i = 0; i < COLOUR_COUNT; ++i) {
        if (card.getColourCost(static_cast<enum DeckCurator::Card::Colour>(i)) == 0) {
            // avoid printing the card cost if it is zero
            continue;
        }
        os << " " << (int) card.getColourCost(static_cast<enum DeckCurator::Card::Colour>(i)) << " ";
        switch (i) {
            case Card::Colourless:
                os << "Colourless";
                break;
            case Card::Red:
                os << "Red";
                break;
            case Card::Blue:
                os << "Blue";
                break;
            case Card::Green:
                os << "Green";
                break;
            case Card::Black:
                os << "Black";
                break;
        }
    }
    os << std::endl;
    os << "CMC: " << (int) card.convertedManaCost() << std::endl;
    os << "Type:";
    for (auto& type : card.getTypes()) {
        os << " ";
        switch (type) {
            case Card::Land:
                os << "land";
                break;
            case Card::Creature:
                os << "Creature";
                break;
            case Card::Sorcery:
                os << "Sorcery";
                break;
            case Card::Artifact:
                os << "Artifact";
                break;
            case Card::Instant:
                os << "Instant";
                break;
            case Card::Legendary:
                os << "Legendary";
                break;
            default:
                os << "Unknown type";
                break;
        }
    }
    return os;
}
