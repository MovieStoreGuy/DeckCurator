#include "../include/Module.hpp"

namespace py = pybind11;

PYBIND11_PLUGIN(DeckCurator) {
    py::module m("DeckCurator", "DeckCurator plugin");
    // Evaluator bindings for Python
    py::class_<DeckCurator::Evaluator> Evaluator(m, "Evaluator");
    Evaluator
        .def(py::init<>())
        .def("setDeck", &DeckCurator::Evaluator::setDeck)
        .def("addEvaluationFunction", &DeckCurator::Evaluator::addEvaluationFunction)
        .def("evaluate", &DeckCurator::Evaluator::evaluate);

    return m.ptr();
}
