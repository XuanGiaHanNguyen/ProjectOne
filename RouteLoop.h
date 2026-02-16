#ifndef ROUTELOOP_H
#define ROUTELOOP_H

#include <iostream>

// ── Circular linked node for a station ───────────────────────────────────────
template <typename T>
struct StationNode {
    T              name;  // e.g. "Central Depot"
    StationNode<T>* next; // always points to something (circular — never nullptr)

    StationNode(T name) : name(name), next(nullptr) {}
};

// ── RouteLoop — circular linked list of stations ──────────────────────────────
// The last node's next always points back to head, forming a loop.
// A "current" pointer tracks where the fleet is right now.
//
// Functions:
//   addStation()     — insert a new station at the end of the loop
//   removeStation()  — unlink a station by name, re-stitch the circle
//   advanceStation() — move current to current->next (loops automatically)
//   displayRoute()   — walk the full circle once and print every station
template <typename T>
class RouteLoop {
private:
    StationNode<T>* head;
    StationNode<T>* current;  // where the fleet is right now
    int size;

public:
    RouteLoop() : head(nullptr), current(nullptr), size(0) {}

    ~RouteLoop() {
        if (head == nullptr) return;
        // Break the circle before freeing
        StationNode<T>* cur = head;
        StationNode<T>* start = head;
        do {
            StationNode<T>* next = cur->next;
            delete cur;
            cur = next;
        } while (cur != start);
    }

    // ── addStation — insert at end, keep tail->next = head ───────────────────
    void addStation(T name) {
        StationNode<T>* newNode = new StationNode<T>(name);
        if (head == nullptr) {
            head          = newNode;
            newNode->next = head;    // points to itself — circle of one
            current       = head;
        } else {
            // Walk to the tail (node whose next == head)
            StationNode<T>* tail = head;
            while (tail->next != head) tail = tail->next;

            tail->next    = newNode;
            newNode->next = head;    // close the circle
        }
        size++;
        std::cout << "[Route] Station added: \"" << name << "\"\n";
    }

    // ── removeStation — unlink by name, re-stitch the circle ─────────────────
    void removeStation(T name) {
        if (head == nullptr) {
            std::cout << "[Route] Route is empty.\n";
            return;
        }
        StationNode<T>* cur  = head;
        StationNode<T>* prev = nullptr;

        // Walk the circle once looking for the name
        do {
            if (cur->name == name) {
                if (size == 1) {
                    // Only one station left — empty the route
                    delete cur;
                    head = current = nullptr;
                    size = 0;
                    std::cout << "[Route] Removed last station \"" << name << "\". Route is now empty.\n";
                    return;
                }

                // Find tail to fix the circle if we remove head
                StationNode<T>* tail = head;
                while (tail->next != head) tail = tail->next;

                if (cur == head) {
                    head       = head->next;
                    tail->next = head;           // tail still closes the loop
                } else {
                    prev->next = cur->next;
                }

                if (current == cur) current = cur->next; // move current away

                std::cout << "[Route] Removed station \"" << name << "\"\n";
                delete cur;
                size--;
                return;
            }
            prev = cur;
            cur  = cur->next;
        } while (cur != head);

        std::cout << "[Route] Station \"" << name << "\" not found.\n";
    }

    // ── advanceStation — move current forward (loops automatically) ───────────
    void advanceStation() {
        if (current == nullptr) {
            std::cout << "[Route] No stations on route.\n";
            return;
        }
        current = current->next;   // next is never nullptr in a circular list
        std::cout << "[Route] Fleet arrived at: \"" << current->name << "\"\n";
    }

    // ── displayRoute — walk the full circle once and print ───────────────────
    void displayRoute() {
        if (head == nullptr) {
            std::cout << "[Route] No stations defined.\n";
            return;
        }
        std::cout << "\n--- Route Loop (" << size << " stations) ---\n";
        StationNode<T>* cur = head;
        int i = 1;
        do {
            std::cout << "  " << i++ << ". " << cur->name;
            if (cur == current) std::cout << "  <-- fleet here";
            std::cout << "\n";
            cur = cur->next;
        } while (cur != head);
        std::cout << "  (loops back to \"" << head->name << "\")\n";
        std::cout << "-----------------------------\n";
    }

    int getSize() { return size; }
};

#endif
