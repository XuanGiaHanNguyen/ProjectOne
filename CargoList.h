#ifndef CARGOLIST_H
#define CARGOLIST_H

#include <iostream>
#include "Cargo.h"

// ── Singly linked node for cargo ──────────────────────────────────────────────
template <typename T>
struct CargoNode {
    Cargo<T>     data;
    CargoNode<T>* next;

    CargoNode(Cargo<T> data) : data(data), next(nullptr) {}
};

// ── CargoList — singly linked list nested inside each Train ───────────────────
// Represents the manifest (list of cargo items) for one specific train.
//
// Functions:
//   loadCargo()     — append a cargo item to the back (push back)
//   unloadCargo()   — remove a cargo item by name (walk and unlink)
//   displayManifest()— traverse forward and print all cargo
//   getTotalWeight()— sum all cargo weights via traversal
template <typename T>
class CargoList {
private:
    CargoNode<T>* head;
    CargoNode<T>* tail;
    int count;

public:
    CargoList() : head(nullptr), tail(nullptr), count(0) {}

    ~CargoList() {
        CargoNode<T>* cur = head;
        while (cur) {
            CargoNode<T>* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    // ── loadCargo — push to back ──────────────────────────────────────────────
    // Allocates a new CargoNode and links it after tail.
    void loadCargo(Cargo<T> cargo) {
        CargoNode<T>* newNode = new CargoNode<T>(cargo);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail       = newNode;
        }
        count++;
        std::cout << "  [Loaded]   \"" << cargo.name
                  << "\" (" << cargo.type << ", " << cargo.weight << " tons)\n";
    }

    // ── unloadCargo — remove by name ──────────────────────────────────────────
    // Uses a prev pointer to unlink the matching node from the singly linked list.
    void unloadCargo(T name) {
        CargoNode<T>* cur  = head;
        CargoNode<T>* prev = nullptr;

        while (cur != nullptr) {
            if (cur->data.name == name) {
                if (prev == nullptr) head = cur->next;  // removing head
                else                 prev->next = cur->next;
                if (cur->next == nullptr) tail = prev;  // removing tail

                std::cout << "  [Unloaded] \"" << name << "\"\n";
                delete cur;
                count--;
                return;
            }
            prev = cur;
            cur  = cur->next;
        }
        std::cout << "  [Error] Cargo \"" << name << "\" not found.\n";
    }

    // ── displayManifest — forward traversal ───────────────────────────────────
    void displayManifest() const {
        if (head == nullptr) {
            std::cout << "    (no cargo loaded)\n";
            return;
        }
        CargoNode<T>* cur = head;
        int i = 1;
        while (cur != nullptr) {
            std::cout << "    " << i++ << ". "
                      << cur->data.name
                      << " | Type: "   << cur->data.type
                      << " | Weight: " << cur->data.weight << " tons\n";
            cur = cur->next;
        }
    }

    // ── getTotalWeight — accumulate via traversal ─────────────────────────────
    int getTotalWeight() const {
        int total = 0;
        CargoNode<T>* cur = head;
        while (cur != nullptr) {
            total += cur->data.weight;
            cur = cur->next;
        }
        return total;
    }

    int getCount() const { return count; }
};

#endif
