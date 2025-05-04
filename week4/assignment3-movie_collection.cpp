#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MOVIE_COUNT = 3;

struct Movie {
    string title;
    string director;
    int yearReleased;
    int duration; // in minutes
    double rating; // out of 10
    string genre;
};

void inputMovies(Movie movies[], int count) {
    for (int i = 0; i < count; ++i) {
        cout << "\nEnter information for movie #" << i + 1 << ":\n";
        cout << "Title: ";
        getline(cin, movies[i].title);
        cout << "Director: ";
        getline(cin, movies[i].director);
        cout << "Year released: ";
        cin >> movies[i].yearReleased;
        cout << "Duration (minutes): ";
        cin >> movies[i].duration;
        cout << "Rating (0-10): ";
        cin >> movies[i].rating;
        cin.ignore(); // Clear newline character
        cout << "Genre: ";
        getline(cin, movies[i].genre);
    }
}

void displayMovies(const Movie movies[], int count) {
    cout << "\nYOUR MOVIE COLLECTION:\n----------------------\n";
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << movies[i].title << " (" << movies[i].yearReleased << ")\n";
        cout << "   Director: " << movies[i].director << "\n";
        cout << "   Duration: " << movies[i].duration << " minutes\n";
        cout << "   Rating: " << fixed << setprecision(1) << movies[i].rating << "/10\n";
        cout << "   Genre: " << movies[i].genre << "\n\n";
    }
}

double calculateAverageRating(const Movie movies[], int count) {
    double total = 0.0;
    for (int i = 0; i < count; ++i) {
        total += movies[i].rating;
    }
    return total / count;
}

int findLongestMovieIndex(const Movie movies[], int count) {
    int maxIndex = 0;
    for (int i = 1; i < count; ++i) {
        if (movies[i].duration > movies[maxIndex].duration) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void findMoviesAfterYear(const Movie movies[], int count, int year) {
    cout << "Movies released after " << year << ":\n";
    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (movies[i].yearReleased > year) {
            cout << "- " << movies[i].title << " (" << movies[i].yearReleased << ")\n";
            found = true;
        }
    }
    if (!found) {
        cout << "None\n";
    }
}

int main() {
    Movie movies[MOVIE_COUNT];

    cout << "MOVIE COLLECTION MANAGER\n------------------------\n";
    inputMovies(movies, MOVIE_COUNT);

    displayMovies(movies, MOVIE_COUNT);

    cout << "Collection Statistics:\n";
    double averageRating = calculateAverageRating(movies, MOVIE_COUNT);
    cout << "Average rating: " << fixed << setprecision(1) << averageRating << "/10\n";

    int longestIndex = findLongestMovieIndex(movies, MOVIE_COUNT);
    cout << "Longest movie: " << movies[longestIndex].title
         << " (" << movies[longestIndex].duration << " minutes)\n\n";

    int year;
    cout << "Enter a year to find movies released after that year: ";
    cin >> year;
    cin.ignore(); // Clear newline
    findMoviesAfterYear(movies, MOVIE_COUNT, year);

    return 0;
}
