#include <iostream>
#include <string>
#include <limits>
#include "TrainFleet.h"
#include "RouteLoop.h"

void printMenu() {
    std::cout << "\n====== Train Cargo Management ======\n"
              << "-- Fleet (Singly Linked List) --\n"
              << " 1. Display full fleet\n"
              << " 2. Add train to fleet\n"
              << " 3. Remove train from fleet\n"
              << "-- Cargo (Nested Singly Linked List) --\n"
              << " 4. Load cargo onto train\n"
              << " 5. Unload cargo from train\n"
              << " 6. Display one train's manifest\n"
              << "-- Route (Circular Linked List) --\n"
              << " 7. Display route loop\n"
              << " 8. Add station to route\n"
              << " 9. Remove station from route\n"
              << "10. Advance fleet to next station\n"
              << " 0. Exit\n"
              << "====================================\n"
              << "Choice: ";
}

// Read a full line, helper to avoid cin >> mixing issues
std::string readLine(const std::string& prompt) {
    std::string val;
    std::cout << prompt;
    std::getline(std::cin, val);
    return val;
}

int readInt(const std::string& prompt) {
    int val;
    std::cout << prompt;
    std::cin >> val;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

int main() {
    TrainFleet<std::string> fleet;
    RouteLoop<std::string>  route;

    // ── Pre-load sample data ──────────────────────────────────────────────────
    // Fleet — singly linked list of trains
    fleet.addTrain("T-01", "Iron Horse",   500);
    fleet.addTrain("T-02", "Steel Falcon", 300);
    fleet.addTrain("T-03", "Coal Runner",  800);

    // Cargo — nested singly linked list inside each train
    fleet.loadCargo("T-01", Cargo<std::string>("Steel Beams",   "Industrial", 120));
    fleet.loadCargo("T-01", Cargo<std::string>("Lumber",        "Raw Material", 80));
    fleet.loadCargo("T-02", Cargo<std::string>("Electronics",   "Fragile",    50));
    fleet.loadCargo("T-03", Cargo<std::string>("Coal",          "Bulk",       400));
    fleet.loadCargo("T-03", Cargo<std::string>("Grain Sacks",   "Food",       200));

    // Route — circular linked list of stations
    route.addStation("Central Depot");
    route.addStation("Northgate Yard");
    route.addStation("Eastport Terminal");
    route.addStation("Southfield Hub");

    std::cout << "\nSample data loaded. Fleet and route ready.\n";

    // ── Menu loop ─────────────────────────────────────────────────────────────
    int choice;
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            fleet.displayFleet();

        } else if (choice == 2) {
            std::string id   = readLine("Train ID   : ");
            std::string name = readLine("Train name : ");
            int maxW         = readInt ("Max weight (tons): ");
            fleet.addTrain(id, name, maxW);

        } else if (choice == 3) {
            std::string id = readLine("Train ID to remove: ");
            fleet.removeTrain(id);

        } else if (choice == 4) {
            std::string trainId = readLine("Train ID    : ");
            std::string cname   = readLine("Cargo name  : ");
            std::string ctype   = readLine("Cargo type  : ");
            int weight          = readInt ("Weight (tons): ");
            fleet.loadCargo(trainId, Cargo<std::string>(cname, ctype, weight));

        } else if (choice == 5) {
            std::string trainId = readLine("Train ID    : ");
            std::string cname   = readLine("Cargo name  : ");
            fleet.unloadCargo(trainId, cname);

        } else if (choice == 6) {
            std::string id = readLine("Train ID: ");
            fleet.displayTrain(id);

        } else if (choice == 7) {
            route.displayRoute();

        } else if (choice == 8) {
            std::string name = readLine("Station name: ");
            route.addStation(name);

        } else if (choice == 9) {
            std::string name = readLine("Station name to remove: ");
            route.removeStation(name);

        } else if (choice == 10) {
            route.advanceStation();

        } else if (choice != 0) {
            std::cout << "Invalid option.\n";
        }

    } while (choice != 0);

    std::cout << "Goodbye!\n";
    return 0;
}
