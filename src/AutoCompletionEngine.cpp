#include <iostream>
#include <limits>
#include <utility>
#include "MyList.h"
#include "AutoCompletionEngine.h"
#include "models/Application.h"

// Helper function to convert a string to lowercase for case-insensitive matching
std::string AutoCompletionEngine::toLower(const std::string &input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Finds all autocomplete suggestions that contain the user input as a substring (case-insensitive)
MyList<std::string> AutoCompletionEngine::findMatchingSuggestions() {
    MyList<std::string> matches;
    const std::string lowerInput = toLower(userInput);

    for (const std::string &option : suggestionList) {
        if (toLower(option).find(lowerInput) != std::string::npos) {
            matches.append(option);
        }
    }
    return matches;
}

// Constructor: Initializes the autocomplete engine with movie titles or actor names from the application
AutoCompletionEngine::AutoCompletionEngine(StringType type) {
    Application *application = Application::getInstance();
    switch (type) {
        case MOVIE: {
            MyList<Movie*>* allMovies = application->getAllMovies();
            for (const Movie *movie : *allMovies) {
                suggestionList.append(movie->getTitle());
            }
            break;
        }
        case ACTOR: {
            MyList<Actor*>* allActors = application->getAllActors();
            for (const Actor *actor : *allActors) {
                suggestionList.append(actor->getName());
            }
            break;
        }
    }
}

// Handles user input and returns either the matched suggestion or the original input
std::string AutoCompletionEngine::getUserInput(std::string prompt) {
    userInput = std::move(prompt);
    MyList<std::string> matches = findMatchingSuggestions();

    if (matches.is_empty()) {
        return userInput;  // No match found, return original input
    }

    // Display matching suggestions
    std::cout << "\nFound matches:\n";
    for (size_t i = 0; i < matches.get_length(); ++i) {
        std::cout << i + 1 << ". " << matches[i] << '\n';
    }

    // Prompt the user to select a match by its index
    std::cout << "Enter the number of the correct match (or 0 to keep the original input): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Return the selected match if valid, otherwise return the original input
    if (choice > 0 && static_cast<size_t>(choice) <= matches.get_length()) {
        return matches[choice - 1];
    }
    return userInput;
}