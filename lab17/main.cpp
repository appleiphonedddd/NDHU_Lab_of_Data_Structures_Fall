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
        /**
         * Initialize all the nodes to NULL
         */
        for (int i = 0; i < 26; i++)
            this->node[i] = NULL;
    }

    void insert(string value)
    {
        Trie *current = this;
        for (char ch : value)
        {
            /**
             * If the current node doesn't have the next node, create a new node
             */
            if (current->node[ch - 'a'] == NULL)
            {
                current->node[ch - 'a'] = new Trie();
            }
            current = current->node[ch - 'a']; // Move to the next node
        }
        current->isWord = true; // Mark the end of the word
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
        return current != NULL && current->isWord; // Check if the current node is the end of the word
    }

    void preorder(Trie *trie, string word = "")
    {
        if (trie->isWord)
        {
            cout << word << endl; // Print the word
        }
        for (int i = 0; i < 26; i++)
        {
            /**
             * If the node exists, move to the next node
             */
            if (trie->node[i])
            {
                char nextChar = i + 'a'; // Convert the index to the character
                preorder(trie->node[i], word + nextChar); // Move to the next node in recursion
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
