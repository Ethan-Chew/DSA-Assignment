#include <iostream>
#include <limits>
#include "MyList.h"
#include "models/Application.h"
#include "PtrQueue.h"

#include "AutoCompletionEngine.h"

enum StringType {
    MOVIE,
    ACTOR,
};

class AutoCompletionEngine {
private:
    std::string buf; // Stores user input
    MyList<std::string> valid; // Valid autocomplete options

    // Converts entire string to lowercase
    std::string toLower(const std::string &s) {
        std::string lower = s;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

    // Find all possible autocomplete suggestions from valid that match the current user input.
    MyList<std::string> GetMatches() {
        MyList<std::string> matches;
        // Retrieves the length of the user's input (buf)
        int windowSize = static_cast<int>(buf.length());

        // Loop through all possible autocomplete suggestions and find those starting with the user's input
        for (const std::string &opt : valid) {
            // Ensure that the Movie Name is longer than the Input to avoid index Out of Bound error
            // Convert everything to lowercase so that substrings will match
            // then if buf is a substring of opt, it is enqueued as a suggestion.
            if (opt.length() >= windowSize && toLower(opt).find(toLower(buf)) != std::string::npos) {
                matches.append(opt);
            }
        }
        return matches;
    }

public:
    // Initializes the autocomplete engine based on whether it's handling movies or actors.
    AutoCompletionEngine(Application &application, StringType type) {
        // Populate the 'valid' list with either Movie Titles or Actor Names
        switch (type) {
            case MOVIE: {
                auto movies = std::move(*application.getAllMovies());
                for (const Movie *i : movies) {
                    valid.append(i->getTitle());
                }
                break;
            }
            case ACTOR:
                auto actors = std::move(*application.getAllActors());
                for (const Actor *i : actors) {
                    valid.append(i->getName());
                }
                break;
        }
    }

    std::string GetInput(std::string prompt) {
        // std::cout << prompt;
        // std::cin.ignore();
        // std::getline(std::cin, buf);
        buf = prompt;

        // Get autocomplete suggestions
        MyList<std::string> matches = GetMatches();

        // If no matches found, return original input
        if (matches.is_empty()) {
            return buf;
        }

        // Display matches
        std::cout << "\nPossible matches:\n";
        for (size_t i = 0; i < matches.get_length(); ++i) {
            std::cout << i + 1 << ". " << matches[i] << '\n';
        }

        // Prompt user to select a match by index
        std::cout << "Enter the number of the correct match (or 0 to keep original input): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear newline

        if (choice > 0 && static_cast<size_t>(choice) <= matches.get_length()) {
            return matches[choice - 1]; // Return selected match
        }

        return buf; // Return original input if no valid selection
    }
};