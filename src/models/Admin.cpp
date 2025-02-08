//
// Created by ethan on 5/2/2025.
//

#include "models/Admin.h"

#include <models/Application.h>
#include <iostream>
#include <limits>

Admin::Admin(std::string usrname, std::string pwd): Account(usrname, pwd) { }
bool Admin::isUserAdmin() const {
    return true;
}

// Admin Basic Features
// Admin Basic Functions
/*
 * Add a New Actor
 *
 * Retrieves input for various fields (Name and Birth Year) to create a new actor object,
 * then saves it into the Application
 */
void Admin::addNewActor() {
    Application* application = Application::getInstance();

    try {
        // Display Menu
        std::cout << "=== Option 1: Add New Actor ===" << std::endl;

        // Set Actor ID to be 1 more than the highest value currently in the database
        int id = application->getMaxActorId() + 1;

        // Get relevant data to create Actor Object
        std::string name;
        int birthYear;

        while (true) {
            std::cout << "Please enter name: ";
            std::cin.ignore();
            getline(std::cin, name);

            // Validate the Name Input
            if (name.empty()) {
                std::cout << "Your name cannot be empty. Please enter a valid name." << std::endl;
            } else { break; }
        }

        while (true) {
            std::cout << "\nPlease enter Birth Year: ";
            if (std::cin >> birthYear && birthYear > 1900 && birthYear < 2026) { break; }

            // Validate Birth Year
            std::cout << "Invalid Birth Year! Please enter a valid year." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        // Create new Actor Object with Unique Pointer for memory safety, then move into Dictionary
        std::unique_ptr<Actor> newActor = std::make_unique<Actor>(Actor(id, name, birthYear));
        application->addActor(std::move(newActor));

        // Get data from Actors Dictionary as the pointer has been moved there
        std::cout << "\nSuccessfully added new actor: " << std::endl;
        application->getActor(id)->print();
    }
    // Error Handling for bad inputs
    catch(std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

/*
 * Adds a New Movie
 *
 * Retrieves input for various fields (Release Year, Plot and Genre) to create a new movie object,
 * then saves it into the Application
 * */
void Admin::addNewMovie() {
    Application* application = Application::getInstance();

    try {
        // Display Menu
        std::cout << "=== Option 2: Add New Movie ===" << std::endl;

        // Set Movie ID to be 1 more than the highest value currently in the database
        int id = application->getMaxMovieId() + 1;

        // Get relevant data to create Movie Object
        std::string title;
        int releaseYear;
        std::string plot;

        while (true) {
            std::cout << "Please enter movie title: ";
            std::cin.ignore();
            getline(std::cin, title);

            // Validate the Name Input
            if (title.empty()) {
                std::cout << "The Movie Title cannot be empty! Please enter a valid Movie Title." << std::endl;
            } else { break; }
        }

        while (true) {
            std::cout << "\nPlease enter movie release year: ";
            if (std::cin >> releaseYear && releaseYear > 1900 && releaseYear < 2026) { break; }

            // Validate Release Year
            std::cout << "Invalid Release Year! Please enter a valid year." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        while (true) {
            std::cout << "\nPlease enter movie plot: ";
            std::cin.ignore();
            getline(std::cin, plot);

            // Validate the Movie Plot Input
            if (title.empty()) {
                std::cout << "The Movie Plot cannot be empty! Please enter a valid Movie Plot." << std::endl;
            } else { break; }
        }

        // Create new Movie Object with Unique Pointer for memory safety, then move into Dictionary
        std::unique_ptr<Movie> newMovie = std::make_unique<Movie>(Movie(id, title, releaseYear, plot));
        application->addMovie(std::move(newMovie));

        // Get data from Movies Dictionary as the pointer has been moved there
        std::cout << "\nSuccessfully added new movie: " << std::endl;
        application->getMovie(id)->print();
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

/*
 * Adds existing Actor to an existing Movie
 *
 * Retrieves input about the Actor ID and Movie ID, then modifies the relationship between them
 * */
void Admin::addActorToMovie() {
    Application* application = Application::getInstance();

    try {
        // Display Menu
        std::cout << "=== Option 3: Add Actor to Movie ===" << std::endl;

        Actor* actor = application->searchForActor(); // Get validated actor item
        int actorId = actor->getId();

        Movie* movie = application->searchForMovie(); // Get validated movie item
        int movieId = movie->getId();

        if (application->addActorToMovie(actorId, movieId)) {
            std::cout << "Actor" << actor->getName() << " added to movie" << movie->getTitle() << "successfully!" << std::endl;
        }
        else {
            std::cout << "Please enter valid Actor and Movie IDs." << std::endl;
        }
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

// Helper Function to Update an Actor
void updateActor(Actor* actor) {
    std::cout << "\nChosen Actor:" << std::endl;
    actor->print();
    std::cout << std::endl;

    // Get relevant data to create Actor Object
    std::string name;
    std::string birthYear;

    while (true) {
        std::cout << "Please enter updated Actor name (';' to skip): ";
        std::cin.ignore();
        getline(std::cin, name);

        // Validate the Name Input
        if (name.empty()) {
            std::cout << "Your name cannot be empty. Please enter a valid name." << std::endl;
        }
        else {
            // Skip updating name if user enters ";"
            if (name != ";") {
                actor->setName(name);
            }
            break;
        }
    }

    while (true) {
        std::cout << "Please enter updated birth year (';' to skip): ";
        std::cin >> birthYear;

        // Skip updating birth year if user enters ";"
        if (!birthYear.empty() && birthYear == ";") { break; }

        // Prevent crashes if input was not int
        try {
            // Validate Birth Year and Update if valid
            if (!birthYear.empty() && std::stoi(birthYear) > 1900 && std::stoi(birthYear) < 2026) {
                actor->setBirthYear(std::stoi(birthYear)); // Use stoi to convert string to int
                break;
            }
        } catch (std::exception &e) {}

        // Validate Birth Year
        std::cout << "Invalid Birth Year! Please enter a valid year." << std::endl;
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

    std::cout << "\nSuccessfully updated Actor information: " << std::endl;
    actor->print();
    std::cout << std::endl;
}

// Helper Function to Update a Movie
void updateMovie(Movie* movie) {
    std::cout << "\nChosen Movie:" << std::endl;
    movie->print();
    std::cout << std::endl;

    // Get relevant data to create Movie Object
    std::string title;
    while (true) {
        std::cout << "Please enter updated movie title (';' to skip): ";
        std::cin.ignore();
        getline(std::cin, title);

        // Validate the Movie Title Input
        if (title.empty()) {
            std::cout << "The Movie Title cannot be empty! Please enter a valid Movie Plot." << std::endl;
        }
        else {
            // Skip updating title if user enters ";"
            if (title != ";") {
                movie->setTitle(title);
            }
            break;
        }
    }

    std::string releaseYear;

    while (true) {
        std::cout << "Please enter updated movie release year (';' to skip): ";
        std::cin >> releaseYear;

        // Skip updating release year if user enters ";"
        if (!releaseYear.empty() && releaseYear == ";") { break; }

        // Prevent crashes if input was not int
        try {
            // Validate Release Year and Update if valid
            if (!releaseYear.empty() && std::stoi(releaseYear) > 1900 && std::stoi(releaseYear) < 2026) { // TODO: is 1900 a good limit?
                movie->setReleaseYear(std::stoi(releaseYear));  // Use stoi to convert string to int
                break;
            }
        } catch (std::exception &e) {}

        // Validate Release Year
        std::cout << "Invalid Release Year! Please enter a valid year." << std::endl;
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

    std::string plot;
    while (true) {
        std::cout << "Please enter updated movie plot (';' to skip): ";
        std::cin.ignore();
        getline(std::cin, plot);

        // Validate the Movie Plot Input
        if (plot.empty()) {
            std::cout << "The Movie Plot cannot be empty! Please enter a valid Movie Plot." << std::endl;
        }
        else {
            // Skip updating plot if user enters ";"
            if (plot != ";") {
                movie->setPlot(plot);
            }
            break;
        }
    }

    std::cout << "\nSuccessfully updated Movie information: " << std::endl;
    movie->print();
    std::cout << std::endl;
}

/*
 * Updates either the details of the Actor or the Movie
 *
 * Asks the user if they would like to update an Actor or Movie, then proceeds to take input of new field values
 * */
void Admin::updateActorOrMovie() {
    Application* application = Application::getInstance();

    try {
        // Display Menu
        std::cout << "=== Option 4: Update actor/movie details ===" << std::endl;

        // Get the User's Update Choice (Movie/Actor)
        int movieActorChoice;
        while (true) {
            std::cout << "\nUpdate (1) Actor or (2) Movie: ";
            if (std::cin >> movieActorChoice && (movieActorChoice == 1 || movieActorChoice == 2)) { break; }

            // Validate Release Year
            std::cout << "Invalid Choice! Please enter either 1 or 2." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        if (movieActorChoice == 1) {
            // Selected Actor
            Actor* actor = application->searchForActor(); // Get validated actor item
            updateActor(actor);
        } else {
            // Selected Movie
            Movie* movie = application->searchForMovie(); // Get validated movie item
            updateMovie(movie);
        }
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

void Admin::reviewReports() {
    std::cout << "\n=== Option 5: Review all Reports ===" << std::endl;
    Application* application = Application::getInstance();

    auto reports = application->retrieveAllReports();
    for (int i = 0; i < reports->get_length(); i++) {
        std::cout << i + 1 << ") Type: " << reports->get(i)->getType() << " | Description: " << reports->get(i)->getDescription() << " | Is Resolved: " << (reports->get(i)->getIsResolved() ? "Yes" : "No") << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Would you like to Resolve a Report?" << std::endl;
    std::string userResponse;
    while (true) {
        std::cout << "Response (Enter y or n): ";
        if (std::cin >> userResponse && (userResponse == "y" || userResponse == "n")) { break; }

        std::cout << "Reply should be either 'y' or 'n'!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (userResponse == "n") { return; }

    int reportId;
    while (true) {
        std::cout << "Please enter the Report ID: ";
        if (std::cin >> reportId && reportId > 0 && reportId <= reports->get_length()) { break; }

        // Validate Affected Id
        std::cout << "Invalid Report ID format! Ensure that Report ID is an integer!" << std::endl;
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

    // Display Report Details
    Report* report = reports->get(reportId - 1).get();
    std::cout << "Report Details:" << std::endl;
    std::cout << "Type: " << report->getType() << std::endl;
    std::cout << "Description: " << report->getDescription() << std::endl;
    std::cout << "Actor/Movie Affected: " << report->getAffectedId() << std::endl;

    if (report->getType() == "Actor") {
        Actor* actor = application->getActor(report->getAffectedId());
        updateActor(actor);
    } else {
        Movie* movie = application->getMovie(report->getAffectedId());
        updateMovie(movie);
    }

    report->setIsResolved(true);
}