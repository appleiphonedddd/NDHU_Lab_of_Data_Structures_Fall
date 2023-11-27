#include <iostream>
#include <string>

using namespace std;

class Trie
{
public:
    bool isWord;    // isWord is true if the node represents end of a word
    Trie* node[26]; // links to the child nodes

    Trie(){
        isWord = false;
        /**
         * Initialize all the child nodes to NULL
         */
        for (int i = 0; i < 26; i++)
            this->node[i] = NULL;
    }
    
    bool search(string key){
        /**
         * If the key is empty, return the value of isWord
         */
        if(key.empty()){
            return this->isWord;
        }

        /**
         * If the key is not empty and the child node is NULL, return false
         */
        else if (!this->node[key.front() - 'a']) {
            return false;
        }

        return this->node[key.front() - 'a']->search(key.substr(1)); // search the next node in recursion
    }
    
    void insert(string value) {
        /**
         * If the value is empty, set isWord to true and return
         */
        if (value.empty()) {
            this->isWord = true;
            return;
        }
        /**
         * If the value is not empty and the child node is NULL, create a new node
         */
        else if (!this->node[value.front() - 'a']) {
            this->node[value.front() - 'a'] = new Trie();
        }
        this->node[value.front() - 'a']->insert(value.substr(1)); // insert the next node in recursion
    }
    
    void preorder(){
        /**
         * If the node represents end of a word, print a space
         */
        if(this->isWord){
            cout << " ";
        }
        /**
         * Print the character and traverse all the child nodes
         */
        for(int i = 0; i < 26; i++){
            if(this->node[i]){
                cout << (char)(i + 'a');
                this->node[i]->preorder();
            }
        }
    }
};

int main()
{
    Trie *trie = new Trie();
    string command, key, value;
    while (1)
    {
        cin >> command;
        if (command == "insert")
        {
            cin >> value;
            trie->insert(value);
        }
        else if (command == "search")
        {
            cin >> key;
            if (trie->search(key))
                cout << "exist" << endl;
            else
                cout << "not exist" << endl;
        }
        else if (command == "print")
        {
            trie->preorder();
        }
        else if (command == "exit")
        {
            break;
        }
    }
}
