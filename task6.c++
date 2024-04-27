#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

vector<string> splitWords(const string& text) {
    vector<string> words;
    istringstream iss(text);
    string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

void wrapText(const vector<string>& words, int lineWidth) {
    int currentWidth = 0;
    int lineCount = 1;

    for (int i = 0; i < words.size(); ++i) {
        const string& word = words[i];

        if (currentWidth + word.length() > lineWidth) {
           
            cout << endl << "line " << lineCount << ": " << word;
            currentWidth = word.length() + 1; 
            lineCount++;
        } else {
            if (currentWidth == 0) {
                cout << "line " << lineCount << ": " << word;
                currentWidth += word.length();
            } else {
                cout << " " << word;
                currentWidth += word.length() + 1; 
            }
        }
    }
    cout << endl;
}

int main() {
    string text = "Mary loves to sing and perform tapdancing.";
    int lineWidth = 10;

    vector<string> words = splitWords(text);

    wrapText(words, lineWidth);

    return 0;
}
