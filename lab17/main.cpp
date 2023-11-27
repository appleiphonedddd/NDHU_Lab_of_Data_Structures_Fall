#include <iostream>
#include <string>

using namespace std;

class Trie
{
public:
    bool isWord;
    Trie *node[26];

    Trie()
    {
        isWord = false;
        for (int i = 0; i < 26; i++)
            this->node[i] = NULL;
    }

    void insert(string value)
    {
        Trie *current = this;
        for (char ch : value)
        {
            if (current->node[ch - 'a'] == NULL)
            {
                current->node[ch - 'a'] = new Trie();
            }
            current = current->node[ch - 'a'];
        }
        current->isWord = true;
    }

    bool search(string key)
    {
        Trie *current = this;
        for (char ch : key)
        {
            if (current->node[ch - 'a'] == NULL)
            {
                return false;
            }
            current = current->node[ch - 'a'];
        }
        return current != NULL && current->isWord;
    }

    void preorder(Trie *trie, string word = "")
    {
        if (trie->isWord)
        {
            cout << word << endl;
        }
        for (int i = 0; i < 26; i++)
        {
            if (trie->node[i])
            {
                char nextChar = i + 'a';
                preorder(trie->node[i], word + nextChar);
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
            trie->preorder(trie);
        }
        else if (command == "exit")
        {
            break;
        }
    }
}
