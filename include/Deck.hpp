#ifndef __DECK_CURATOR__DECK_H
#define __DECK_CURATOR__DECK_H

/*
 *  DeckCurator - Deck Class
 */

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>


#include "Card.hpp"

namespace DeckCurator {
    class Deck : public std::enable_shared_from_this<Deck> {
        public:

            typedef std::vector<std::shared_ptr<Card>>::const_iterator iterator;

            static uint8_t MAX_MANA_COST;

            Deck();
            virtual ~Deck();

            /*
             *  Deck - add Card
             *  This will add a card to the deck's internal storage
             *
             *  @param card A pointer to a card object
             */
            void addCard(std::shared_ptr<Card> card);

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
            const std::shared_ptr<Card> getCardAt(size_t index) const;

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

            std::shared_ptr<Deck> filterByType(enum Card::Type);

            std::shared_ptr<Deck> filterByColour(enum Card::Colour);

            std::vector<uint32_t> getManaCurve();

            friend std::ostream& operator<<(std::ostream& os, DeckCurator::Deck& deck);

        protected:
            std::vector<std::shared_ptr<Card>> deck;
    };
}

#endif
