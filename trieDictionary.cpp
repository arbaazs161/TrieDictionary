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



string suggestWord(wordStructure *root, string word){
    if(root->isEnd){
        return word;
    }

    if(root == NULL){
        return "No Word Found";
    }

    for(int i = 0; i<word.length(); i++){
        root = root->map[word[i]];
    }

    while(!root->isEnd){
        char x = root->map.begin()->first;
        word.push_back(x);
        root = root->map[x];
    }

    return word;

}

string query(wordStructure* root){  //Reads words and meaning from a file
                                    //separated by "|"
    cout<<"Enter word to search : ";
    string str, meaning, meaningStr;
    cin>>str; 
    
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    meaning = searchMeaning(root, str);
    if(meaning != ""){
        meaningStr = "Meaning of " + str + " is : " + meaning;
    }
    else{
        meaning = suggestWord(root, str.substr(0, str.length()/2));
        if(meaning != ""){
            meaningStr = "Did you mean : " + meaning;
        }
        else{
            meaningStr = "No such Word found :(";
        }
    }
    return meaningStr;
}

int main(){     //Main

    wordStructure* root = NULL;
    bool quit = true;
    int startup;

    std::ifstream inFile("AWordsDict.txt");
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
    
    cout<<"Welcome to My Dictionary\n";
    do{
    cout<<"1. Search Word\n";
    cout<<"0. Quit\n";
    cin>>startup;

    switch(startup){
        case 1: cout<<query(root)<<"\n";
                //cout<<suggestWord(root, "ad");
                break;
        case 0: quit = false;
                break;
        default: cout<<"Wrong Command :( . Try Again.\n";
                break;
    }
    }while (quit);
    
    return 0;
}