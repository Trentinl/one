#include <iostream>
#include <cctype>
#include <unordered_map>
#include <fstream>

using namespace std;

string encrypt(const string& message) {
    string output;
    for (size_t i = 0; i < message.length(); ++i) {
        char c = message[i];
        switch (tolower(c)) {
            case 'q':
            case 'a':
            case 'z':
                output.push_back('1');
                break;
            case 'w':
            case 's':
            case 'x':
                output.push_back('2');
                break;
            case 'e':
            case 'd':
            case 'c':
                output.push_back('3');
                break;
            case 'r':
            case 'f':
            case 'v':
                output.push_back('4');
                break;
            case 't':
            case 'g':
            case 'b':
                output.push_back('5');
                break;
            case 'y':
            case 'h':
            case 'n':
                output.push_back('6');
                break;
            case 'u':
            case 'j':
            case 'm':
                output.push_back('7');
                break;
            case 'i':
            case 'k':
                output.push_back('8');
                break;
            case 'o':
            case 'l':
                output.push_back('9');
                break;
            case 'p':
                output.push_back('0');
                break;
            default:
                output.push_back(c);
        }
    }
    return output;
}

string decrypt_word(const string& encrypted_word, const unordered_map<string, string>& words) {
    try {
        return words.at(encrypted_word);
    } catch (out_of_range) {
        return "?";
    }
}

// wordlist.txt has a word on each line, in no specific order
// we want to put each word from this word list into a hashmap
// where the key = the encrypted word ("63999") and the value =
// the word ("hello")

unordered_map<string, string> words_from_list(const string& filename) {
    unordered_map<string, string> words;

    ifstream file(filename);

    string line;
    while (getline(file, line)) {
        words[encrypt(line)] = line;
    }

    return words;
}

string decrypt(const string& msg) {
    unordered_map<string, string> words = words_from_list("words.txt");

    return decrypt_word(msg, words);
}

int main() {
    string msg = "3634605896";
    cout << decrypt(msg) << endl;
    return 0;
}




// main:
// either check the command line arguments or
// allow the user to interactively decide what
// they want to do.

// their options are: decode a keycrypt string,
// or: encrypt a keycrypt string


// encrypting is taking a string to produce another string of the same length
// trentin is handsome -> 5436586 82 61632973

// decrypting is also taking a string to produce another string, but it is much more involved
// 5436586 82 61632973 -> trentin is handsome


// Crypt
// "1" - 'Q' | 'A' | 'Z'
// "2" - 'W' | 'S' | 'X'
// "3" - 'E' | 'D' | 'C'
// "4" - 'R' | 'F' | 'V'
// "5" - 'T' | 'G' | 'B'
// "6" - 'Y' | 'H' | 'N'
// "7" - 'U' | 'J' | 'M'
// "8" - 'I' | 'K'
// "9" - 'O' | 'L'
// "0" - 'P'

//#include <map>
//#include <iostream>
//#include <cassert>
//
//int main(int argc, char **argv)
//{
//    std::map<std::string, int> m;
//    m["hello"] = 23;
//    // check if key is present
//    if (m.find("world") != m.end())
//        std::cout << "map contains key world!\n";
//    // retrieve
//    std::cout << m["hello"] << '\n';
//    std::map<std::string, int>::iterator i = m.find("hello");
//    assert(i != m.end());
//    std::cout << "Key: " << i->first << " Value: " << i->second << '\n';
//    return 0;
//}