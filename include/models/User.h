/*
* Created By: Ethan Chew (S10255990K), Darius Koh (S10255626K), Lim Yu Yang (S10255816J)
* Group: 4
*/

#include "Account.h"

class User: public Account {
public:
    User(std::string, std::string);
    bool isUserAdmin() const override;

    // User Basic Features

    /*
     * Display Actors between two ages inclusive
     *
     * Input: x, y (starting and ending age of Actors)
     * Output: Actors printed in ascending order of age within the range
     */
    void displayActors();

    /*
     * Display movies made within the past 3 years (in ascending order of year)
     *
     * Input: None
     * Output: All Movies made in the past 3 years, sorted in ascending order
     */
    void displayMovies();

    /*
     * Displays the Movies that a particular actor starred in
     *
     * Input: Either the Actor's Name or ID
     * Output: All movies that an actor has acted in, sorted alphabetically
     */
    void displayActorMovies();

    /*
     * Display all the Actors in a particular movie
     *
     * Input: Either the Movie's Title or ID
     * Output: All actors starred in the movie, sroted alphabetically
     */
    void displayActorsInMovie();

    /*
     * Display a List of Actors that a Particular Actor knows
     * Created using BFS
     *
     * Input: Either the Actor's Name or ID
     * Output: All Actors that the inputted Actor knows (splitted into Level One and Two Connections)
     */
    void displayKnownActors();

     /*
     * Allows users to file a report by specifying the Report's description, type and affected item (Actor/Movie)
     *
     * Input: Report Details (Type, Description, ID of Affected Movie/Actor)
     * Output: Filed Report
     */
    void fileReport();

    // User Features (Advanced)

   /*
    * Allows users to Display and Sort all movies by: Alphabetical, Release Year, Rating
    *
    * Input: Sorting Option
    * Output: Sorted List of Movies
    *
    * Secondary Input: Movie Rating (from 1 to 5)
    */
    void displayAndSortMovies();

    /*
     * Allows users to Display and Sort all actors by: Alphabetical, Age, Rating
     *
     * Input: Sorting Option
     * Output: Sorted List of Actors
     *
     * Secondary Input: Actor Rating (from 1 to 5)
     */
    void displayAndSortActors();

    /*
     * Finding the 'Path' between how 2 Actors can possibly know each other
     * Path Finding using BFS
     *
     * Input: Either the Name or ID of 2 Different Actors
     * Output: Distance between both Actors and Path between both actors
     */
    void findDistanceBetweenActors();
};