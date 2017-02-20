/**
 * Project 1: convert4to5.cpp
 * 
 * Authored by: Takumi Nishida AND Jacob Hansen
 * CSCI 446 
 * Spring semester
 */


#include <iostream>
#include <cmath>
#include <unordered_map>
#include <string>

using namespace std;

// global dictionary lookup hash table
unordered_map<string, string> dictTable;


/**
 * Perform a table lookup on a nible to retreive its 5-bit encoding.
 *
 * @param nible The binary data string (nible) to be encoded.
 *
 * @return The 5-bit encoding for the passed nible.
 */
string convert4Bto5B(const string nible) {
    return dictTable[nible];
}

/**
 * Convert a string to its binary equivalent.
 *
 * @param inStr The character string to be encoded in binary.
 *
 * @return A string of binary data representing the passed string.
 */
string stringToBinary (const string& inStr) {
    string outStr;
    double base = 2;

    for(unsigned int i=0; i<inStr.length(); i++) {
        int charCode = inStr[i];
        string binaryCharStr = ""; 

        for(double j=7; j>=0; j--) {
            int thisPower = pow(base, j); 
            char thisDigit = '0' + charCode / thisPower;

            if(thisDigit == '1') {
                charCode -= thisPower;
            }

            binaryCharStr += thisDigit;
        }   

        outStr += binaryCharStr;
    }   

    return outStr;
}


// MAIN //
int main(int argc, char* argv[]) {
    // populate the dictionary
    dictTable["0000"] = "11110";
    dictTable["0001"] = "01001";
    dictTable["0010"] = "10100";
    dictTable["0011"] = "10101";
    dictTable["0100"] = "01010";
    dictTable["0101"] = "01011";
    dictTable["0110"] = "01110";
    dictTable["0111"] = "01111";
    dictTable["1000"] = "10010";
    dictTable["1001"] = "10011";
    dictTable["1010"] = "10110";
    dictTable["1011"] = "10111";
    dictTable["1100"] = "11010";
    dictTable["1101"] = "11011";
    dictTable["1110"] = "11100";
    dictTable["1111"] = "11101";

    string msg = "";
    cout << "please enter a message: " << endl;
    getline(cin, msg);

    cout << "your message " << msg << endl;

    string binaryMsg = stringToBinary(msg);
    cout << "in binary: " << binaryMsg << endl;

    string encodedMsg = "";
    for(unsigned int i=0; i<binaryMsg.length(); i+=4) {
        string nextCharBinary = convert4Bto5B(binaryMsg.substr(i, 4));
        encodedMsg += nextCharBinary;
    }
    cout << "is encode using 4B/5B to: " << encodedMsg << endl;

    return 0;
}
