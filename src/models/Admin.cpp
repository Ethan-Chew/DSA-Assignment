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
        Genre genre = NONE;

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

        // Display Genres
        std::string genres[] = { "Action", "Science Fiction", "Horror", "Thriller", "Romance", "Fantasy" };
        for (int i = 0; i < genres->length(); i++) {
            std::cout << "[" << i+1 << "] " << genres[i] << std::endl;
        }

        int genreId;
        while (true) {
            std::cout << "\nSelect a Genre (from 1 to 6): ";
            if (std::cin >> genreId && genreId >= 1 && genreId <= 6) { break; }

            // Validate Genre
            std::cout << "Invalid Genre ID! Genre ID has to be a number and within the range." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
        if (genreId == 1) {
            genre = ACTION;
        } else if (genreId == 2) {
            genre = SCIFI;
        } else if (genreId == 3) {
            genre = HORROR;
        } else if (genreId == 4) {
            genre = THRILLER;
        } else if (genreId == 5) {
            genre = ROMANCE;
        } else if (genreId == 6) {
            genre = FANTASY;
        } else {
            genre = NONE;
        }

        // Create new Movie Object with Unique Pointer for memory safety, then move into Dictionary
        std::unique_ptr<Movie> newMovie = std::make_unique<Movie>(Movie(id, title, releaseYear, plot, genre));
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

        int actorId;
        while (true) {
            std::cout << "Please enter Actor ID: ";
            if (std::cin >> actorId) { break; }

            // Validate ActorID
            std::cout << "Invalid Actor ID! Please enter a valid ID." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        int movieId;
        while (true) {
            std::cout << "\nPlease enter Movie ID: ";
            if (std::cin >> movieId) { break; }

            // Validate MovieID
            std::cout << "Invalid Movie ID! Please enter a valid ID." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        if (application->addActorToMovie(actorId, movieId)) {
            std::cout << "Actor added successfully!" << std::endl;
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

        int movieActorChoice;
        int actorMovieId;

        std::cout << "Update (1) Actor or (2) Movie: ";
        std::cin >> movieActorChoice;

        // Update Actor
        if (movieActorChoice == 1) {
            std::cout << "\nPlease enter Actor ID: ";
            std::cin >> actorMovieId;

            // Show chosen actor
            Actor* chosenActor = application->getActor(actorMovieId);
            std::cout << "\nActor chosen: " << std::endl;
            chosenActor->print();

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
                        chosenActor->setName(name);
                    }
                    break;
                }
            }

            while (true) {
                std::cout << "\nPlease enter updated birth year (';' to skip): ";
                std::cin >> birthYear;

                // Skip updating birth year if user enters ";"
                if (!birthYear.empty() && birthYear == ";") { break; }

                // Prevent crashes if input was not int
                try {
                    // Validate Birth Year and Update if valid
                    if (!birthYear.empty() && std::stoi(birthYear) > 1900 && std::stoi(birthYear) < 2026) {
                        chosenActor->setBirthYear(std::stoi(birthYear)); // Use stoi to convert string to int
                        break;
                    }
                } catch (std::exception &e) {}

                // Validate Birth Year
                std::cout << "Invalid Birth Year! Please enter a valid year." << std::endl;
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            }

            std::cout << "\nSuccessfully updated Actor information: " << std::endl;
            application->getActor(actorMovieId)->print();
        }

        // Update Movie
        else if (movieActorChoice == 2) {
            std::cout << "\nPlease enter Movie ID: ";
            std::cin >> actorMovieId;

            // Show chosen movie
            Movie* chosenMovie = application->getMovie(actorMovieId);
            std::cout << "\nMovie chosen: " << std::endl;
            chosenMovie->print();

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
                        chosenMovie->setTitle(title);
                    }
                    break;
                }
            }

            std::string releaseYear;

            while (true) {
                std::cout << "\nPlease enter updated movie release year (';' to skip): ";
                std::cin >> releaseYear;

                // Skip updating release year if user enters ";"
                if (!releaseYear.empty() && releaseYear == ";") { break; }

                // Prevent crashes if input was not int
                try {
                    // Validate Release Year and Update if valid
                    if (!releaseYear.empty() && std::stoi(releaseYear) > 1900 && std::stoi(releaseYear) < 2026) {
                        chosenMovie->setReleaseYear(std::stoi(releaseYear));  // Use stoi to convert string to int
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
                std::cout << "\nPlease enter updated movie plot (';' to skip): ";
                std::cin.ignore();
                getline(std::cin, plot);

                // Validate the Movie Plot Input
                if (plot.empty()) {
                    std::cout << "The Movie Plot cannot be empty! Please enter a valid Movie Plot." << std::endl;
                }
                else {
                    // Skip updating plot if user enters ";"
                    if (plot != ";") {
                        chosenMovie->setPlot(plot);
                    }
                    break;
                }
            }

            // Display Genres
            std::string genres[] = { "Action", "Science Fiction", "Horror", "Thriller", "Romance", "Fantasy" };
            for (int i = 0; i < genres->length(); i++) {
                std::cout << "[" << i+1 << "] " << genres[i] << std::endl;
            }

            std::string genreId;
            while (true) {
                std::cout << "\nSelect a Genre (from 1 to 6) (';' to skip)";
                std::cin >> genreId;

                // Skip updating genre if user enters ";"
                if (!genreId.empty() && genreId == ";") {
                    break;
                }

                // Prevent crashes if input was not int
                try {
                    // Check genreId for validity
                    if (std::stoi(genreId) >= 1 && std::stoi(genreId) <= 6) {
                        switch (std::stoi(genreId)) {
                            case 1:
                                chosenMovie->setGenre(ACTION);
                            case 2:
                                chosenMovie->setGenre(SCIFI);
                            case 3:
                                chosenMovie->setGenre(HORROR);
                            case 4:
                                chosenMovie->setGenre(THRILLER);
                            case 5:
                                chosenMovie->setGenre(ROMANCE);
                            case 6:
                                chosenMovie->setGenre(FANTASY);
                            default:
                                chosenMovie->setGenre(NONE);
                        }
                    }
                } catch (std::exception &e) {}

                // Validate Genre
                std::cout << "Invalid Genre ID! Genre ID has to be a number or ';' and within the range." << std::endl;
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            }

            std::cout << "\nSuccessfully updated Movie information: " << std::endl;
            application->getMovie(actorMovieId)->print();
        }

        // Invalid Choice
        else {
            std::cout << "Invalid Option. Please choose either (1) Actor or (2) Movie." << std::endl;
        }
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

/*
 * Prints out our whole database of Movies and Actors
 * */
void Admin::printAll() {
    Application* application = Application::getInstance();
    try {
        std::cout << "=== Option 5: Printing database ===" << std::endl;

        std::cout << "=== Actors ===" << std::endl;
        MyList<Actor*>* actors = application->getAllActors();
        actors->print();

        std::cout << "=== Movies ===" << std::endl;
        MyList<Movie*>* movies = application->getAllMovies();
        movies->print();

        std::cout << "=== Movie Cast of each movie ===" << std::endl;
        for (int i = 0; i < movies->get_length(); i++) {
            int movieId = movies->get(i)->getId();
            movies->get(i)->print();
            application->getActors(movieId)->print();
        }

        std::cout << "=== Movies each actor was casted in ===" << std::endl;
        for (int i = 0; i < actors->get_length(); i++) {
            int actorId = actors->get(i)->getId();
            actors->get(i)->print();
            application->getMovies(actorId)->print();
        }
    }
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}
