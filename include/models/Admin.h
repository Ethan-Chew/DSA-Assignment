/*
* Created By: Ethan Chew (S10255990K), Darius Koh (S10255626K), Lim Yu Yang (S10255816J)
* Group: 4
*/

#include "Account.h"

class Admin: public Account {
public:
    Admin(std::string, std::string);
    bool isUserAdmin() const override;

    // Admin Features (Basic)

    /*
     * Add a New Actor
     *
     * Input: Various fields (Name and Birth Year) to create a new actor object
     * Output: Created Actor
     */
    void addNewActor();

    /*
     * Adds a New Movie
     *
     * Input: Various fields (Release Year, Plot and Genre) to create a new movie object
     * Output: Created Movie
     * */
    void addNewMovie();

    /*
     * Adds existing Actor to an existing Movie
     *
     * Input: Either the Name/Title or ID of an Actor/Movie
     * Output: None, Confirmation that Relationship has been created
     * */
    void addActorToMovie();

     /*
     * Updates either the details of the Actor or the Movie
     *
     * Input: Choice between Updating an Actor vs Movie; Then, respective details of Actor/Movie
     * Output: Updated Actor/Movie
     * */
    void updateActorOrMovie();

    /*
     * Allows Admins to review all Report made by Users and take appropriate action
     *
     * Input: Check if the Admin wants to act on any report; If yes, the Report ID, and required Information
     * Output: Updated Actor/Movie
     */
    void reviewReports();
};
