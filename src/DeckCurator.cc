#include "../include/DeckCurator.hpp"

namespace py = pybind11;
namespace dc = DeckCurator;

PYBIND11_PLUGIN(DeckCurator) {
    py::module m("DeckCurator", "DeckCurator plugin");
    // Card Class
    py::class_<dc::Card, std::shared_ptr<dc::Card>> Card(m, "Card");
    Card
        .def(py::init<std::string>(),
            py::arg("Name") = "")
        .def("getName", &dc::Card::getName)
        .def("addType", &dc::Card::addType, py::arg("Type"))
        .def("isType", &dc::Card::isType, py::arg("Type"))
        .def("getTypes", &dc::Card::getTypes)
        .def("convertedManaCost", &dc::Card::convertedManaCost)
        .def("setColourCost", &dc::Card::setColourCost,
            py::arg("Colour"),
            py::arg("Cost") = 0)
        .def("getColourCost", &dc::Card::getColourCost,
            py::arg("Colour"))
        .def("__eq__", [](const py::object lhs, const py::object rhs)->bool{
            try {
                dc::Card* clhs = lhs.cast<dc::Card*>();
                dc::Card* crhs = lhs.cast<dc::Card*>();
                // this will call the '==' defined in the DeckCurator namespace
                return *clhs == *crhs;
            } catch (py::cast_error ) {
                return false;
            }
            return false;
        })
        .def("__repr__",
            [](const dc::Card &c) {
                return "<DeckCurator.Card '" + c.getName() + ":" + std::to_string(c.convertedManaCost()) + "'>";
            }
        );

    py::enum_<enum dc::Card::Type> (Card, "Type")
        .value("Legendary",  dc::Card::Legendary)
        .value("Creature",   dc::Card::Creature)
        .value("Artifact",   dc::Card::Artifact)
        .value("Basic_Land", dc::Card::Basic_Land)
        .value("Land",       dc::Card::Land)
        .value("Instant",    dc::Card::Instant)
        .value("Sorcery",    dc::Card::Sorcery)
        .export_values();

    py::enum_<enum DeckCurator::Card::Colour> (Card, "Colour")
        .value("Colourless", dc::Card::Colourless)
        .value("Colorless",  dc::Card::Colorless)
        .value("Red",        dc::Card::Red)
        .value("Green",      dc::Card::Green)
        .value("Blue",       dc::Card::Blue)
        .value("Black",      dc::Card::Black)
        .value("White",      dc::Card::White)
        .export_values();

    // Deck Bindings for python
    py::class_<dc::Deck, std::shared_ptr<dc::Deck>> Deck(m, "Deck");
    Deck
        .def(py::init<>())
        .def("addCard", &DeckCurator::Deck::addCard,
            py::arg("Card") = nullptr)
        .def("shuffle", &DeckCurator::Deck::shuffle)
        .def("getCardAt", &DeckCurator::Deck::getCardAt)
        .def("removeCardAt", &DeckCurator::Deck::removeCardAt)
        .def("size", &DeckCurator::Deck::size)
        .def("averageCMC", &DeckCurator::Deck::averageCMC)
        .def("getManaCurve", &DeckCurator::Deck::getManaCurve)
        .def_property_static("MAX_MANA_COST", [](py::object ){
            return DeckCurator::Deck::MAX_MANA_COST;
        }, [](py::object o) {
            DeckCurator::Deck::MAX_MANA_COST = py::cast<uint8_t>(o);
        })
        .def("__repr__",
            [](const DeckCurator::Deck &d) {
                return "<DeckCurator.deck '" + std::to_string(d.size()) + "'>'";
            }
        )
        .def("__len__", &DeckCurator::Deck::size)
        .def("__iter__",
            [](DeckCurator::Deck& deck) {
                return py::make_iterator(deck.begin(), deck.end());
            }, py::keep_alive<0, 1>()
        );

    // Evaluator bindings for Python
    py::class_<DeckCurator::Evaluator> Evaluator(m, "Evaluator");
    Evaluator
        .def(py::init<>())
        .def("setDeck", &DeckCurator::Evaluator::setDeck)
        .def("addEvaluationFunction", &DeckCurator::Evaluator::addEvaluationFunction)
        .def("evaluate", &DeckCurator::Evaluator::evaluate);

    py::class_<DeckCurator::CommanderEvaluator> CommanderEval(m, "CommanderEvaluator", Evaluator);
    CommanderEval.def(py::init<std::shared_ptr<DeckCurator::Deck>>(),
        py::arg("Deck") = nullptr);

    m.attr("__version__") = py::str("dev");

    return m.ptr();
}
