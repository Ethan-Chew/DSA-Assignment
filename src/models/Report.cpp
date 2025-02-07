//
// Created by ethan on 7/2/2025.
//

#include "models/Report.h"

Report::Report(std::string desc, std::string type, int affectedId, std::string reporteeUsername) {
    description = desc;
    this->type = type;
    this->affectedId = affectedId;
    this->reporteeUsername = reporteeUsername;
    isResolved = false;
}

std::string Report::getDescription() {
    return description;
}

std::string Report::getType() {
    return type;
}

int Report::getAffectedId() {
    return affectedId;
}

std::string Report::getReporteeUsername() {
    return reporteeUsername;
}

bool Report::getIsResolved() {
    return isResolved;
}


bool Report::setIsResolved(bool isResolved) {
    this->isResolved = isResolved;
    return isResolved;
}
