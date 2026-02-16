#ifndef TRAINFLEET_H
#define TRAINFLEET_H

#include <iostream>
#include "CargoList.h"

// ── Train node — one train in the fleet, contains its own CargoList ───────────
template <typename T>
struct TrainNode {
    T            id;       // e.g. "T-01"
    T            name;     // e.g. "Iron Horse"
    int          maxWeight;// max cargo weight in tons
    CargoList<T> cargo;    // nested singly linked list of cargo items
    TrainNode<T>* next;

    TrainNode(T id, T name, int maxWeight)
        : id(id), name(name), maxWeight(maxWeight), next(nullptr) {}
};

// ── TrainFleet — singly linked list of trains ─────────────────────────────────
// Each node IS a train and also OWNS a CargoList (nested linked list).
//
// Functions:
//   addTrain()      — push a new train to the back of the fleet
//   removeTrain()   — unlink and delete a train by ID (also frees its cargo)
//   loadCargo()     — find a train by ID, call its CargoList::loadCargo()
//   unloadCargo()   — find a train by ID, call its CargoList::unloadCargo()
//   displayFleet()  — traverse fleet, print each train + its manifest
//   displayTrain()  — print one train's details and full cargo manifest
template <typename T>
class TrainFleet {
private:
    TrainNode<T>* head;
    int size;

    // Internal helper — find a train node by ID
    TrainNode<T>* findTrain(T id) {
        TrainNode<T>* cur = head;
        while (cur != nullptr) {
            if (cur->id == id) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

public:
    TrainFleet() : head(nullptr), size(0) {}

    ~TrainFleet() {
        TrainNode<T>* cur = head;
        while (cur) {
            TrainNode<T>* next = cur->next;
            delete cur;             // CargoList destructor runs automatically
            cur = next;
        }
    }

    // ── addTrain — push new train to back ────────────────────────────────────
    void addTrain(T id, T name, int maxWeight) {
        TrainNode<T>* newNode = new TrainNode<T>(id, name, maxWeight);
        if (head == nullptr) {
            head = newNode;
        } else {
            TrainNode<T>* cur = head;
            while (cur->next != nullptr) cur = cur->next;  // walk to tail
            cur->next = newNode;
        }
        size++;
        std::cout << "[Fleet] Train added: [" << id << "] "
                  << name << " (max " << maxWeight << " tons)\n";
    }

    // ── removeTrain — unlink by ID ────────────────────────────────────────────
    void removeTrain(T id) {
        TrainNode<T>* cur  = head;
        TrainNode<T>* prev = nullptr;

        while (cur != nullptr) {
            if (cur->id == id) {
                if (prev == nullptr) head = cur->next;
                else                 prev->next = cur->next;

                std::cout << "[Fleet] Train removed: [" << id << "] " << cur->name << "\n";
                delete cur;   // also frees nested CargoList
                size--;
                return;
            }
            prev = cur;
            cur  = cur->next;
        }
        std::cout << "[Fleet] Train ID \"" << id << "\" not found.\n";
    }

    // ── loadCargo — find train, delegate to its CargoList ────────────────────
    void loadCargo(T trainId, Cargo<T> cargo) {
        TrainNode<T>* train = findTrain(trainId);
        if (train == nullptr) {
            std::cout << "[Fleet] Train \"" << trainId << "\" not found.\n";
            return;
        }
        int newTotal = train->cargo.getTotalWeight() + cargo.weight;
        if (newTotal > train->maxWeight) {
            std::cout << "  [Overweight] Cannot load \"" << cargo.name
                      << "\". Would exceed max weight ("
                      << newTotal << "/" << train->maxWeight << " tons).\n";
            return;
        }
        std::cout << "[Train " << trainId << "] Loading cargo:\n";
        train->cargo.loadCargo(cargo);
    }

    // ── unloadCargo — find train, delegate to its CargoList ──────────────────
    void unloadCargo(T trainId, T cargoName) {
        TrainNode<T>* train = findTrain(trainId);
        if (train == nullptr) {
            std::cout << "[Fleet] Train \"" << trainId << "\" not found.\n";
            return;
        }
        std::cout << "[Train " << trainId << "] Unloading cargo:\n";
        train->cargo.unloadCargo(cargoName);
    }

    // ── displayTrain — show one train + its full manifest ────────────────────
    void displayTrain(T id) {
        TrainNode<T>* train = findTrain(id);
        if (train == nullptr) {
            std::cout << "[Fleet] Train \"" << id << "\" not found.\n";
            return;
        }
        std::cout << "\n  Train : [" << train->id << "] " << train->name << "\n"
                  << "  Weight: " << train->cargo.getTotalWeight()
                  << "/" << train->maxWeight << " tons"
                  << " | Cargo items: " << train->cargo.getCount() << "\n"
                  << "  Manifest:\n";
        train->cargo.displayManifest();
    }

    // ── displayFleet — traverse all trains, print each with manifest ──────────
    void displayFleet() {
        if (head == nullptr) {
            std::cout << "[Fleet] No trains in fleet.\n";
            return;
        }
        std::cout << "\n======= TRAIN FLEET (" << size << " trains) =======\n";
        TrainNode<T>* cur = head;
        int i = 1;
        while (cur != nullptr) {
            std::cout << "\n  #" << i++ << " [" << cur->id << "] " << cur->name
                      << " | " << cur->cargo.getTotalWeight()
                      << "/" << cur->maxWeight << " tons"
                      << " | " << cur->cargo.getCount() << " cargo items\n"
                      << "  Manifest:\n";
            cur->cargo.displayManifest();
            cur = cur->next;
        }
        std::cout << "=====================================\n";
    }

    int getSize() { return size; }
};

#endif
