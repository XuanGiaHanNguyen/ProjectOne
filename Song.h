#ifndef SONG_H
#define SONG_H

#include <string>

// Simple data struct representing one song
template <typename T>
struct Song {
    T title;
    T artist;
    int duration; // in seconds

    Song() : title(""), artist(""), duration(0) {}
    Song(T title, T artist, int duration)
        : title(title), artist(artist), duration(duration) {}
};

#endif
