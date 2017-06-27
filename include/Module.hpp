#ifndef __DECK_CURATOR__MODULE_H
#define __DECK_CURATOR__MODULE_H

#ifdef __APPLE__
    #include <Python/Python.h>
#endif
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "Card.hpp"
#include "Deck.hpp"
#include "Evaluator.hpp"

#endif
