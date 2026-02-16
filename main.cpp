#include <iostream>
#include <string>
#include "Song.h"
#include "Playlist.h"

// ── Helper: print menu ────────────────────────────────────────────────────────
void printMenu() {
    std::cout << "\n=== SoundTrack Playlist Manager ===\n"
              << "1. Display playlist\n"
              << "2. Add song\n"
              << "3. Remove song\n"
              << "4. Play current song\n"
              << "5. Next song\n"
              << "6. Previous song\n"
              << "7. Toggle loop\n"
              << "8. Display playlist in reverse\n"
              << "0. Exit\n"
              << "Choice: ";
}

int main() {
    Playlist<std::string> playlist;

    // Pre-load a few songs so the list is not empty at start
    playlist.addSong(Song<std::string>("Blinding Lights", "The Weeknd",  200));
    playlist.addSong(Song<std::string>("As It Was",       "Harry Styles", 167));
    playlist.addSong(Song<std::string>("Heat Waves",      "Glass Animals",238));

    int choice;
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            playlist.displayPlaylist();

        } else if (choice == 2) {
            std::string title, artist;
            int mins, secs;
            std::cout << "Title: ";  std::getline(std::cin, title);
            std::cout << "Artist: "; std::getline(std::cin, artist);
            std::cout << "Duration (min sec): "; std::cin >> mins >> secs;
            std::cin.ignore();
            playlist.addSong(Song<std::string>(title, artist, mins * 60 + secs));

        } else if (choice == 3) {
            std::string title;
            std::cout << "Title to remove: "; std::getline(std::cin, title);
            playlist.removeSong(title);

        } else if (choice == 4) {
            playlist.playCurrent();

        } else if (choice == 5) {
            playlist.nextSong();

        } else if (choice == 6) {
            playlist.prevSong();

        } else if (choice == 7) {
            playlist.toggleLoop();

        } else if (choice == 8) {
            playlist.displayReverse();

        } else if (choice != 0) {
            std::cout << "Invalid option.\n";
        }

    } while (choice != 0);

    std::cout << "Goodbye!\n";
    return 0;
}
