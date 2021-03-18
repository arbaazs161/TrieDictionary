#include<iostream>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<algorithm>
#include <cctype>
#include <string>

using namespace std;

struct wordStructure{               //Structure to build a word character by character
                                    //known as TRIE Structure
    bool isEnd;
    unordered_map<char, wordStructure*> map;
    string meaning;
};

wordStructure* createNode(){        
    wordStructure* node = new wordStructure;
    node->isEnd = false;
    return node;
}

void buildWord(wordStructure*& root, const string& word, const string& meaning){

                                    //build word function takes root of structure
                                    //word and its meaning
    if(root == NULL){
        root = createNode();
    }

    wordStructure *temp = root;

    for(int i = 0; i<word.length(); i++){
        char x = word[i];

        if(temp->map.find(x) == temp->map.end()){
            temp->map[x] = createNode();       
        }
                                    //Checks if the node of a character is present or not

        temp = temp->map[x];        //stores the character in map
    }

    temp->isEnd = true;             //marks end of word
    temp->meaning = meaning;        //store meaning
}

string searchMeaning(wordStructure* root, const string& word){

    if (root == NULL) 
        return ""; 
  
    wordStructure* temp = root;     
  

    for (int i = 0; i < word.length(); i++) { 
        temp = temp->map[word[i]]; 
        if (temp == NULL) 
            return ""; 
    } 
                                    //iterates through every character
                                    //until end of word is true
    if (temp->isEnd) 
        return temp->meaning;       //returns meaning of word stored.
    return "";

}

int main(){     //Main Call

    wordStructure* root = NULL;

    std::ifstream inFile("dictionary.txt");
    if (inFile.is_open())
    {
        std::string line;
        while( std::getline(inFile,line) )
        {
            std::stringstream ss(line);

            std::string word, meaning;
            
            std::getline(ss,word,'|');
            std::getline(ss,meaning,'|');

            buildWord(root, word, meaning);        
        }
    }
                                    //Reads words and meaning from a file
                                    //separated by "|"
    cout<<"Enter word to search : ";
    string str;
    cin>>str; 
    cout <<"Meaning of "<<str<<" : ";
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout<<searchMeaning(root, str);

    return 0;
}