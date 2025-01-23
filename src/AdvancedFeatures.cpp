//
// Created by ethan on 22/1/2025.
//

#include "AdvancedFeatures.h"
#include <limits>

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

void AdvancedFeatures::displayAndSortActors(Application& application) {
    std::cout << "=== Option 7: Display and Sort a list of all Movies ===" << std::endl;

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

    MyLinkedList<Actor*>* actors = application.getAllActors();
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

void AdvancedFeatures::displayAndSortMovies(Application& application) {
    std::cout << "Option 6: Display and Sort a list of all Actors" << std::endl;

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
        sortType = AGE;
    } else {
        sortType = RATING;
    }

    MyLinkedList<Movie*>* movies = application.getAllMovies();
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
