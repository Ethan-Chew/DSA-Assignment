//
// Created by d on 17/1/2025.
//

#include "BasicFeatures.h"
#include <iostream>
#include <limits>

#include "MyDict.h"
#include "models/Application.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "MyList.h"
#include "PtrQueue.h"

// Admin Basic Functions
/*
 * Add a New Actor
 *
 * Retrieves input for various fields (Name and Birth Year) to create a new actor object,
 * then saves it into the Application
 */
void BasicFeatures::addNewActor(Application &application) {
    try {
        // Display Menu
        std::cout << "=== Option 1: Add New Actor ===" << std::endl;

        // Set Actor ID to be 1 more than the highest value currently in the database
        int id = application.getMaxActorId() + 1;

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
        application.addActor(std::move(newActor));

        // Get data from Actors Dictionary as the pointer has been moved there
        std::cout << "\nSuccessfully added new actor: " << std::endl;
        application.getActor(id)->print();
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
void BasicFeatures::addNewMovie(Application &application) {
    try {
        // Display Menu
        std::cout << "=== Option 2: Add New Movie ===" << std::endl;

        // Set Movie ID to be 1 more than the highest value currently in the database
        int id = application.getMaxMovieId() + 1;

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
        application.addMovie(std::move(newMovie));

        // Get data from Movies Dictionary as the pointer has been moved there
        std::cout << "\nSuccessfully added new movie: " << std::endl;
        application.getMovie(id)->print();
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
void BasicFeatures::addActorToMovie(Application &application) {
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

        if (application.addActorToMovie(actorId, movieId)) {
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
            application.getMovie(actorMovieId)->print();
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

// Additional Feature for Admin to view entire Database
void BasicFeatures::printAll(Application &application) {
    try {
        std::cout << "=== Option 5: Printing database ===" << std::endl;

        std::cout << "=== Actors ===" << std::endl;
        MyList<Actor*>* actors = application.getAllActors();
        actors->print();

        std::cout << "=== Movies ===" << std::endl;
        MyList<Movie*>* movies = application.getAllMovies();
        movies->print();

        std::cout << "=== Movie Cast of each movie ===" << std::endl;
        for (int i = 0; i < movies->get_length(); i++) {
            int movieId = movies->get(i)->getId();
            movies->get(i)->print();
            application.getActors(movieId)->print();
        }

        std::cout << "=== Movies each actor was casted in ===" << std::endl;
        for (int i = 0; i < actors->get_length(); i++) {
            int actorId = actors->get(i)->getId();
            actors->get(i)->print();
            application.getMovies(actorId)->print();
        }
    }
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
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
            if (std::cin >> startAge) {
                std::cout << "Ending Age: ";
                if (std::cin >> endAge) {
                    // Validate logical age ranges
                    if (startAge > 0 && endAge > 0) {
                        if (endAge > startAge) { break; }
                        std::cout<< "The Ending Age must be greater than the Starting Age" << std::endl;
                    }
                    else {
                        std::cout<< "The Starting and Ending Age must be greater than 0" << std::endl;
                    }
                }
                else {
                    std::cout<< "The Starting and Ending Age must be an integer" << std::endl;
                }
            }
            else {
                std::cout<< "The Starting and Ending Age must be an integer" << std::endl;
            }

            // Checks failed
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        MyList<Actor*> *actorz = application.getAllActors();
        auto *filtered = new MyList<Actor*>();
        const int thisYear = 2025;

        for (const Actor* actor : *actorz) {
            int age = thisYear - actor->getBirthYear();
            if (age >= startAge && age <= endAge) filtered->append(const_cast<Actor *>(actor));
        }

        // Sort and Print
        filtered->sort(AGE);

        // todo: print
        for (const Actor* actor : *filtered) {
            std::cout
                << actor->getName()
                << "\n";
        }
        std::cout << std::endl;
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

// Display movies made within the past 3 years (in ascending order of year)
void BasicFeatures::displayMovies(Application &application) {
    try {
        std::cout << "=== Option 2: Display Movies made within the past 3 years ===" << std::endl;

        MyList<Movie*>* movies = application.getAllMovies();
        auto* filteredMovies = new MyList<Movie*>();

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
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

// Display all movies an actor starred in (in alphabetical order)
void BasicFeatures::displayActorMovies(Application &application) {
    try {
        std::cout << "=== Option 3: Display all Movies an Actor starred in ===" << std::endl;

        int actorId;
        while (true) {
            std::cout << "Please enter Actor ID: ";
            if (std::cin >> actorId) { break; }

            // Validate ActorID
            std::cout << "Invalid Actor ID! Please enter a valid ID." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        // Get and sort Movies
        MyList<Movie*>* movies = application.getMovies(actorId);
        if (movies == nullptr) {
            std::cout << "No Actor with the ID of " << actorId << " was found!" << std::endl;
            return;
        }
        if (movies->get_length() == 0) {
            std::cout << "Actor has not acted in any movie!" << std::endl;
            return;
        }
        movies->sort(ALPHABETICALLY);
        movies->print();
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

// Display all the actors in a particular movie (in alphabetical order)
void BasicFeatures::displayActorsInMovie(Application& application) {
    try {
        std::cout << "=== Option 4: Display all the Actors in a Particular Movie ===" << std::endl;

        int movieId;
        while (true) {
            std::cout << "\nPlease enter Movie ID: ";
            if (std::cin >> movieId) { break; }

            // Validate MovieID
            std::cout << "Invalid Movie ID! Please enter a valid ID." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        // Get and sort Actors
        MyList<Actor*>* actors = application.getActors(movieId);
        if (actors == nullptr) {
            std::cout << "No Movie with the ID of " << movieId << " was found!" << std::endl;
            return;
        }
        if (actors->get_length() == 0) {
            std::cout << "Movie does not have any actors!" << std::endl;
            return;
        }
        actors->sort(ALPHABETICALLY);
        actors->print();
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
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
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}