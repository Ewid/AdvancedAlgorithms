#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

// Time Complexity is O(n) number of characters in the input, we check for each character in the string.
// The Best Case (yyyyy) is where all are the same character, Average case is some repeated characters (yoyo) Worst case is all different characters (yousef).

// Space Complexity is also O(n) as it needs more space as the input size increases we need to store all unique characters.
// The Best Case (yyyyy) you only keep one as there is no variety of Characters. Average case is some repeated characters (yoyo) you keep one of each type (y), (o) only.
// The Worst Case is when (yousef) you have to keep one from each as they are all different characters all are different.

string DuplicateRemoval(const string &input) {
    unordered_set<char> seenchars; // Every Time We Will See A Character We Will Add It To This Set As A Seen Character.
    string result; // This One Will Keep Adding The Characters That Have Not Been Added To Seen To Make Sure All The Duplicates Are Filtered Out.

    for (char c : input) { // Going Through All The Characters In The Inputted String Once To Ensure Linear Traversal (Sequential Accessing Of each character in the string) O(n) complexity 
        char lowercased = tolower(c);
        if (seenchars.find(lowercased) == seenchars.end()) { // Checks If The Character Has not been seen yet 
            seenchars.insert(lowercased); // If Condition above applies Adds it to the set of Seen Characters as a unique character.
            result += lowercased; // Unique Characters appended to result string 
        }
    }

    return result;
}

int main() {
    string input = "Advanced Algorithms Easy Task Number One"; // String Input
    string output = DuplicateRemoval(input); // Function Works On The Input
    cout << "String with duplicate characters : " << input << endl; // Print Original String
    cout << "String after duplicate characters have been removed : " << output << endl; // Print String with no duplicate chars.
    return 0;
}
