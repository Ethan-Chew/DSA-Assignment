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
void BasicFeatures::addNewActor(Application &application) {
    try {
        // Display Menu
        std::cout << "=== Option 1: Add New Actor ===" << std::endl;

        // Set Actor ID to be 1 more than the highest value currently in the database
        int id = application.getMaxActorId() + 1;

        // Get relevant data to create Actor Object
        std::string name;
        int birthYear;
        
        std::cout << "Please enter name: ";
        std::cin.ignore();
        getline(std::cin, name);

        std::cout << "\nPlease enter birth year: ";
        std::cin >> birthYear;

        // Create new Actor Object with Unique Pointer for memory safety, then move into Dictionary
        std::unique_ptr<Actor> newActor = std::make_unique<Actor>(Actor(id, name, birthYear));
        application.addActor(std::move(newActor));

        // Get data from Actors Dictionary as the pointer has been moved there
        std::cout << "\nSuccessfully added new actor: " << std::endl;
        application.getActor(id)->print();
    }
    // Error Handling for bad inputs
    catch(std::exception &e) {
        std::cout << "An error has occurred. Please try again." << "\n";
    }
}

// Add new movie
void BasicFeatures::addNewMovie(Application &application) {
    try {
        // Display Meny
        std::cout << "=== Option 2: Add New Movie ===" << std::endl;

        // Set Movie ID to be 1 more than the highest value currently in the database
        int id = application.getMaxMovieId() + 1;

        // Get relevant data to create Movie Object
        std::string title;
        int releaseYear;
        std::string plot;
        Genre genre = NONE;

        std::cout << "Please enter movie title: ";
        std::cin.ignore();
        getline(std::cin, title);

        std::cout << "\nPlease enter movie release year: ";
        std::cin >> releaseYear;

        std::cout << "\nPlease enter movie plot: ";
        std::cin.ignore();
        getline(std::cin, plot);

        // TODO: Add Genre when implemented

        // Create new Movie Object with Unique Pointer for memory safety, then move into Dictionary
        std::unique_ptr<Movie> newMovie = std::make_unique<Movie>(Movie(id, title, releaseYear, plot, genre));
        application.addMovie(std::move(newMovie));

        // Get data from Movies Dictionary as the pointer has been moved there
        std::cout << "\nSuccessfully added new movie: " << std::endl;
        application.getMovie(id)->print();
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << std::endl;
    }
}

// Add an actor to a movie
void BasicFeatures::addActorToMovie(Application &application) {
    try {
        // Display Menu
        std::cout << "=== Option 3: Add Actor to Movie ===" << std::endl;
        int actorId;
        int movieId;

        std::cout << "Please enter Actor ID: ";
        std::cin >> actorId;

        std::cout << "\nPlease enter Movie ID: ";
        std::cin >> movieId;

        if (application.addActorToMovie(actorId, movieId)) {
            std::cout << "Actor added successfully!" << std::endl;
        }

        // TODO: Exception handling for incorrect Ids
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << std::endl;
    }
}

// Update actor/movie details
void BasicFeatures::updateActorOrMovie(Application &application) {
    try {
        // Display Menu
        std::cout << "=== Option 4: Update actor/movie details ===" << std::endl;

        int movieActorChoice;
        int actorMovieId;

        std::cout << "Update (1) Actor or (2) Movie: ";
        std::cin >> movieActorChoice;

        // Update Actor
        if (movieActorChoice == 1) {
            std::cout << "\nPlease enter Actor ID: ";
            std::cin >> actorMovieId;

            // Show chosen actor
            Actor* chosenActor = application.getActor(actorMovieId);
            std::cout << "\nActor chosen: " << std::endl;
            chosenActor->print();

            // Get relevant data to create Actor Object
            std::string name;
            std::string birthYear;

            std::cout << "Please enter updated Actor name \n (';' to skip): ";
            std::cin.ignore();
            getline(std::cin, name);

            // Skip updating name if user enters ";"
            if (name != ";") {
                chosenActor->setName(name);
            }

            std::cout << "\nPlease enter updated birth year \n (';' to skip): ";
            std::cin >> birthYear;

            // Skip updating birth year if user enters ";"
            if (birthYear != ";") {
                chosenActor->setBirthYear(std::stoi(birthYear)); // Use stoi to convert string to int
            }

            std::cout << "\nSuccessfully updated Actor information: " << std::endl;
            application.getActor(actorMovieId)->print();
        }

        // Update Movie
        else if (movieActorChoice == 2) {
            std::cout << "\nPlease enter Movie ID: ";
            std::cin >> actorMovieId;

            // Show chosen movie
            Movie* chosenMovie = application.getMovie(actorMovieId);
            std::cout << "\nMovie chosen: " << std::endl;
            chosenMovie->print();

            // Get relevant data to create Movie Object
            std::string title;
            std::string releaseYear;
            std::string plot;
            Genre genre = NONE;

            std::cout << "Please enter updated movie title \n (';' to skip): ";
            std::cin.ignore();
            getline(std::cin, title);

            // Skip updating title if user enters ";"
            if (title != ";") {
                chosenMovie->setTitle(title);
            }

            std::cout << "\nPlease enter updated movie release year \n (';' to skip): ";
            std::cin >> releaseYear;

            // Skip updating release year if user enters ";"
            if (releaseYear != ";") {
                chosenMovie->setReleaseYear(std::stoi(releaseYear));  // Use stoi to convert string to int
            }

            std::cout << "\nPlease enter updated movie plot \n (';' to skip): ";
            std::cin.ignore();
            getline(std::cin, plot);

            // Skip updating plot if user enters ";"
            if (plot != ";") {
                chosenMovie->setPlot(plot);
            }

            // TODO: Add Genre when implemented

            std::cout << "\nSuccessfully updated Movie information: " << std::endl;
            application.getMovie(actorMovieId)->print();
        }

        // Invalid Choice
        else {
            std::cout << "Invalid Option. Please choose either (1) Actor or (2) Movie." << std::endl;
        }
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "Invalid Input Entered. Please Try Again." << std::endl;
    }
}

// Additional Feature for Admin to view entire Database
void BasicFeatures::printAll(Application &application) {
    std::cout << "\nPrinting all dictionary\n";

    std::cout << "\nActors\n";
    MyLinkedList<Actor*>* actors = application.getAllActors();
    actors->print();

    std::cout << "\nMovies\n";
    MyLinkedList<Movie*>* movies = application.getAllMovies();
    movies->print();

    std::cout << "\nGets actors casted in a movie\n";
    for (int i = 0; i < movies->get_length(); i++) {
        int movieId = movies->get(i)->getId();
        movies->get(i)->print();
        application.getActors(movieId)->print();
    }

    std::cout << "\nGets movies actors acted in\n";
    for (int i = 0; i < actors->get_length(); i++) {
        int actorId = actors->get(i)->getId();
        actors->get(i)->print();
        application.getMovies(actorId)->print();
    }
}

// User Basic Functions
// Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user
void BasicFeatures::displayActors(Application &application) {
    try {
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

        // Sort and Print
        filteredActors->sort(AGE);
        filteredActors->print();
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << std::endl;
    }
}

// Display movies made within the past 3 years (in ascending order of year)
void BasicFeatures::displayMovies(Application &application) {
    try {
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
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << std::endl;
    }
}

// Display all movies an actor starred in (in alphabetical order)
void BasicFeatures::displayActorMovies(Application &application) {
    try {
        std::cout << "=== Option 3: Display all Movies an Actor starred in ===" << std::endl;

        int actorId;
        std::cout << "Actor ID: ";
        std::cin >> actorId;

        // Get and sort Movies
        MyLinkedList<Movie*>* movies = application.getMovies(actorId);
        if (movies == nullptr) {
            std::cout << "No Actor with the ID of " << actorId << " was found!" << std::endl;
            return;
        }
        movies->sort(ALPHABETICALLY);
        movies->print();
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "Invalid Actor ID provided. Please try again." << std::endl;
    }
}

// Display all the actors in a particular movie (in alphabetical order)
void BasicFeatures::displayActorsInMovie(Application& application) {
    try {
        std::cout << "=== Option 4: Display all the Actors in a Particular Movie ===" << std::endl;

        int movieId;
        std::cout << "Movie ID: ";
        std::cin >> movieId;

        // Get and sort Actors
        MyLinkedList<Actor*>* actors = application.getActors(movieId);
        if (actors == nullptr) {
            std::cout << "No Movie with the ID of " << movieId << " was found!" << std::endl;
            return;
        }
        actors->sort(ALPHABETICALLY);
        actors->print();
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "Invalid Movie ID provided. Please try again." << std::endl;
    }
}

// Display a list of all actors that a particular actor knows.
void BasicFeatures::displayKnownActors(Application &application) {
    try {
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

            // Loop through all Movies to search for Actors
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

            // Only proceed to the next level when all nodes in the current level has been processed
            if (currentDepthCount == 0) {
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
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "Invalid Actor ID provided. Please try again." << std::endl;
    }
}