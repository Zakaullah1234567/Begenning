# Music Playlist Using Circular Doubly Linked List (C++)

## Overview
This project is a **console-based Music Playlist Management System** implemented in **C++** using a **Circular Doubly Linked List (CDLL)** data structure.

It allows users to manage a playlist of songs just like a real music player, where:
- Songs can be added or deleted dynamically
- You can move **forward and backward** through the playlist
- When you reach the **last song and press next**, the playlist automatically loops back to the **first song**
- When you are at the **first song and press previous**, it moves to the **last song**

This circular behavior makes the playlist continuous and user-friendly.

---

## Data Structure Used

### Circular Doubly Linked List
Each song is stored as a **node** containing:
- Song title
- Pointer to the **next** song
- Pointer to the **previous** song

Because the list is **circular**:
- `tail->next` points to `head`
- `head->prev` points to `tail`

This enables seamless looping through the playlist.

---

## Features

- Add a song to the playlist
- Delete a song by title
- Search for a song
- Display playlist (forward)
- Display playlist (backward)
- Play next song (loops to first song automatically)
- Play previous song (loops to last song automatically)
- Show currently playing song

---

## Project Structure
```
Playlist.cpp   // Main C++ source file
README.md      // Project documentation
```

---

## How It Works

- Songs are stored dynamically using a **Circular Doubly Linked List**
- A `current` pointer keeps track of the currently playing song
- Navigation is done using `next` and `prev` pointers
- The program runs in a menu-driven loop until the user exits

---

## How to Run

1. Open a terminal or command prompt
2. Compile the program:
```bash
g++ Playlist.cpp -o Playlist
```
3. Run the executable:
```bash
./Playlist
```

---

## Sample Menu
```
==== MUSIC PLAYLIST MENU ====
1. Add Song
2. Delete Song
3. Search Song
4. Display Playlist (Forward)
5. Display Playlist (Backward)
6. Play Next Song
7. Play Previous Song
8. Show Current Song
9. Exit
```

---

## Learning Outcomes

- Understanding **Circular Doubly Linked Lists**
- Dynamic memory allocation using pointers
- Real-world application of linked lists
- Menu-driven programming in C++

---

## Future Improvements

- Shuffle mode
- Save playlist to a file
- Load playlist from a file
- Song duration tracking
- GUI-based version

---

## Author

**Zaka Ullah**  
Student of Computer Science  
Focused on C++ and Data Structures

---