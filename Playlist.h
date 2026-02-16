#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Node.h"
#include "Song.h"
#include <iostream>
#include <string>

// Playlist class — doubly linked list of Song<T>
// head  = first song
// tail  = last song
// current = now-playing pointer (enables prev/next/loop)
template <typename T>
class Playlist {
private:
    Node<Song<T>>* head;
    Node<Song<T>>* tail;
    Node<Song<T>>* current;   // points to the song being "played"
    int size;
    bool loopEnabled;

public:
    // ── Constructor / Destructor ─────────────────────────────────────────────
    Playlist() : head(nullptr), tail(nullptr), current(nullptr),
                 size(0), loopEnabled(false) {}

    ~Playlist() {
        // Free every node
        Node<Song<T>>* cur = head;
        while (cur) {
            Node<Song<T>>* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    // ── addSong — append to end (push back) ──────────────────────────────────
    // Creates a new node and links it after tail.
    void addSong(Song<T> song) {
        Node<Song<T>>* newNode = new Node<Song<T>>(song);
        if (head == nullptr) {          // list is empty
            head = tail = newNode;
            current = head;             // auto-select first song
        } else {
            newNode->prev = tail;
            tail->next    = newNode;
            tail          = newNode;
        }
        size++;
        std::cout << "Added: \"" << song.title << "\" by " << song.artist << "\n";
    }

    // ── removeSong — remove by title ─────────────────────────────────────────
    // Walks list, unlinks matching node, fixes head/tail/current if needed.
    void removeSong(T title) {
        Node<Song<T>>* cur = head;
        while (cur != nullptr) {
            if (cur->data.title == title) {
                // Stitch neighbours together
                if (cur->prev) cur->prev->next = cur->next;
                else           head = cur->next;   // removed head

                if (cur->next) cur->next->prev = cur->prev;
                else           tail = cur->prev;   // removed tail

                // Move current pointer away before deleting
                if (current == cur)
                    current = cur->next ? cur->next : cur->prev;

                std::cout << "Removed: \"" << cur->data.title << "\"\n";
                delete cur;
                size--;
                return;
            }
            cur = cur->next;
        }
        std::cout << "Song \"" << title << "\" not found.\n";
    }

    // ── playCurrent — display the now-playing song ───────────────────────────
    void playCurrent() {
        if (current == nullptr) {
            std::cout << "Playlist is empty.\n";
            return;
        }
        std::cout << "Now playing: \"" << current->data.title
                  << "\" by " << current->data.artist
                  << " [" << current->data.duration / 60
                  << ":" << (current->data.duration % 60 < 10 ? "0" : "")
                  << current->data.duration % 60 << "]\n";
    }

    // ── nextSong — advance current forward ───────────────────────────────────
    // If at the tail and loop is ON, wraps back to head (circular behaviour).
    void nextSong() {
        if (current == nullptr) { std::cout << "Playlist is empty.\n"; return; }
        if (current->next != nullptr) {
            current = current->next;
        } else if (loopEnabled) {
            current = head;     // wrap around
            std::cout << "(Looping back to start)\n";
        } else {
            std::cout << "Already at the last song.\n";
            return;
        }
        playCurrent();
    }

    // ── prevSong — move current backward ─────────────────────────────────────
    // If at head and loop is ON, wraps to tail.
    void prevSong() {
        if (current == nullptr) { std::cout << "Playlist is empty.\n"; return; }
        if (current->prev != nullptr) {
            current = current->prev;
        } else if (loopEnabled) {
            current = tail;     // wrap around
            std::cout << "(Looping back to end)\n";
        } else {
            std::cout << "Already at the first song.\n";
            return;
        }
        playCurrent();
    }

    // ── toggleLoop — enable/disable circular playback ────────────────────────
    void toggleLoop() {
        loopEnabled = !loopEnabled;
        std::cout << "Loop " << (loopEnabled ? "ON" : "OFF") << "\n";
    }

    // ── displayPlaylist — traverse forward and print all songs ───────────────
    void displayPlaylist() {
        if (head == nullptr) { std::cout << "Playlist is empty.\n"; return; }
        std::cout << "\n--- Playlist (" << size << " songs) ---\n";
        Node<Song<T>>* cur = head;
        int i = 1;
        while (cur != nullptr) {
            std::cout << i++ << ". "
                      << cur->data.title << " - " << cur->data.artist;
            if (cur == current) std::cout << "  <-- now playing";
            std::cout << "\n";
            cur = cur->next;
        }
        std::cout << "--------------------------\n";
    }

    // ── displayReverse — traverse backward using prev pointers ───────────────
    void displayReverse() {
        if (tail == nullptr) { std::cout << "Playlist is empty.\n"; return; }
        std::cout << "\n--- Playlist (reversed) ---\n";
        Node<Song<T>>* cur = tail;
        int i = size;
        while (cur != nullptr) {
            std::cout << i-- << ". "
                      << cur->data.title << " - " << cur->data.artist << "\n";
            cur = cur->prev;
        }
        std::cout << "--------------------------\n";
    }

    // ── getSize ───────────────────────────────────────────────────────────────
    int getSize() { return size; }
};

#endif
