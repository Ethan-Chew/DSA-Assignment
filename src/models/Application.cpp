//
// Created by ethan on 15/1/2025.
//

#include "models/Application.h"

Application::Application() {
    uniqueInstance = nullptr;
}

Application& Application::getInstance() {
    if (uniqueInstance == nullptr) {
        uniqueInstance = new Application();
    }
    return *uniqueInstance;
}


