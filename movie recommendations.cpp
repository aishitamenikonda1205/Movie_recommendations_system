#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
// Base Class

class Movie {
protected:
    string title;
    int year;
    float rating;

public:
    Movie(string t, int y) {
        title = t;
        year = y;
        rating = 0;
    }

    virtual void recommendSimilar() = 0;

    void setRating(float r) {
        rating = r;
    }

    float getRating() {
        return rating;
    }

    int getYear() {
        return year;
    }

    string getTitle() {
        return title;
    }

    void display() {
        cout << "Title  : " << title << endl;
        cout << "Year   : " << year << endl;
        cout << "Rating : " << rating << endl;
    }
};

//derive class

class ActionMovie : public Movie {
public:
    ActionMovie(string t, int y) : Movie(t, y) {}

    void recommendSimilar() {
        cout << "Recommended Action Movies: John Wick, Avengers\n";
    }
};

class DramaMovie : public Movie {
public:
    DramaMovie(string t, int y) : Movie(t, y) {}

    void recommendSimilar() {
        cout << "Recommended Drama Movies: Titanic, Joker\n";
    }
};

class ComedyMovie : public Movie {
public:
    ComedyMovie(string t, int y) : Movie(t, y) {}

    void recommendSimilar() {
        cout << "Recommended Comedy Movies: Home Alone, Mr Bean\n";
    }
};

//user class

class User {
private:
    string username;

public:
    User(string u) {
        username = u;
    }

    void showProfile() {
        cout << "\nUser Profile\n";
        cout << "Username: " << username << endl;
    }
};

// Sorting functions 

// Selection Sort by Rating
void selectionSort(vector<Movie*>& movies) {

    int n = movies.size();

    for (int i = 0; i < n - 1; i++) {

        int maxIndex = i;

        for (int j = i + 1; j < n; j++) {

            if (movies[j]->getRating() > movies[maxIndex]->getRating()) {
                maxIndex = j;
            }
        }

        swap(movies[i], movies[maxIndex]);
    }

    cout << "\nMovies Sorted By Rating\n";
}

// Insertion Sort by Year
void insertionSort(vector<Movie*>& movies) {

    int n = movies.size();

    for (int i = 1; i < n; i++) {

        Movie* key = movies[i];
        int j = i - 1;

        while (j >= 0 && movies[j]->getYear() > key->getYear()) {
            movies[j + 1] = movies[j];
            j--;
        }

        movies[j + 1] = key;
    }

    cout << "\nMovies Sorted By Year\n";
}

// Merge Function
void merge(vector<Movie*>& movies, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Movie*> L(n1);
    vector<Movie*> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = movies[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = movies[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {

        if (L[i]->getTitle().length() <= R[j]->getTitle().length()) {
            movies[k] = L[i];
            i++;
        }
        else {
            movies[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        movies[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        movies[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort by Title Length
void mergeSort(vector<Movie*>& movies, int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        mergeSort(movies, left, mid);
        mergeSort(movies, mid + 1, right);

        merge(movies, left, mid, right);
    }
}

// function for display

void displayMovies(vector<Movie*>& movies) {

    if (movies.empty()) {
        cout << "\nNo Movies Available\n";
        return;
    }

    cout << "MOVIE LIST \n";

    for (int i = 0; i < movies.size(); i++) {

        cout << "\nMovie " << i + 1 << endl;

        movies[i]->display();

        movies[i]->recommendSimilar();

        cout << "---------------------\n";
    }
}

// MAIN FUNCTION 

int main() {

    vector<Movie*> movies;

    User user("Aishita");

    int choice;

    while (true) {

        cout << "\n MOVIE RECOMMENDATION SYSTEM \n";

        cout << "1. Add Action Movie\n";
        cout << "2. Add Drama Movie\n";
        cout << "3. Add Comedy Movie\n";
        cout << "4. Rate Movie\n";
        cout << "5. Display Movies\n";
        cout << "6. Sort By Rating\n";
        cout << "7. Sort By Year\n";
        cout << "8. Sort By Title Length\n";
        cout << "9. User Profile\n";
        cout << "10. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        // For adding movies

        if (choice == 1 || choice == 2 || choice == 3) {

            string title;
            int year;

            cin.ignore();

            cout << "Enter Movie Title: ";
            getline(cin, title);

            cout << "Enter Release Year: ";
            cin >> year;

            if (choice == 1) {
                movies.push_back(new ActionMovie(title, year));
            }

            else if (choice == 2) {
                movies.push_back(new DramaMovie(title, year));
            }

            else {
                movies.push_back(new ComedyMovie(title, year));
            }

            cout << "Movie Added Successfully\n";
        }

        // Movie rating

        else if (choice == 4) {

            if (movies.empty()) {
                cout << "No Movies Available\n";
                continue;
            }

            displayMovies(movies);

            int index;
            float rating;

            cout << "Enter Movie Number: ";
            cin >> index;

            cout << "Enter Rating (1-5): ";
            cin >> rating;

            movies[index - 1]->setRating(rating);

            cout << "Rating Updated\n";
        }

        // display

        else if (choice == 5) {
            displayMovies(movies);
        }

        //SORT BY RATING

        else if (choice == 6) {

            selectionSort(movies);

            displayMovies(movies);
        }

        //SORT BY YEAR

        else if (choice == 7) {

            insertionSort(movies);

            displayMovies(movies);
        }

        // SORT BY TITLE LENGTH

        else if (choice == 8) {

            mergeSort(movies, 0, movies.size() - 1);

            cout << "\nMovies Sorted By Title Length\n";

            displayMovies(movies);
        }

        // USER PROFILE 

        else if (choice == 9) {
            user.showProfile();
        }

        // EXIT 

        else if (choice == 10) {

            cout << "Exiting Program...\n";

            break;
        }

        else {
            cout << "Invalid Choice\n";
        }
    }

    return 0;
}
