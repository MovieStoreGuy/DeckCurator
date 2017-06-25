#include "../include/Module.hpp"

namespace py = pybind11;

PYBIND11_PLUGIN(DeckCurator) {
    py::module m("DeckCurator", "DeckCurator plugin");

    // Card Bindings for python
    py::class_<DeckCurator::Card> Card(m, "Card");
    Card
        .def(py::init<std::string>())
        .def("getName", &DeckCurator::Card::getName)
        .def("addType", &DeckCurator::Card::addType)
        .def("isType", &DeckCurator::Card::isType)
        .def("getTypes", &DeckCurator::Card::getTypes)
        .def("convertedManaCost", &DeckCurator::Card::convertedManaCost)
        .def("setColourCost", &DeckCurator::Card::setColourCost)
        .def("getColourCost", &DeckCurator::Card::getColourCost)
        .def("__repr__",
            [](const DeckCurator::Card &c) {
                return "<DeckCurator.Card '" + c.getName() + ":" + std::to_string(c.convertedManaCost()) + "'>";
            }
        );

    py::enum_<enum DeckCurator::Card::Type> (Card, "Type")
        .value("Legendary", DeckCurator::Card::Legendary)
        .value("Creature", DeckCurator::Card::Creature)
        .value("Artifact", DeckCurator::Card::Artifact)
        .value("Land", DeckCurator::Card::Land)
        .value("Instant", DeckCurator::Card::Instant)
        .value("Sorcery", DeckCurator::Card::Sorcery)
        .export_values();

    py::enum_<enum DeckCurator::Card::Colour> (Card, "Colour")
        .value("Colourless", DeckCurator::Card::Colourless)
        .value("Colorless", DeckCurator::Card::Colorless)
        .value("Red", DeckCurator::Card::Red)
        .value("Green", DeckCurator::Card::Green)
        .value("Blue", DeckCurator::Card::Blue)
        .value("Black", DeckCurator::Card::Black)
        .value("White", DeckCurator::Card::White)
        .export_values();

    // Deck Bindings for python
    py::class_<DeckCurator::Deck> Deck(m, "Deck");
    Deck
        .def(py::init<>())
        .def("addCard", &DeckCurator::Deck::addCard)
        .def("shuffle", &DeckCurator::Deck::shuffle)
        .def("getCardAt", &DeckCurator::Deck::getCardAt)
        .def("removeCardAt", &DeckCurator::Deck::removeCardAt)
        .def("size", &DeckCurator::Deck::size)
        .def("averageCMC", &DeckCurator::Deck::averageCMC)
        .def("__repr__",
            [](const DeckCurator::Deck &d) {
                return "<DeckCurator.deck '" + std::to_string(d.size()) + "'>'";
            }
        );

    // Evaluator bindings for Python
    py::class_<DeckCurator::Evaluator> Evaluator(m, "Evaluator");
    Evaluator
        .def(py::init<>())
        .def("setDeck", &DeckCurator::Evaluator::setDeck)
        .def("addEvaluationFunction", &DeckCurator::Evaluator::addEvaluationFunction)
        .def("evaluate", &DeckCurator::Evaluator::evaluate);

    return m.ptr();
}
