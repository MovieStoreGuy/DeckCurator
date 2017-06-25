#include "../include/Card.hpp"
#include <string>
#include <iostream>

#define TESTFRAME
inline void assert(bool result, std::string msg) {
    if (!result) {
        std::cerr << "Error: " << msg << std::endl;
    }
}

int main() {
    std::cerr << "Starting Card Test Framework" << std::endl;
    TESTFRAME{
        uint8_t mana[COLOUR_COUNT] = {};
        std::string name = "";
        DeckCurator::Card * card = new DeckCurator::Card(name, mana);
        assert(card != nullptr, "created card");
        assert(card->getName() == name, "name set");
        name = "newname";
        assert(card->getName() != name, "new name");
        for (int i = 0; i < COLOUR_COUNT; ++i) {
            assert(card->getColourCost(i) == 0, "Wrong colour cost");
        }
        assert(card->convertedManaCost() == 0, "Mana count");
        assert(card->getColourCost(COLOUR_COUNT + 1) == (uint8_t)-1, "Wrong count");
        assert(card->getTypes().size() == 0, "types");
        assert(!card->isType(DeckCurator::Card::Legendary), "No type set");
        assert(!card->isType(DeckCurator::Card::Creature), "No type set");
        assert(!card->isType(DeckCurator::Card::Artifact), "No type set");
        assert(!card->isType(DeckCurator::Card::Land), "No type set");
        assert(!card->isType(DeckCurator::Card::Instant), "No type set");
        assert(!card->isType(DeckCurator::Card::Sorcery), "No type set");
        card->addType(DeckCurator::Card::Legendary);
        assert(card->isType(DeckCurator::Card::Legendary), "No type set");
    }
    std::cerr << "DIE" << std::endl;
    return 0;
}
