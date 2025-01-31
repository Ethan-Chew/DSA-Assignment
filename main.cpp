#include <cassert>
#include <iostream>

#include "AdvancedFeatures.h"
#include "DataParser.h"
#include "AutoCompletionEngine.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "models/Account.h"
#include "models/Application.h"
#include "BasicFeatures.h"


void setupApplication(Application &application) {
    // Parse the Actors from the CSV into the Application
    auto t1 = std::chrono::high_resolution_clock::now();
    DataParser actorParser(
        "data/actors.csv",
        HeaderSpec("id", ColumnType::INT),
        HeaderSpec("name", ColumnType::STRING),
        HeaderSpec("birth", ColumnType::INT));

    // Retrieve the result
    auto actorResult = actorParser.ParseData();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "parsed actors in " << ms_int.count() << " ms" << std::endl;
    // Get each Column from CSV
    auto *ids = reinterpret_cast<MyList<int>*>((*actorResult)["id"]);
    auto *names = reinterpret_cast<MyList<std::string>*>((*actorResult)["name"]);
    auto *birth = reinterpret_cast<MyList<int>*>((*actorResult)["birth"]);

    // Create Actors and add to Dictionary
    for (int i = 0; i < ids->get_length(); i++) {
        int id = ids->get(i);
        std::string name = names->get(i);
        int birthYear = birth->get(i);

        std::unique_ptr<Actor> actor(new Actor(id, name, birthYear));
        application.addActor(std::move(actor));
    }

    // Parse the Movies from the CSV into the Application
    t1 = std::chrono::high_resolution_clock::now();
    DataParser movieParser(
        "data/movies.csv",
        HeaderSpec("id", ColumnType::INT),
        HeaderSpec("title", ColumnType::STRING),
        HeaderSpec("plot",ColumnType::STRING),
        HeaderSpec("year", ColumnType::INT));

    // Retrieve the result
    auto movieResult = movieParser.ParseData();
    t2 = std::chrono::high_resolution_clock::now();
    ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "parsed movies in " << ms_int.count() << " ms" << std::endl;

    // Get each Column from CSV
    auto *movieIds = reinterpret_cast<MyList<int>*>((*movieResult)["id"]);
    auto *titles = reinterpret_cast<MyList<std::string>*>((*movieResult)["title"]);
    auto *plots = reinterpret_cast<MyList<std::string>*>((*movieResult)["plot"]);
    auto *years = reinterpret_cast<MyList<int>*>((*movieResult)["year"]);

    // Create Movie Objects and add to Dictionary
    for (int i = 0; i < movieIds->get_length(); i++) {
        std::unique_ptr<Movie> movie = std::make_unique<Movie>(movieIds->get(i), titles->get(i), years->get(i), plots->get(i), Genre::NONE);
        application.addMovie(std::move(movie));
    }

    // Parse the Actors and Movies relationship from the CSV into the Application
    t1 = std::chrono::high_resolution_clock::now();
    DataParser castParser(
        "data/cast.csv",
        HeaderSpec("person_id", ColumnType::INT),
        HeaderSpec("movie_id", ColumnType::INT));

    // Retrieve the result
    auto castResult = castParser.ParseData();

    t2 = std::chrono::high_resolution_clock::now();
    ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "parsed cast  in " << ms_int.count() << " ms" << std::endl;

    // Get each Column from the CSV
    auto *castPersonIds = reinterpret_cast<MyList<int>*>((*castResult)["person_id"]);
    auto *castMovieIds = reinterpret_cast<MyList<int>*>((*castResult)["movie_id"]);

    // Create and update Actor-Movie Relationships
    for (int i = 0; i < castPersonIds->get_length(); i++) {
        application.addActorToMovie(castPersonIds->get(i), castMovieIds->get(i));
    }
}

// Login user to User/Admin Accounts
Account loginUser(Application &application) {
    std::cout << "Amazing Movie App" << "\n";
    std::cout << "-----------------" << "\n";

    // Login System
    while (true) {
        std::string username, password;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        // Check if login details are valid
        Account* account = application.getAccount(username);
        if (account == nullptr) {
            std::cout << "No account with username found." << "\n";
        } else {
            if (account->comparePassword(password)) {
                std::cout << "Welcome, " + username + "!" << "\n";
                return *account;
            }
            std::cout << "Incorrect Password." << "\n";
        }
    }
}

// Displays main menu and runs commands based on user input
bool displayMenu(Application &application, bool isAdmin) {
    int choice = -1;
    while (choice != 0) {
        // User Commands
        if (!isAdmin) {
            std::cout <<
                "Available User Functions\n"
                "1. Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user\n"
                "2. Display movies made within the past 3 years (in ascending order of year)\n"
                "3. Display all movies an actor starred in (in alphabetical order)\n"
                "4. Display all the actors in a particular movie (in alphabetical order)\n"
                "5. Display a list of all actors that a particular actor knows.\n"
                "6. Display, Sort, and Rate a list of all Movies\n"
                "7. Display, Sort, and Rate a list of all Actors\n"
                "8 (Adv). Find Distance Between Two Actors\n"
                "9. Test autocomplete"
                "0. Log Out\n"
                "Enter Choice: " << "\n";
            std::cin >> choice;

            switch (choice) {
                default: { break; }

                // Display actors in age range
                case 1: {
                    BasicFeatures::displayActors(application);
                    break;
                }

                // Display movies released in past 3 years
                case 2: {
                    BasicFeatures::displayMovies(application);
                    break;
                }

                // Display movies actor starred in
                case 3: {
                    BasicFeatures::displayActorMovies(application);
                    break;
                }

                // Display all actors cast in movie
                case 4: {
                    BasicFeatures::displayActorsInMovie(application);
                    break;
                }

                // Display all actors an actor knows
                case 5: {
                    BasicFeatures::displayKnownActors(application);
                    break;
                }

                // Display and Sort Movies
                case 6: {
                    AdvancedFeatures::displayAndSortMovies(application);
                    break;
                }

                // Display and Sort Actors
                case 7: {
                    AdvancedFeatures::displayAndSortActors(application);
                    break;
                }

                // Find Distance Between Two Actors
                case 8: {
                    AdvancedFeatures::findDistanceBetweenActors(application);
                    break;

                    case 9: {
                        AutoCompletionEngine AutoComplete = AutoCompletionEngine(application, MOVIE);
                        std::string prompt;
                        std::string response;

                        AutoComplete.GetInput(prompt);
                        // std::cout << "Enter Prompt: ";
                        // std::cin >> prompt;
                        // std::cout << ;
                    }
                }
            }
        }
        // Admin Commands
        else {
            std::cout <<
                "Available Admin Commands\n"
                "1. Add new actor\n"
                "2. Add new movie\n"
                "3. Add an actor to a movie\n"
                "4. Update actor/movie details.\n"
                "5. Display entire database\n"
                "0. Log Out\n"
                "Enter Choice: " << "\n";
            std::cin >> choice;

            switch (choice) {
                default: { break; }

                // Add new actor
                case 1: {
                    BasicFeatures::addNewActor(application);
                    break;
                }

                // Add new movie
                case 2: {
                    BasicFeatures::addNewMovie(application);
                    break;
                }

                // Add actor to movie
                case 3: {
                    BasicFeatures::addActorToMovie(application);
                    break;
                }

                // Update actor/movie details
                case 4: {
                    BasicFeatures::updateActorOrMovie(application);
                    break;
                }

                case 5: {
                    BasicFeatures::printAll(application);
                    break;
                }
            }
        }
    }

    // Exit app
    std::string exit;
    std::cout << "Exit App? (y/n)";
    std::cin >> exit;
    return (exit == "y");
}

int main()
{
    Application* application = Application::getInstance();
    setupApplication(*application);

    Account account;
    bool exitApplication = false;

    // Login and Main Menu Setup
    while (!exitApplication) {
        account = loginUser(*application);
        exitApplication = displayMenu(*application, account.isAdministrator()); // Allows user to quit app with input
    }

    return 0;
}