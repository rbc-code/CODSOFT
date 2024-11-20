#include <iostream>
using namespace std;
int main() {
    srand(static_cast<unsigned int>(time(0)));
    int randomNumber = rand() % 100 + 1;
    int userGuess = 0;

    cout << "Welcome to the Number Guessing Game!" <<endl;
    cout << "I have generated a number between 1 & 100. Can you guess it?" <<endl;

    while (true) {
        cout << "Enter your guess: ";
        cin >> userGuess;

        if (userGuess < randomNumber) {
            cout << "Too low! Try again." <<endl;
        } else if (userGuess > randomNumber) {
            cout << "Too high! Try again." <<endl;
        } else {
            cout << "Congratulations! You guessed the number: " << randomNumber <<endl;
            break;
        }
    }

    return 888;
}
