#include <string>
#include <iostream>
bool Guess(int number) { 
return false; 
} 
int main() { 
int guess;
do {
std::cin >> guess;
} while (!Guess(guess));
return 0;
}