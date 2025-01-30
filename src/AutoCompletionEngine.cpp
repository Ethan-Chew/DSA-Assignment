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
    std::string buf;
    MyList<std::string> valid;

    PtrQueue<std::string> GetMatches() {
        PtrQueue<std::string> matches;
        // no chance the input string is 2bln chars
        int windowSize = static_cast<int>(buf.length());

        for (const std::string &opt : valid) {
            // first do a length check to avoid OOB reads
            // then check if substr matches
            if (opt.length() >= windowSize && opt.substr(0, windowSize) == buf) {
                matches.enqueue(opt);
            }
        }

        return matches;
    }

public:
    AutoCompletionEngine(Application &app, StringType type) {
        // populate valid list
        switch (type) {
            case MOVIE: {
                auto *movies = app.getAllMovies();
                for (const Movie *i : *movies) {
                    valid.append(i->getTitle());
                }
                break;
            }
            case ACTOR:
                auto *actors = app.getAllActors();
                for (const Actor *i : *actors) {
                    valid.append(i->getName());
                }
                break;
        }
    }

    std::string GetInput(const std::string &prompt="Enter string or press tab to autocomplete > ") {
        PtrQueue<std::string> matches;
        std::string suggestion;

        // dont want buffering here to reflect changes in real time
        std::cin.tie(nullptr);
        std::cout << std::unitbuf;
        std::cout << prompt << std::flush;

        while (true) {
            char chr;
            std::cin.get(chr);
            if (chr == '\t') {
                matches = GetMatches();
                bool success = matches.dequeue(suggestion);
                if (success) {
                    buf = suggestion;
                }

                std::cout << "\r" << std::string(prompt.length() + buf.length(), ' ') << "\r" << prompt << buf << std::flush;
                continue;
            }

            if (chr == '\b') {
                // if there are letters in the buffer, remove one, else do nothing
                !buf.empty() ? buf.pop_back() : void();
                continue;
            }

            if (chr == '\n') {
                break;
            }

            buf += chr;
        }

        // reset buffering for caller
        std::cout << std::nounitbuf;
        return buf;
    }
};