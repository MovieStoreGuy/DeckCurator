#ifndef __DECK_CURATOR__DECK_H
#define __DECK_CURATOR__DECK_H

/*
 *  DeckCurator - Deck Class
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "Card.hpp"

namespace DeckCurator {
    class Deck {
        public:

            typedef std::vector<Card*>::const_iterator iterator;

            Deck();
            virtual ~Deck();

            /*
             *  Deck - add Card
             *  This will add a card to the deck's internal storage
             *
             *  @param card A pointer to a card object
             */
            void addCard(Card* card);

            /*
             *  Deck - shuffle
             *
             *  Shuffles the internal deck container
             */
            void shuffle();

            /*
             *  Deck - get card at
             *
             *  Obtains the card from the internal container and does not modify the internal
             *  container.
             *  @param index The card index in the deck you wish to obtain.
             *  @return A pointer to the card or nullptr if out of range
             */
            const Card * getCardAt(size_t index) const;

            /*
             *  Deck - remove card at
             *
             *  removes a card from the given deck.
             *  @param index removes card from deck at index
             */
            void removeCardAt(size_t index);

            /*
             *  Deck - size
             *
             *  @return the current size of the deck
             */
            size_t size() const;

            uint8_t averageCMC() const;

            iterator begin() const;

            iterator end() const;

            friend std::ostream& operator<<(std::ostream& os, DeckCurator::Deck& deck);

        protected:
            std::vector<Card* > deck;
    };
}

#endif
