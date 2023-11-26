#include <iostream>
#include <string>

using namespace std;

class Trie
{
public:
    bool isWord;
    Trie* node[26];

    Trie(){
        isWord = false;
        for (int i = 0; i < 26; i++)
            this->node[i] = NULL;
    }
    
    bool search(string key){
        if(key.empty()){
            return this->isWord;
        }

        else if (!this->node[key.front() - 'a']) {
            return false;
        }

        return this->node[key.front() - 'a']->search(key.substr(1));
    }
    
    void insert(string value) {
        if (value.empty()) {
            this->isWord = true;
            return;
        }
        else if (!this->node[value.front() - 'a']) {
            this->node[value.front() - 'a'] = new Trie();
        }
        this->node[value.front() - 'a']->insert(value.substr(1));
    }
    
    void preorder(){
        if(this->isWord){
            cout << " ";
        }
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
