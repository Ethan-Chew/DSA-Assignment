//
// Created by d on 17/1/2025.
//

#include "../include/BasicFeatures.h"
#include <iostream>
#include "MyDict.h"
#include "models/Application.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "MyLinkedList.h"
#include "PtrQueue.h"

// Admin Basic Functions
// Add new actor
bool BasicFeatures::addNewActor(Application &application) {
    try {
        std::string name;
        int birthYear;

        std::cout <<
            "Option: 'Add New Actor' Selected.\n"
            "Please enter name: ";
        getline(std::cin, name);

        std::cout << "\nPlease enter birth year: ";
        std::cin >> birthYear;

        // TODO: Add Id parser

        std::unique_ptr<Actor> newActor = std::make_unique<Actor>(Actor(0, name, birthYear));
        application.addActor(std::move(newActor));

        std::cout << "\nSuccessfully added new movie: " << std::endl;
        newActor->print();

        return true;
    }
    catch(std::exception &e) {
        std::cout << "An error has occurred. Please try again." << "\n";
        return false;
    }
}

// Add new movie
bool BasicFeatures::addNewMovie(Application &application) {
    try {
        std::string title;
        int releaseYear;
        std::string plot;

        std::cout <<
            "Option: 'Add New Movie' Selected.\n"
            "Please enter movie title: ";
        getline(std::cin, title);

        std::cout << "\nPlease enter movie release year: ";
        std::cin >> releaseYear;

        std::cout << "\nPlease enter movie plot: ";
        getline(std::cin, plot);

        // TODO Add Genre when implemented

        // TODO: Add Id parser

        std::unique_ptr<Movie> newMovie = std::make_unique<Movie>(Movie(0, title, releaseYear, plot, Genre::NONE));
        application.addMovie(std::move(newMovie));

        std::cout << "\nSuccessfully added new movie: " << std::endl;
        newMovie->print();

        return true;
    }
    catch (std::exception &e) {
        std::cout << "An error has occurred. Please try again." << "\n";
        return false;
    }
}

// Add an actor to a movie
bool BasicFeatures::addActorToMovie(Application &application) {
    int actorId;
    int movieId;

    std::cout <<
            "Option: 'Add Actor to Movie' Selected.\n"
            "Please enter actor's id: ";
    std::cin >> actorId;

    std::cout << "\nPlease enter movie id: ";
    std::cin >> movieId;

    if (application.addActorToMovie(actorId, movieId)) {
        std::cout << "Actor added successfully!" << "\n";
        return true;
    }
    return false;
}

// Update actor/movie details
bool BasicFeatures::updateActorOrMovie(Application &application) {
    int movieActorChoice;
    int actorMovieId;

    std::cout <<
            "Option: 'Update actor/movie details' Selected.\n"
            "Update (1) Actor or (2) Movie: ";
    std::cin >> movieActorChoice;

    // TODO: Add get actor/movie with Id functionality in application
    if (movieActorChoice == 1) {
        std::cout << "\nPlease enter actor id: ";
        std::cin >> actorMovieId;

        Actor* chosenActor = application.getActor(actorMovieId);
        std::cout << "\nActor chosen: " << std::endl;
        chosenActor->print();

    }
    else if (movieActorChoice == 2) {
        std::cout << "\nPlease enter actor id: ";
        std::cin >> actorMovieId;

        Movie* chosenMovie = application.getMovie(actorMovieId);
        std::cout << "\nMovie chosen: " << std::endl;
        chosenMovie->print();
    }
    else {
        std::cout << "Invalid Input. Please try again." << "\n";
        return false;
    }
    return true;
}

// User Basic Functions
// Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user
bool BasicFeatures::displayActors(Application &application) {
    std::cout << "=== Option 1: Display (in ascending order of age) the Actors with age between x and y (inclusive) ===" << std::endl;

    int startAge, endAge;
    // Get User Input, and Validate
    while (true) {
        std::cout << "Starting Age: ";
        std::cin >> startAge;
        std::cout << "Ending Age: ";
        std::cin >> endAge;

        if (startAge <= 0 || endAge <= 0) {
            std::cout<< "The Starting and Ending Age must be greater than 0" << std::endl;
        } else { break; }
    }

    MyLinkedList<Actor*>* actors = application.getAllActors();
    auto* filteredActors = new MyLinkedList<Actor*>();

    // Filter the LinkedList and only preserve Actors between the age range
    const int currentYear = 2025; // TODO: Use STL to get current year
    for (int i = 0; i < actors->get_length(); i++) {
        Actor* actor = actors->get(i);
        int actorCurrentAge = currentYear - actor->getBirthYear();
        if (actorCurrentAge >= startAge && actorCurrentAge <= endAge) {
            filteredActors->append(actor);
        }
    }

    filteredActors->sort(AGE);
    filteredActors->print();

    return true;
}

// Display movies made within the past 3 years (in ascending order of year)
bool BasicFeatures::displayMovies(Application &application) {
    std::cout << "=== Option 2: Display Movies made within the past 3 years ===" << std::endl;

    MyLinkedList<Movie*>* movies = application.getAllMovies();
    auto* filteredMovies = new MyLinkedList<Movie*>();

    // Filter the LinkedList and only preserve Movies that were made in the past 3 years
    const int currentYear = 2025; // TODO: Use STL to get current year
    for (int i = 0; i < movies->get_length(); i++) {
        Movie* movie = movies->get(i);
        if ((currentYear - movie->getReleaseYear()) <= 3) {
            filteredMovies->append(movie);
        }
    }

    filteredMovies->sort(RELEASE_YEAR);

    if (filteredMovies->get_length() == 0) {
        std::cout << "There are no Movies in the past 3 years" << std::endl;
    }

    filteredMovies->print();

    return true;
}

// Display all movies an actor starred in (in alphabetical order)
bool displayActorMovies(Application &application) {
    std::cout << "=== Option 3: Display all Movies an Actor starred in ===" << std::endl;
    int actorId;
    std::cout << "Actor ID: ";
    std::cin >> actorId;

    MyLinkedList<Movie*>* movies = application.getMovies(actorId);
    if (movies == nullptr) {
        std::cout << "No Actor with the ID of " << actorId << " was found!" << std::endl;
        return false;
    }
    movies->sort(ALPHABETICALLY);
    movies->print();

    return true;
}

// Display all the actors in a particular movie (in alphabetical order)
void BasicFeatures::displayActorsInMovie(Application& application) {
    std::cout << "=== Option 4: Display all the Actors in a Particular Movie ===" << std::endl;
    int movieId;
    std::cout << "Movie ID: ";
    std::cin >> movieId;

    MyLinkedList<Actor*>* actors = application.getActors(movieId);
    if (actors == nullptr) {
        std::cout << "No Movie with the ID of " << movieId << " was found!" << std::endl;
        return;
    }
    actors->sort(ALPHABETICALLY);
    actors->print();
}

// Display a list of all actors that a particular actor knows.
void BasicFeatures::displayKnownActors(Application &application) {
    // Display Starting Menu
    std::cout << "=== Option 5: Display list of all actors that a particular actor knows ===" << std::endl;
    int actorId;
    std::cout << "Actor ID: ";
    std::cin >> actorId;

    SortedList* firstLevel = new SortedList(); // First Level Connections (directly worked with them in a Movie)
    SortedList* secondLevel = new SortedList(); // Second Level Connections (knowing someone through another person)

    // Perform Breadth-First Search (BFS) on the Relationship Dictionaries to determine first and second level connections
    PtrQueue<int>* queue = new PtrQueue<int>();
    SortedList* visitedNodes = new SortedList(); // Hold the nodes that has already been visited (reduce repeats)
    queue->enqueue(actorId);
    visitedNodes->insert(actorId);

    int depth = 1; // How 'deep' you are in the tree. Start at depth = 1
    int currentDepthCount = 1; // Number of nodes in the current depth
    int nextDepthCount = 0;    // Number of nodes in the next depth

    while (!queue->is_empty() && depth <= 2) { // Only need to search until 2nd Layer
        int currentActorId;
        queue->get_front(currentActorId);
        queue->dequeue();
        currentDepthCount--; // Once popped from the queue, there is one less node to traverse later

        SortedList* movies = application.getActorMovies(currentActorId);
        if (movies == nullptr) {
            std::cout << "Actor has not acted in any movies." << std::endl;
            return;
        }
        for (int i = 0; i < movies->getLength(); i++) {
            int movieId = movies->get(i);

            if (visitedNodes->find(movieId) != -1) continue; // Skip Movies that have already been iterated through
            visitedNodes->insert(movieId); // We have now visited it, so mark it as visited

            // Find the Other Actors that have acted in the Movie
            SortedList* otherActors = application.getMovieActors(movieId);
            for (int j = 0; j < otherActors->getLength(); j++) {
                int otherActorId = otherActors->get(j);

                if (visitedNodes->find(otherActorId) != -1) continue; // Skip the actor that has already been iterated through
                visitedNodes->insert(otherActorId); // Now that we have visited the actor, mark as visited

                // Add the Actor to either the First or Second Level
                if (depth == 1) {
                    firstLevel->insert(otherActorId);
                } else if (depth == 2) {
                    secondLevel->insert(otherActorId);
                }

                // Enqueue the Other Actor ID for further processing
                queue->enqueue(otherActorId);
                nextDepthCount++; // Increment 1 to the number of nodes in the next depth
            }
        }
        if (currentDepthCount == 0) { // Only proceed to the next level when all nodes in the current level has been processed
            depth++;
            currentDepthCount = nextDepthCount; // Move to next level
            nextDepthCount = 0; // Reset the count for next level
        }
    }

    // Display the First Level Actors
    std::cout << "=== First Level (Actor has directly interacted with) ===" << std::endl;
    for (int i = 0; i < firstLevel->getLength(); i++) {
        Actor* actor = application.getActor(firstLevel->get(i));
        actor->print();
    }

    std::cout << std::endl; // Print Empty Line

    // Display the Second Level Actors
    std::cout << "=== Second Level (Actor knows someone who has interacted with) ===" << std::endl;
    for (int i = 0; i < secondLevel->getLength(); i++) {
        Actor* actor = application.getActor(secondLevel->get(i));
        actor->print();
    }

    std::cout << std::endl; // Print Empty Line
}