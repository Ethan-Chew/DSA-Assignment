//
// Created by ethan on 7/2/2025.
//

#include "models/Report.h"

Report::Report(std::string desc, std::string type, int affectedId, int reporteeId) {
    description = desc;
    this->type = type;
    this->affectedId = affectedId;
    this->reporteeId = reporteeId;
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

int Report::getReporteeId() {
    return reporteeId;
}

bool Report::setIsResolved(bool isResolved) {
    this->isResolved = isResolved;
    return isResolved;
}
