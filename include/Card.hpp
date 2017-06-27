#ifndef __DECK_CURATOR__CARD_H
#define __DECK_CURATOR__CARD_H

#include <cstdint>
#include <string>
#include <set>
#include <iostream>
#include <pybind11/pybind11.h>

#define COLOUR_COUNT 6

namespace DeckCurator {
    class Card {
    public:
        // Static definition of card types
        // Note: The order defined is the order printed
        static enum Type {
            Legendary,
            Creature,
            Artifact,
            Land,
            Instant,
            Sorcery,
        } Type;

        static enum Colour {
            Colourless = 0,
            Colorless  = 0,
            Red        = 1,
            Green      = 2,
            Blue       = 3,
            White      = 4,
            Black      = 5
        } Colour;

        static enum Abilities {
            Cyclying,
            Flying,
            Flash,
            Hexproof,
            Indestructable,
            Shroud,
            Tap_Target,
            Tap_Creature,
        } Abilities;

        Card(std::string name);
        /*
         *  Card - getname
         *
         *  @returns the name of the card
         */
        std::string getName() const;
        /*
         *  Card - addType
         *
         *  Each card is of a spefic(?) type(s) which can be added to the card
         *  @param type Card type to be added to the card.
         */
        void addType(enum Type);
        /*
         *  Card - isType
         *
         *  @param type the type in question
         *  @return true if it is that type, otherwise false
         */
        bool isType(enum Type) const;
        /*
         *  Card - getType
         *
         *  @return the types of the card
         */
        std::set<int> getTypes() const;
        /*
         *  Card - ConvertedManaCost
         *
         *  @return the converted mana cost of the card
         */
        uint8_t convertedManaCost() const;
        /*
         *  Card - setColourCost
         *
         *  @param colour The colour to set (use card::Colour)
         *  @param cost   The cost to be set to the colour
         */
        void setColourCost(enum Colour, uint8_t cost);
        /*
         *  Card - getColourCost
         *
         *  @param colour the colour in question
         *  @return the cost for the colour given, (uint8_t)-1 if out of range
         */
        uint8_t getColourCost(enum Colour) const;

        friend std::ostream& operator<<(std::ostream& os, DeckCurator::Card& card);
    private:
        std::string name;
        uint8_t mana[COLOUR_COUNT];
        std::set<int> types;
    };
}

#endif
