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

    // Find all possible autocomplete suggestions from valid that match the current buf input.
    PtrQueue<std::string> GetMatches() {
        PtrQueue<std::string> matches;
        // Retrieves input (buf) length
        int windowSize = static_cast<int>(buf.length());

        for (const std::string &opt : valid) {
            // first do a length check to avoid OOB reads (Movie name should be longer than input)
            // then if the first windowSize characters of opt match buf, it is enqueued as a suggestion.
            if (opt.length() >= windowSize && opt.substr(0, windowSize) == buf) {
                matches.enqueue(opt);
            }
        }
        return matches;
    }

public:
    // Initializes the autocomplete engine based on whether it's handling movies or actors.
    AutoCompletionEngine(Application &app, StringType type) {
        // populate valid list
        switch (type) {
            case MOVIE: {
                auto movies = app.getAllMoviesList();
                for (const Movie *i : movies) {
                    valid.append(i->getTitle());
                }
                break;
            }
            case ACTOR:
                auto actors = app.getAllActorsList();
                for (const Actor *i : actors) {
                    valid.append(i->getName());
                }
                break;
        }
    }

    // std::string GetInput(const std::string &prompt="Enter string or press tab to autocomplete > ") {
    //     PtrQueue<std::string> matches;
    //     std::string suggestion;
    //
    //     // dont want buffering here to reflect changes in real time
    //     std::cin.tie(nullptr);
    //     std::cout << std::unitbuf;
    //     std::cout << prompt << std::flush;
    //
    //     while (true) {
    //         char chr;
    //         std::cin.get(chr);
    //         if (chr == '\t') {
    //             matches = GetMatches();
    //             bool success = matches.dequeue(suggestion);
    //             if (success) {
    //                 buf = suggestion;
    //             }
    //
    //             std::cout << "\r" << std::string(prompt.length() + buf.length(), ' ') << "\r" << prompt << buf << std::flush;
    //             continue;
    //         }
    //
    //         if (chr == '\b') {
    //             // if there are letters in the buffer, remove one, else do nothing
    //             !buf.empty() ? buf.pop_back() : void();
    //             continue;
    //         }
    //
    //         if (chr == '\n') {
    //             break;
    //         }
    //
    //         buf += chr;
    //     }
    //
    //     // reset buffering for caller
    //     std::cout << std::nounitbuf;
    //     return buf;
    // }

    std::string GetInput(const std::string &prompt = "Enter a string: ") {
        std::string input;
        std::cout << prompt;
        std::cin.ignore();
        std::getline(std::cin, input);

        // Get autocomplete suggestions
        PtrQueue<std::string> matches = GetMatches();
        std::vector<std::string> suggestions;

        while (!matches.is_empty()) {
            std::string match;
            if (matches.dequeue(match)) {
                suggestions.push_back(match);
            }
        }

        // If no matches found, return original input
        if (suggestions.empty()) {
            return input;
        }

        // Display matches
        std::cout << "\nPossible matches:\n";
        for (size_t i = 0; i < suggestions.size(); ++i) {
            std::cout << i + 1 << ". " << suggestions[i] << '\n';
        }

        // Prompt user to select a match by index
        std::cout << "Enter the number of the correct match (or 0 to keep original input): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear newline

        if (choice > 0 && static_cast<size_t>(choice) <= suggestions.size()) {
            return suggestions[choice - 1]; // Return selected match
        }

        return input; // Return original input if no valid selection
    }

};