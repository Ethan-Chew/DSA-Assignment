//
// Created by ethan on 5/2/2025.
//

#pragma once
#include <iostream>

class Report {
private:
    std::string description;
    std::string type;
    int affectedId;
    int reporteeId;
    bool isResolved;
public:
    Report(std::string, std::string, int, int);

    // Getters
    std::string getDescription();
    std::string getType();
    int getAffectedId();
    int getReporteeId();
    bool getIsResolved();

    // Setters
    bool setIsResolved(bool);
};