#include <iostream>
#include <cctype>
#include <unordered_map>
#include <fstream>
#include <cstring>

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
        return string(encrypted_word.length(), '?');
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

/// Finds the next series of one or more numbers from the string.
/// @param word_len is overwritten as the length of the returned string.
/// @returns a slice of the msg string if a word could be found, otherwise empty string is returned.
string next_encrypted_word(const string& msg, size_t start_pos, size_t& end_pos) {
    size_t start;
    size_t end = msg.length();
    bool reading_word = false;
    for (size_t i = start_pos; i < msg.length(); ++i) {
        if (isdigit(msg[i])) { // If this character is a number
            if (!reading_word) {
                start = i;
                reading_word = true;
            }
        } else {
            if (reading_word) {
                end = i;
                break;
            }
        }
    }
    if (!reading_word) return {}; // If we didn't find a word
    end_pos = end; // Set the caller's variable for the end position
    return msg.substr(start, end-start); // Return part of the string that contains the word
}

string decrypt(const string& msg) {
    string decrypted_msg;
    unordered_map<string, string> words = words_from_list("words.txt");

    size_t pos = 0;
    size_t last_word_end;
    string word;
    while (!(word = next_encrypted_word(msg, pos, last_word_end)).empty()) {
        auto decrypted = decrypt_word(word, words);
        decrypted_msg.append(msg.substr(pos, last_word_end-decrypted.length()-pos));
        decrypted_msg.append(decrypted);
        pos = last_word_end;
    }
    // Push any characters past the last encrypted word
    if (last_word_end < decrypted_msg.length()) decrypted_msg.append(msg.substr(last_word_end));

    return decrypted_msg;
}

const char* const USAGE = "USAGE: one <encrypt|decrypt> <message>";

void print_help() {
    cout << USAGE << endl;
}

int main(int argc, const char* argv[]) {
    if (argc == 3) {
        if (strcmp(argv[1], "encrypt") == 0) {
            cout << encrypt(argv[2]) << endl;
        } else if (strcmp(argv[1], "decrypt") == 0) {
            cout << decrypt(argv[2]) << endl;
        } else {
            cout << "Not a valid command. Either \"encrypt\" or \"decrypt\"." << endl;
            print_help();
            return 1;
        }
    } else {
        cout << "Need more than one argument." << endl;
        print_help();
        return 1;
    }
    return 0;
}
