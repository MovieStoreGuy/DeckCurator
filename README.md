# Deck Curator
This project looks at evaluating Magic The Gathering (TM) decks to see how well
they preform against different metric functions.


## How it works
Once you have constructed a deck, you can specify what metrics to perform against your deck. The library keeps object as constant when it is being evaluated so that operations can happen in parallel without side affects.


### Example

*Adding functions to the Evaluator using c++ 11 lambda*
```c++
// ...
std::unique_ptr<DeckCurator::Evaluator> eval(new DeckCurator::Evaluator());
eval->setDeck(&deck);
eval->addEvaluationFunction([](const DeckCurator::Deck * deck)->double{
    // Custom Deck Evaluator function
});
std::cout << "The Deck Metric is: " << eval->evaluate() << std::endl;
```
Once the function has been added to the evaluator object, it is then in its own async block so that the process of one function does not block another.

## Project Goals
- [ ] Be able to work as microservice
    - [ ] Have a accessible docker container
- [ ] Templated using Jinja
- [ ] Python binding support
- [ ] Support multiple file types for reading / writing
    - [ ] JSON
    - [ ] Plain text
    - [ ] Yaml
