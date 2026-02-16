# 🚂 Train Cargo Management – Linked List Implementation

**Course:** COP4530 – Data Structures  
**Semester:** Spring 2026  
**Project:** Project 1 – Linked List Implementation

| Member | Name | Student ID |
|--------|------|------------|
| Member 1 | Xuan Gia Han Nguyen | U78330128 |
| Member 2 | Quang Hien Tran | U |

---

## Overview

A command-line Train Cargo Management system built on two custom linked list implementations:

- **Singly Linked List** — manages the train fleet, where each train node also owns a nested singly linked list of its cargo items
- **Circular Linked List** — manages the station route loop the fleet cycles through

---

## How to Run

Compile and launch the program using the following commands:

```bash
g++ -std=c++17 -Wall -Wextra -o train_cargo main.cpp
./train_cargo
```
The program will pre-load sample trains, cargo, and stations so you can interact with it immediately.

---

## Menu Options

### Fleet Management (Singly Linked List)

| # | Option | Description |
|---|--------|-------------|
| 1 | Display full fleet | Shows all trains and their full cargo manifests |
| 2 | Add train to fleet | Appends a new train to the end of the fleet list |
| 3 | Remove train from fleet | Finds and removes a train by ID, also frees its cargo |

### Cargo Management (Nested Singly Linked List)

| # | Option | Description |
|---|--------|-------------|
| 4 | Load cargo onto train | Finds a train by ID and appends cargo to its manifest |
| 5 | Unload cargo from train | Finds a train by ID and removes a cargo item by name |
| 6 | Display one train's manifest | Shows a single train's details and cargo list |

### Route Management (Circular Linked List)

| # | Option | Description |
|---|--------|-------------|
| 7 | Display route loop | Traverses the full circular station loop and prints every stop |
| 8 | Add station to route | Inserts a new station at the end of the circular route |
| 9 | Remove station from route | Unlinks a station by name and re-stitches the circle |
| 10 | Advance fleet to next station | Moves the current pointer forward, wraps automatically |
| 0 | Exit | Ends the program |

### Adding a Train
When selecting **Add train**, you will be prompted to enter:
- Train ID (e.g. `T-04`)
- Train name (e.g. `Night Freight`)
- Max weight capacity in tons

### Loading Cargo
When selecting **Load cargo**, you will be prompted to enter:
- Train ID
- Cargo name
- Cargo type
- Weight in tons
---

## Team Contributions

| Team Member | Contribution | 
|-------------|-------------|
| Xuan Gia Han Nguyen | 50% | 
| Quang Hien Tran | 50% |
