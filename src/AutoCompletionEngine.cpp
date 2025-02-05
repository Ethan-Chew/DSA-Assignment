#include <iostream>
#include <limits>
#include <utility>
#include "MyList.h"
#include "models/Application.h"
#include "PtrQueue.h"

#include "AutoCompletionEngine.h"

// Used to initialise autocomplete for either actors or movies
enum StringType {
    ACTOR,
    MOVIE,
};

class AutoCompletionEngine {
private:
    std::string userInput; // Stores the current user input
    MyList<std::string> suggestionList; // List of valid autocomplete suggestions

    // Helper function to convert a string to lowercase for case-insensitive matching
    std::string toLower(const std::string &input) {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    // Finds all autocomplete suggestions that contain the user input as a substring (case-insensitive)
    MyList<std::string> findMatchingSuggestions() {
        MyList<std::string> matches;
        const std::string lowerInput = toLower(userInput); // Convert input to lowercase once for efficiency

        for (const std::string &option : suggestionList) {
            // Use string::npos to check if substring is within option
            // string::npos is a constant that represents "not found", thus, find returns an unequal value to npos if found
            if (toLower(option).find(lowerInput) != std::string::npos) {
                matches.append(option); // Add to matches if user input is a substring of the suggestion
            }
        }
        return matches;
    }

public:
    // Constructor
    AutoCompletionEngine(Application &application, const StringType type) {
        // Initializes the autocomplete engine with either movie titles or actor names from the given application
        switch (type) {
            case MOVIE: {
                auto movies = std::move(*application.getAllMovies());
                for (const Movie *movie : movies) {
                    suggestionList.append(movie->getTitle());
                }
                break;
            }
            case ACTOR: {
                auto actors = std::move(*application.getAllActors());
                for (const Actor *actor : actors) {
                    suggestionList.append(actor->getName());
                }
                break;
            }
        }
    }

    // Handles user input and returns either the matched suggestion or the original input
    std::string getUserInput(std::string prompt) {
        userInput = std::move(prompt); // Store user input using move to prevent unnecessary copies

        // Find autocomplete suggestions that match the input
        MyList<std::string> matches = findMatchingSuggestions();

        // If no suggestions are found, return the original input
        if (matches.is_empty()) {
            return userInput;
        }

        // Display matching suggestions to the user
        std::cout << "\nPossible matches:\n";
        for (size_t i = 0; i < matches.get_length(); ++i) {
            std::cout << i + 1 << ". " << matches[i] << '\n';
        }

        // Prompt the user to select a match by its index
        std::cout << "Enter the number of the correct match (or 0 to keep the original input): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear remaining input

        // Return the selected match if the choice is valid, otherwise return the original input
        if (choice > 0 && static_cast<size_t>(choice) <= matches.get_length()) {
            return matches[choice - 1];
        }
        return userInput;
    }
};