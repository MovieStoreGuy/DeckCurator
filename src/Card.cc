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

namespace py = pybind11;

PYBIND11_PLUGIN(DeckCurator) {
    py::module m("DeckCurator", "DeckCurator plugin");
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

    return m.ptr();
}
