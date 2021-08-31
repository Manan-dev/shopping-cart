#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

// function prototypes
int NumNonWSCharacters(const string&);
int NumWords(const string&);
void CharReplace(string&, char, char);
char PrintMenu();

// The god of all functions --> Main
int main (){
    string userInput;
    istringstream ss;
    char userChoice;
    char replaceChar;
    char findChar;
    
    string filename;
    cout << "Enter a file to read: ";
    cin >> filename;
    cout << endl;

// takes in filename then error checks
    ifstream in(filename);
    if (!in){
        cerr << "Unable to open file " << filename << endl;
        return 1;
    }

// stores the help.txt contents into a vector
    string userText2;
    vector <string>name;
    cout << filename << " contains: \n";
   while(getline(in,userText2)){
        cout << userText2 << endl;
        name.push_back(userText2);
   }
    in.close();

// runs till user types in character q
    while (userChoice != 'q'){
        userChoice = PrintMenu();
        int Count = 0;
// switch statements for all functions
    switch (userChoice)
    {
    case 'c':
// added for loop for every case to count or replace.
        for (unsigned int i =0; i <name.size(); i++){
          Count += NumNonWSCharacters(name.at(i));
        }
        cout << "\nNumber of non-whitespace characters: " << Count << endl;
        break;

    case 'w':
        for (unsigned int i =0; i <name.size(); i++){
          Count += NumWords(name.at(i));
        }
        cout << "\nNumber of words: " << Count << endl;
        break;

    case 'r':
        cout<< "Enter a character to find: ";
        cin >> findChar;
        cout<< "Enter a character to replace: ";
        cin >> replaceChar;
        cout << "\nNew contents: " << endl;
        for (unsigned int i =0; i <name.size(); i++){
        CharReplace(name.at(i), findChar, replaceChar);
        }
        cout << '\n';
        break;

    case 'q':
        return 0;
        break;
        
    default:
        userChoice = PrintMenu();
        break;
    }
// makes the output.txt file for new contents
    ofstream out("output.txt");
    for (unsigned int i =0; i < name.size(); i++){
        out << name.at(i) << '\n';
    }
    out.close();
}

    return 0;
}

// print menu function and returns a character of user's choice
char PrintMenu(){
    char choice;
    cout << "\nOptions\n";
    cout << "w - Number of words\n";
    cout << "c - Number of non-whitespace characters\n";
    cout << "r - Replace a character\n";
    cout << "q - Quit\n";
    cout << endl;
    cout << "Choose an option: ";
    
    // Ctrl- D part
    if (!(cin  >> choice)){
        cout << endl;
        return 'q';
    } else{
    return choice;
}
}

// counts the number of words
int NumWords(const string& userText1){
        istringstream ss;
        string everyWord;
        int count = 0;
        ss.str(userText1);
        while (ss >> everyWord){
            count++;
        }
    return count;
}

// counts non-whitespace characters
int NumNonWSCharacters(const string& userWords){  
    istringstream fullInput;
    string eachWord;
    int countNonWS = 0;
    fullInput.str(userWords);

    while (fullInput >> eachWord){
        countNonWS += eachWord.length();
}
    return countNonWS;
}

// replaces character of user's choice with another character of user's choice and returns nothing
void CharReplace(string& userText2, char findChar2, char replaceChar2){
    
    for (unsigned int j = 0; j < userText2.size(); j++){
        if (userText2.at(j) == findChar2){
            userText2.at(j) = replaceChar2;
        }
    }
  cout << userText2 << endl;
}
