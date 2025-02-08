//
// Created by yy on 22/1/2025.
//

#pragma once
#ifndef DSA_AUTOCOMPLETIONENGINE_H
#define DSA_AUTOCOMPLETIONENGINE_H
#include "MyList.h"
#include "models/Application.h"

// Enum for specifying the type of autocomplete suggestions
enum StringType {
    ACTOR,
    MOVIE
};

class AutoCompletionEngine {
private:
    std::string userInput;
    MyList<std::string> suggestionList;

    std::string toLower(const std::string &input);
    MyList<std::string> findMatchingSuggestions();

public:
    // Constructor
    explicit AutoCompletionEngine(StringType type);

    // Handles user input and returns either the matched suggestion or the original input
    std::string getUserInput(std::string prompt);
};

#endif //DSA_AUTOCOMPLETIONENGINE_H
