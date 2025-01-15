#include <iostream>
#include "DataParser.h"
#include "models/Actor.h"
#include "models/Movie.h"
#include "models/Application.h"

void parseActors(MyDict<int, Actor> &actors) {
    DataParser parser(
        "./data/actors.csv",
        HeaderSpec("id", ColumnType::INT),
        HeaderSpec("name", ColumnType::STRING),
        HeaderSpec("birth", ColumnType::INT));

    auto result = parser.ParseData();

    auto *ids = reinterpret_cast<MyList<int>*>((*result)["id"]);
    auto *names = reinterpret_cast<MyList<std::string>*>((*result)["name"]);
    auto *birth = reinterpret_cast<MyList<int>*>((*result)["birth"]);

    for (int i = 0; i < ids->get_length(); i++) {
        actors.add(ids->get(i), Actor(ids->get(i), names->get(i), birth->get(i)));
    }
}

void parseMovies(MyDict<int, Movie> &movies) {
    DataParser parser(
        "./data/movies.csv",
        HeaderSpec("id", ColumnType::INT),
        HeaderSpec("title", ColumnType::STRING),
        HeaderSpec("year", ColumnType::INT));

    auto result = parser.ParseData();

    auto *ids = reinterpret_cast<MyList<int>*>((*result)["id"]);
    auto *titles = reinterpret_cast<MyList<std::string>*>((*result)["title"]);
    auto *years = reinterpret_cast<MyList<int>*>((*result)["year"]);

    for (int i = 0; i < ids->get_length(); i++) {
        movies.add(ids->get(i), Movie(ids->get(i), titles->get(i), years->get(i), "", Genre::NONE));
    }
}

void setupApplication(Application &application) {
    // Parse the Actors from the CSV into the Application
    MyDict<int, Actor> actors;
    parseActors(actors);
    application.setActors(std::move(actors));

    // Parse the Movies from the CSVV into the Application
    MyDict<int, Movie> movies;
    parseMovies(movies);
    application.setMovies(std::move(movies));
}

int main()
{
    Application* application = Application::getInstance();
    setupApplication(*application);

    return 0;
}