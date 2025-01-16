#include <iostream>
#include "DataParser.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "models/Application.h"
using namespace std;

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
}

void displayMenu() {
    int userRole;
    int choice;

    while (true) {
        cout <<
            "--- Enter Role ---\n"
            "1. Admin\n"
            "2. User\n"
            "Enter Choice: " << endl;
        cin >> userRole;

        choice = 100;
        if (userRole == 1) {
            while (choice != 0) {
                cout <<
                    "1. Add new actor\n"
                    "2. Add new movie\n"
                    "3. Add an actor to a movie\n"
                    "4. Update actor/movie details.\n"
                    "0. Reselect user role\n"
                    "Enter Choice: " << endl;
                cin >> choice;

                switch (choice) {
                    default: { break; }

                    case 1: { break; }

                    case 2: { break; }

                    case 3: { break; }

                    case 4: { break; }

                    case 0: break;
                }
            }

        }
        if (userRole == 2) {
            while (choice != 0) {
                cout <<
                    "1. Display (in ascending order of age) the actors with age between x and y (inclusive) where x and y are integer values to be entered by the user\n"
                    "2. Display movies made within the past 3 years (in ascending order of year)\n"
                    "3. Display all movies an actor starred in (in alphabetical order)\n"
                    "4. Display all the actors in a particular movie (in alphabetical order)\n"
                    "5. Display a list of all actors that a particular actor knows.\n"
                    "0. Reselect user role\n"
                    "Enter Choice: " << endl;
                cin >> choice;

                switch (choice) {
                    default: { break; }

                    case 1: { break; }

                    case 2: { break; }

                    case 3: { break; }

                    case 4: { break; }

                    case 5: { break; }

                    case 0: break;
                }
            }
        }
    }
}

int main()
{
    Application* application = Application::getInstance();
    setupApplication(*application);

    // Setup Main Menu
    displayMenu();


    return 0;
}