#include <iostream>
#include <vector>
using namespace std;

// Movie class
class Movie {
private:
    string title;
    string genre;
    int duration; // in minutes

public:
    Movie(string t, string g, int d) : title(t), genre(g), duration(d) {}

    string getTitle() const { return title; }

    void playMovie() const {
        cout << "Now Playing: " << title << " [" << genre << ", " << duration << " mins]\n";
    }
};

// Netflix class
class Netflix {
private:
    vector<Movie> movies;

public:
    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    void watchMovie(const string& movieTitle) {
        for (const auto& movie : movies) {
            if (movie.getTitle() == movieTitle) {
                movie.playMovie();
                return;
            }
        }
        cout << "Movie not found in the catalog.\n";
    }

    void showAvailableMovies() const {
        cout << "Available Movies:\n";
        for (const auto& movie : movies) {
            cout << "- " << movie.getTitle() << "\n";
        }
    }
};

// Main function
int main() {
    // Creating Netflix service
    Netflix netflix;

    // Adding movies
    netflix.addMovie(Movie("Inception", "Sci-Fi", 148));
    netflix.addMovie(Movie("The Dark Knight", "Action", 152));
    netflix.addMovie(Movie("Interstellar", "Sci-Fi", 169));

    // Display available movies
    netflix.showAvailableMovies();

    // Watching movies
    netflix.watchMovie("Inception");
    netflix.watchMovie("Avatar"); // Should show "Movie not found."

    return 0;
}
