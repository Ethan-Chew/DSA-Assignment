//
// Created by ethan on 22/1/2025.
//

#include "AdvancedFeatures.h"
#include <limits>

#include "PtrQueue.h"

// Helper Function to handle rating of Rateable Objects
void handleRate(Rateable* obj) {
    int rate;
    while (true) {
        std::cout << "Rating (from 1 to 5): ";
        if (std::cin >> rate && rate >= 1 && rate <= 5) { break; }

        std::cout << "Invalid Rating! Please enter a number from 1 to 5." << std::endl;
    }

    obj->addRating(rate);
    std::cout << "Rating Updated! New Rating: " << obj->getRating() << std::endl;
}

void AdvancedFeatures::displayAndSortMovies(Application& application) {
    std::cout << "Option 6: Display and Sort a list of all Movies" << std::endl;

    std::cout << "Filtering Options" << std::endl;
    std::cout << "[1] Alphabetically" << std::endl;
    std::cout << "[2] Release Year" << std::endl;
    std::cout << "[3] Rating" << std::endl;

    int selectedFilter;
    while (true) {
        std::cout << "Option: ";
        if (std::cin >> selectedFilter && selectedFilter >= 1 && selectedFilter <= 3) { break; }

        std::cout << "Invalid Filter Option! Filter Option has to be a number and within the range." << std::endl;
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

    SortType sortType;
    if (selectedFilter == 1) {
        sortType = ALPHABETICALLY;
    } else if (selectedFilter == 2) {
        sortType = RELEASE_YEAR;
    } else {
        sortType = RATING;
    }

    MyList<Movie*>* movies = application.getAllMovies();
    movies->sort(sortType);
    movies->print();

    // Handle Rating
    std::string optn;
    std::cout << "Do you want to rate any movie in the list? (y/n): ";
    while (true) {
        std::cin >> optn;
        if (optn.empty() || (optn != "y" && optn != "n")) {
            std::cout << "Invalid Option! Please try again." << std::endl;
        } else { break; }
    }
    if (optn == "y") {
        int movieId;
        Movie* movie;
        while (true) {
            std::cout << "\nMovie ID: ";
            if (std::cin >> movieId) {
                movie = application.getMovie(movieId);
                if (movie == nullptr) {
                    std::cout << "Invalid Movie ID! Please try again." << std::endl;
                }
                break;
            }

            // Validate Movie ID
            std::cout << "Movie ID must be a number! Please enter a valid year." << std::endl;
        }
        handleRate(movie);
    }
}

void AdvancedFeatures::displayAndSortActors(Application& application) {
    std::cout << "=== Option 7: Display and Sort a list of all Actors ===" << std::endl;

    std::cout << "Filtering Options" << std::endl;
    std::cout << "[1] Alphabetically" << std::endl;
    std::cout << "[2] Age" << std::endl;
    std::cout << "[3] Rating" << std::endl;

    int selectedFilter;
    while (true) {
        std::cout << "Option: ";
        if (std::cin >> selectedFilter && selectedFilter >= 1 && selectedFilter <= 3) { break; }

        std::cout << "Invalid Filter Option! Filter Option has to be a number and within the range." << std::endl;
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

    SortType sortType;
    if (selectedFilter == 1) {
        sortType = ALPHABETICALLY;
    } else if (selectedFilter == 2) {
        sortType = AGE;
    } else {
        sortType = RATING;
    }

    MyList<Actor*>* actors = application.getAllActors();
    actors->sort(sortType);
    actors->print();

    // Handle Rating
    std::string optn;
    std::cout << "Do you want to rate any actor in the list? (y/n): ";
    while (true) {
        std::cin >> optn;
        if (optn.empty() || (optn != "y" && optn != "n")) {
            std::cout << "Invalid Option! Please try again." << std::endl;
        } else { break; }
    }
    if (optn == "y") {
        int actorId;
        Actor* actor;
        while (true) {
            std::cout << "\nActor ID: ";
            if (std::cin >> actorId) {
                actor = application.getActor(actorId);
                if (actor == nullptr) {
                    std::cout << "Invalid Actor ID! Please try again." << std::endl;
                }
                break;
            }

            // Validate Actor ID
            std::cout << "Actor ID must be a number! Please enter a valid year." << std::endl;
        }
        handleRate(actor);
    }
}

void AdvancedFeatures::findDistanceBetweenActors(Application& application) {
    std::cout << "=== Option 8 (Advanced): Find Distance Between Two Actors ===" << std::endl;

    Actor* actor1 = nullptr;
    Actor* actor2 = nullptr;
    int actor1Id, actor2Id;

    // Allow input and Validate that actor exists
    while (true) {
        std::cout << "\nActor 1 ID: ";
        if (std::cin >> actor1Id) {
            actor1 = application.getActor(actor1Id);
            if (actor1 == nullptr) {
                std::cout << "Actor with ID: " << actor1Id << " does not exist. Please try again." << std::endl;
            } else { break; }
        } else {
            std::cout << "Invalid Actor ID! Please try again." << std::endl;
        }
    }
    while (true) {
        std::cout << "\nActor 2 ID: ";
        if (std::cin >> actor2Id) {
            actor2 = application.getActor(actor2Id);
            if (actor2 == nullptr) {
                std::cout << "Actor with ID: " << actor1Id << " does not exist. Please try again." << std::endl;
            } else { break; }
        } else {
            std::cout << "Invalid Actor ID! Please try again." << std::endl;
        }
    }

    // Run BFS and find the distance between the two Actors
    if (actor1Id == actor2Id) {
        std::cout << "Distance: 0 | Actors are the same." << std::endl;
        return;
    }

    bool didFind = false;
    PtrQueue<int>* queue = new PtrQueue<int>(); // Keep track of nodes to visit
    SortedList* visited = new SortedList();
    MyDict<int, int> previous; // Stores a list of a node, and it's parent node. Used to backtrack later on

    queue->enqueue(actor1Id); // Save the starting node into the queue
    previous.add(actor1Id, -1); // Save the Starting Node into the Dictionary, with a 'parent node' of -1 to indicate the start

    while (!queue->is_empty()) {
        int currNode;
        queue->dequeue(currNode); // Dequeue the queue and save that as the current node to traverse
        visited->insert(currNode); // Add the Actor ID to the list of visited nodes

        SortedList* movieIds = application.getActorMovies(currNode); // Retrieve all movies that the actor was part of
        for (int i = 0; i < movieIds->getLength(); i++) { // Iterate through all movieIds
            SortedList* actorIds = application.getMovieActors(movieIds->get(i)); // Get the actor who was part of a movie
            for (int j = 0; j < actorIds->getLength(); j++) { // Iterate through all actorIds
                int otherActorId = actorIds->get(j);

                if (visited->find(otherActorId) != -1) { continue; }
                visited->insert(otherActorId);

                queue->enqueue(otherActorId);
                previous.add(otherActorId, currNode);

                if (otherActorId == actor2Id) {
                    didFind = true;
                    break;
                }
            }
        }
    }

    if (didFind) {
        std::cout << "Backtracking from Actor 2 to Actor 1: ";
        // Backtrack from the end to the start
        int currNode = actor2Id; // Start from the end
        int distance = 0;
        while (currNode != -1) {
            if (distance > 0) { // Handle Formatting
                std::cout << " -> ";
            }
            std::cout << currNode;
            currNode = previous[currNode];
            distance++;
        }
        std::cout << std::endl << "Total Distance: " << distance << std::endl;
    } else {
        std::cout << "These two actors will never know each other." << std::endl;
    }
}
