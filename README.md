# Spotify Clone – Linked List Implementation

**Course:** COP4530 – Data Structures  
**Semester:** Spring 2026  
**Project:** Project 1 – Linked List Implementation

| Member | Name | Student ID |
|--------|------|------------|
| Member 1 | Xuan Gia Han Nguyen | U78330128 |
| Member 2 | Quang Hien Tran | U |

---

## Overview

A command-line Spotify-inspired playlist manager built on a custom **doubly linked list** implementation. Users can create a named playlist, manage songs, and control playback through a numbered menu interface.

---

## How to Run

Compile and launch the program using the following commands:
```bash
g++ -std=c++17 -Wall -Wextra -o main main.cpp
./main
```

When prompted, enter a name for your playlist. You will then see a numbered menu — type a number and press Enter to execute any action.

---

## Menu Options

### Playlist & Song Management

| # | Option | Description |
|---|--------|-------------|
| 1 | View playlist | Display all songs in a formatted table with title, artist, and duration |
| 2 | Add song (to end) | Adds a new song to the end of the playlist (`pushBack`) |
| 3 | Remove song by title | Searches for and removes the first song matching the given title |
| 8 | Display playlist in reverse | Displays the playlist in reversed order |

### Playback Controls

| # | Option | Description |
|---|--------|-------------|
| 4 | Play / Resume | Starts or resumes playback at the current song |
| 4 | Pause | Pauses the currently playing song |
| 5 | Next song | Advances to the next song (wraps to beginning in Repeat All mode) |
| 6 | Previous song | Goes back to the previous song (wraps to end in Repeat All mode) |
| 7 | Toggle Loop | Enables/disables circular playback |
| 0 | Exit | Exits the playlist and ends the program |

### Adding a Song

When selecting **Add song**, you will be prompted to enter:
- Song title
- Artist name
- Duration (minutes and seconds entered separately)

---

## Team Contributions

| Team Member | Contribution |
|-------------|-------------|
| Xuan Gia Han Nguyen | 50% — `DoublyLinkedList.h`, Song class, testing |
| Quang Hien Tran | 50% — `Playlist.h`, `main.cpp`, documentation |

