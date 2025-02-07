//
// Created by ethan on 5/2/2025.
//

#include "models/User.h"

#include <models/Application.h>
#include <limits>

#include "PtrQueue.h"

User::User(std::string usrname, std::string pwd): Account(usrname, pwd) { }
bool User::isUserAdmin() const {
    return false;
}

// User Basic Functions
/*
 * Display Actors between two ages inclusive
 *
 * Input: x, y (starting and ending age of Actors)
 * Output: Actors printed in ascending order of age within the range
 */
void User::displayActors() {
    Application* application = Application::getInstance();
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

        MyList<Actor*> *actorz = application->getAllActors();
        auto *filtered = new MyList<Actor*>();
        const int thisYear = 2025; // TODO: DONT HARDCODE YEAR

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
void User::displayMovies() {
    Application* application = Application::getInstance();
    try {
        std::cout << "=== Option 2: Display Movies made within the past 3 years ===" << std::endl;

        MyList<Movie*>* movies = application->getAllMovies();
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
void User::displayActorMovies() {
    Application* application = Application::getInstance();
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
        MyList<Movie*>* movies = application->getMovies(actorId);
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
void User::displayActorsInMovie() {
    Application* application = Application::getInstance();
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
        MyList<Actor*>* actors = application->getActors(movieId);
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
void User::displayKnownActors() {
    Application* application = Application::getInstance();
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

            SortedList* movies = application->getActorMovies(currentActorId);
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
                SortedList* otherActors = application->getMovieActors(movieId);
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
            Actor* actor = application->getActor(firstLevel->get(i));
            actor->print();
        }
        std::cout << std::endl; // Print Empty Line

        // Display the Second Level Actors
        std::cout << "=== Second Level (Actor knows someone who has interacted with) ===" << std::endl;
        for (int i = 0; i < secondLevel->getLength(); i++) {
            Actor* actor = application->getActor(secondLevel->get(i));
            actor->print();
        }
        std::cout << std::endl; // Print Empty Line
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}

/*
 * File Report
 *
 * Allows users to file a report by specifying the Report's description, type and affected item (Actor/Movie)
 */
void User::fileReport() {
    Application* application = Application::getInstance();
    try {
        // Display Starting Menu
        std::cout << "=== Option 8: File an Error Report on a Actor or Movie ===" << std::endl;

        // Ask user to choose between Actor or Movie Report
        std::cout << "Report Type:" << std::endl;
        std::cout << "1. Actor" << std::endl;
        std::cout << "2. Movie" << std::endl;
        int reportTypeInt;
        while (true) {
            std::cout << "\nPlease enter the Report Type (1 or 2): ";
            if (std::cin >> reportTypeInt && (reportTypeInt == 1 || reportTypeInt == 2)) { break; }

            // Validate Report Type
            std::cout << "Invalid Report Type! Ensure Report Type is an Integer and either 1 or 2." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }

        // Ask User for Description of Report
        std::string desc;
        while (true) {
            std::cout << "Report Description: ";
            std::cin.ignore();
            getline(std::cin, desc);

            // Validate the Description Input
            if (desc.empty()) {
                std::cout << "The Report Description cannot be empty!" << std::endl;
            } else { break; }
        }

        // Get the Affected ID (either ID of Actor or ID of Movie)
        int affectedId;
        while (true) {
            std::cout << "Please enter the ID of the affected Actor/Movie: ";
            if (std::cin >> affectedId) {
                // Validate that the Actor/Movie with ID exists
                if (reportTypeInt == 1) {
                    // Actor
                    Actor* actor = application->getActor(affectedId);
                    if (actor == nullptr) {
                        std::cout << "No Actor with Actor ID (" << affectedId << ") found!" << std::endl;
                    } else { break; }
                } else {
                    // Movie
                    Movie* movie = application->getMovie(affectedId);
                    if (movie == nullptr) {
                        std::cout << "No Movie with Movie ID (" << affectedId << ") found!" << std::endl;
                    } else { break; }
                }
            } else {
                // Validate Affected Id
                std::cout << "Invalid Affected ID format! Ensure that Affected ID is an integer!" << std::endl;
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            }
        }

        // File a Report
        Report* report = new Report(desc, reportTypeInt == 1 ? "Actor" : "Movie", affectedId, this->getUsername());
        application->addReport(report);

        // Display Created Report
        std::cout << "Report Created!" << std::endl;
        std::cout << "Type: " << report->getType() << std::endl;
        std::cout << "Description: " << report->getDescription() << std::endl;
        std::cout << "Actor/Movie Affected: " << report->getAffectedId() << std::endl;
        std::cout << std::endl;
    }
    // Error Handling for bad inputs
    catch (std::exception &e) {
        std::cout << "An error has occurred with exception: " << e.what() << " Please try again." << std::endl;
    }
}


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

// User Advanced Features
void User::displayAndSortMovies() {
    Application* application = Application::getInstance();
    std::cout << "=== Option 6: Display and Sort a list of all Movies ===" << std::endl;

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

    MyList<Movie*>* movies = application->getAllMovies();
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
                movie = application->getMovie(movieId);
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

void User::displayAndSortActors() {
    Application* application = Application::getInstance();
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

    MyList<Actor*>* actors = application->getAllActors();
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
                actor = application->getActor(actorId);
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

void User::findDistanceBetweenActors() {
    Application* application = Application::getInstance();
    std::cout << "=== Option 9 (Advanced): Find Distance Between Two Actors ===" << std::endl;

    Actor* actor1 = nullptr;
    Actor* actor2 = nullptr;
    int actor1Id, actor2Id;

    // Allow input and Validate that actor exists
    while (true) {
        std::cout << "\nActor 1 ID: ";
        if (std::cin >> actor1Id) {
            actor1 = application->getActor(actor1Id);
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
            actor2 = application->getActor(actor2Id);
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

        SortedList* movieIds = application->getActorMovies(currNode); // Retrieve all movies that the actor was part of
        for (int i = 0; i < movieIds->getLength(); i++) { // Iterate through all movieIds
            SortedList* actorIds = application->getMovieActors(movieIds->get(i)); // Get the actor who was part of a movie
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
