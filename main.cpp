#include <iostream>
#include "DataParser.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "models/Account.h"
#include "models/Application.h"
#include "BasicFeatures.h"

void setupApplication(Application &application) {
    // Parse the Actors from the CSV into the Application
    DataParser actorParser(
        "./data/actors.csv",
        HeaderSpec("id", ColumnType::INT),
        HeaderSpec("name", ColumnType::STRING),
        HeaderSpec("birth", ColumnType::INT));

    auto actorResult = actorParser.ParseData();

    auto *ids = reinterpret_cast<MyList<int>*>((*actorResult)["id"]);
    auto *names = reinterpret_cast<MyList<std::string>*>((*actorResult)["name"]);
    auto *birth = reinterpret_cast<MyList<int>*>((*actorResult)["birth"]);

    for (int i = 0; i < ids->get_length(); i++) {
        Actor actor = Actor(ids->get(i), names->get(i), birth->get(i));
        application.addActor(actor);
    }

    // Parse the Movies from the CSV into the Application
    DataParser movieParser(
        "./data/movies.csv",
        HeaderSpec("id", ColumnType::INT),
        HeaderSpec("title", ColumnType::STRING),
        HeaderSpec("year", ColumnType::INT));

    auto movieResult = movieParser.ParseData();

    auto *movieIds = reinterpret_cast<MyList<int>*>((*movieResult)["id"]);
    auto *titles = reinterpret_cast<MyList<std::string>*>((*movieResult)["title"]);
    auto *years = reinterpret_cast<MyList<int>*>((*movieResult)["year"]);

    for (int i = 0; i < movieIds->get_length(); i++) {
        Movie movie = Movie(movieIds->get(i), titles->get(i), years->get(i), "", Genre::NONE);
        application.addMovie(movie);
    }

    // Parse the Actors and Movies relationship from the CSV into the Application
    DataParser castParser(
        "./data/cast.csv",
        HeaderSpec("person_id", ColumnType::INT),
        HeaderSpec("movie_id", ColumnType::INT));

    /// Retrieve the result
    auto castResult = castParser.ParseData();

    /// Get each Column from the CSV
    auto *castPersonIds = reinterpret_cast<MyList<int>*>((*castResult)["person_id"]);
    auto *castMovieIds = reinterpret_cast<MyList<int>*>((*castResult)["movie_id"]);

    for (int i = 0; i < castPersonIds->get_length(); i++) {
        application.addActorToMovie(castPersonIds->get(i), castMovieIds->get(i));
    }
}

Account loginUser(Application &application) {
    std::cout << "Amazing Movie App" << "\n";
    std::cout << "-----------------" << "\n";

    while (true) {
        std::string username = "", password = "";
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        Account* account = application.getAccount(username);
        if (account == nullptr) {
            std::cout << "No account with username found." << "\n";
        } else {
            if (account->comparePassword(password)) {
                std::cout << "Welcome, " + username + "!" << "\n";
                return *account;
            } else {
                std::cout << "Incorrect Password." << "\n";
            }
        }
    }
}

void displayMenu(Application &application, bool isAdmin) {
    int choice = -1;
    while (choice != 0) {
        if (!isAdmin) {
            std::cout <<
                "Available User Functions\n"
                "1. Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user\n"
                "2. Display movies made within the past 3 years (in ascending order of year)\n"
                "3. Display all movies an actor starred in (in alphabetical order)\n"
                "4. Display all the actors in a particular movie (in alphabetical order)\n"
                "5. Display a list of all actors that a particular actor knows.\n"
                "0. Exit App\n"
                "Enter Choice: " << "\n";
            std::cin >> choice;

            switch (choice) {
                default: { break; }

                case 1: { break; }

                case 2: { break; }

                case 3: { break; }

                case 4: {
                    BasicFeatures::displayActorsInMovie(application, 109830);
                    break;
                }

                case 5: { break; }
            }
        } else {
            std::cout <<
                "Available Admin Commands\n"
                "1. Add new actor\n"
                "2. Add new movie\n"
                "3. Add an actor to a movie\n"
                "4. Update actor/movie details.\n"
                "0. Exit App\n"
                "Enter Choice: " << "\n";
            std::cin >> choice;

            switch (choice) {
                default: { break; }

                case 1: {
                    BasicFeatures::addNewActor(application);
                    break;
                }

                case 2: {
                    BasicFeatures::addNewMovie(application);
                    break;
                }

                case 3: {
                    BasicFeatures::addActorToMovie(application);
                    break;
                }

                case 4: {
                    BasicFeatures::updateActorOrMovie(application);
                    break;
                }
            }
        }
    }
}

int main()
{
    Application* application = Application::getInstance();
    setupApplication(*application);

    // Login and Main Menu Setup
    Account account = loginUser(*application);
    displayMenu(*application, account.isAdministrator());


    return 0;
}