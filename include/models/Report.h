/*
* Created By: Ethan Chew (S10255990K), Darius Koh (S10255626K), Lim Yu Yang (S10255816J)
* Group: 4
*/

#pragma once
#include <iostream>

class Report {
private:
    std::string description;
    std::string type;
    int affectedId;
    std::string reporteeUsername;
    bool isResolved;
public:
    Report(std::string, std::string, int, std::string);

    // Getters
    std::string getDescription();
    std::string getType();
    int getAffectedId();
    std::string getReporteeUsername();
    bool getIsResolved();

    // Setters
    bool setIsResolved(bool);
};