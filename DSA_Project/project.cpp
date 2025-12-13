#include <iostream>
#include <string>
using namespace std;

class Song {
public:
    string title;
    Song* next;
    Song* prev;

    Song(string t) {
        title = t;
        next = NULL;
        prev = NULL;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist() {
        head = NULL;
        tail = NULL;
        current = NULL;
    }

    void addSong(string title) {
        Song* newSong = new Song(title);

        if (head == NULL) {
            head = tail = newSong;
            current = head;
            head->next = head;
            head->prev = head;
            cout << "First song added: " << title << endl;
            return;
        }

        tail->next = newSong;
        newSong->prev = tail;
        newSong->next = head;
        head->prev = newSong;
        tail = newSong;

        cout << "Song added: " << title << endl;
    }


    void deleteSong(string title) {
        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = head;
        bool found = false;
        do {
            if (temp->title == title) {
                found = true;
                break;
            }
            temp = temp->next;
        } while (temp != head);

        if (!found) {
            cout << "Song not found.\n";
            return;
        }

        if (temp == head && temp == tail) { 
            head = tail = current = NULL;
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            if (temp == tail) tail = temp->prev;
            if (current == temp) current = temp->next;
        }

        delete temp;
        cout << "Song deleted successfully.\n";
    }


    void searchSong(string title) {
        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = head;
        while (temp != NULL) {
            if (temp->title == title) {
                cout << "Song found: " << title << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Song not found.\n";
    }

    void displayForward() {
        if (head == NULL) { cout << "Playlist is empty.\n"; return; }
        cout << "\n--- Playlist (Forward) ---\n";
        Song* temp = head;
        do {
            cout << temp->title << endl;
            temp = temp->next;
        } while (temp != head);
    }

    void displayBackward() {
        if (tail == NULL) { cout << "Playlist is empty.\n"; return; }
        cout << "\n--- Playlist (Backward) ---\n";
        Song* temp = tail;
        do {
            cout << temp->title << endl;
            temp = temp->prev;
        } while (temp != tail);
    }


    void playNext() {
        if (current == NULL) {
            cout << "No songs in playlist.\n";
            return;
        }

        current = current->next;
        if (current == head)
            cout << "You are now on the first song: " << current->title << endl;
        else
            cout << "Now playing: " << current->title << endl;
    }


    void playPrevious() {
        if (current == NULL) {
            cout << "No songs in playlist.\n";
            return;
        }

        current = current->prev;
        if (current == tail)
            cout << "You are now on the last song: " << current->title << endl;
        else
            cout << "Now playing: " << current->title << endl;
    }


    void currentSong() {
        if (current != NULL)
            cout << "Currently playing: " << current->title << endl;
        else
            cout << "No song is currently playing.\n";
    }
};

int main() {
    Playlist playlist;
    int choice;
    string title;

    do {
        cout << "\n==== MUSIC PLAYLIST MENU ====\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Search Song\n";
        cout << "4. Display Playlist (Forward)\n";
        cout << "5. Display Playlist (Backward)\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Show Current Song\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            getline(cin, title);
            playlist.addSong(title);
            break;
        case 2:
            cout << "Enter song title to delete: ";
            getline(cin, title);
            playlist.deleteSong(title);
            break;
        case 3:
            cout << "Enter song title to search: ";
            getline(cin, title);
            playlist.searchSong(title);
            break;
        case 4:
            playlist.displayForward();
            break;
        case 5:
            playlist.displayBackward();
            break;
        case 6:
            playlist.playNext();
            break;
        case 7:
            playlist.playPrevious();
            break;
        case 8:
            playlist.currentSong();
            break;
        case 9:
            cout << "Exiting Playlist. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 9);

    return 0;
}