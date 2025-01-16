#include <iostream>
#include "DataParser.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "models/Application.h"

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

int main()
{
    Application* application = Application::getInstance();
    setupApplication(*application);

    return 0;
}