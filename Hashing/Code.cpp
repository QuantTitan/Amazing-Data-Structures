#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>

using namespace std;

class PhoneRecord
{
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string &n, const string &org, const vector<string> &numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const
    {
        return name;
    }

    string getOrganisation() const
    {
        return organisation;
    }

    vector<string> getPhoneNumbers() const
    {
        return phoneNumbers;
    }
};

class HashTableRecord
{
private:
    int key;
    PhoneRecord *element; // Pointer to PhoneRecord
    HashTableRecord *next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord *rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const
    {
        return key;
    }

    PhoneRecord *getRecord() const
    {
        return element;
    }

    HashTableRecord *getNext() const
    {
        return next;
    }

    void setNext(HashTableRecord *nxt)
    {
        next = nxt;
    }
};

bool lessthan(pair<string, int> &a, pair<string, int> &b)
{
    return a.second > b.second;
}

class PhoneBook
{
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord *hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook()
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
    long long computeHash(const string &str)
    {
        long long int hash = 0;
        int x = HASH_TABLE_SIZE;
        for (int i = 0; i < str.length(); i++)
        {
            hash += (str[i] * ((long long int)pow(x, i) % (long long int)(1e9 + 7)));
        }
        hash %= x;
        return hash;
    }

    // Add your own implementation for adding a contact
    void addContact(PhoneRecord *record)
    {
        long long int key;
        string word;
        stringstream inp_name(record->getName());
        while (getline(inp_name, word, ' '))
        {
            key = computeHash(word);
            HashTableRecord *HTR_obj = new HashTableRecord(key, record); 
            if (hashTable[key] != nullptr)
            {
                HTR_obj->setNext(hashTable[key]);
            }
            hashTable[key] = HTR_obj;
        }
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string *searchName)
    {
        string word;
        int key, pos, i;
        vector<PhoneRecord *> v = fetchContacts(searchName);
        if (v.size() == 0) 
        {                  
            return false;
        }
        PhoneRecord *first = *v.begin(); 
        HashTableRecord *temp;
        HashTableRecord *temp2;
        stringstream word_stream(first->getName());
        while (word_stream >> word)
        {
            pos = 0;
            key = computeHash(word);
            temp = hashTable[key];
            while (temp != nullptr)
            {
                pos++;
                if (temp->getRecord()->getName().compare(first->getName()) == 0)
                {
                    break;
                }
                temp = temp->getNext();
            }
            temp = hashTable[key];
            if(pos == 1)
            {
                hashTable[key] = temp->getNext();
                free(temp);
                continue; 
            }
            for (i = 1; i < pos - 1; i++)
            {
                temp = temp->getNext();
            }
            temp2 = temp->getNext();
            temp->setNext(temp2->getNext());
            delete (temp2); 
        }
        return true;
    }

    vector<PhoneRecord *> fetchContacts(const string *query)
    {
        int f;
        long long int key;
        string word, name_word, PR_name;
        map<string, int> m;
        vector<PhoneRecord *> store;
        stringstream q(*query);
        while (q >> word)
        {
            key = computeHash(word);
            HashTableRecord *head = hashTable[key];
            while (head != nullptr)
            {
                PR_name = head->getRecord()->getName();
                stringstream name(PR_name);
                while (name >> name_word)
                {
                    if (word.compare(name_word) == 0)
                    {
                        f = 0;
                        for (auto &it3 : store)
                        {
                            if (it3 == head->getRecord()) 
                            {
                                f = 1;
                                break;
                            }
                        }
                        if (f == 0)
                        {
                            store.push_back(head->getRecord());
                        }
                        m[PR_name] += 1; 
                        break;
                    }
                }
                head = head->getNext();
            }
        }

        // sorting
        vector<pair<string, int>> v;
        for (auto &it : m)
        {
            v.push_back(it);
        }
        sort(v.begin(), v.end(), lessthan); 
        vector<PhoneRecord *> res;
        for (auto &it1 : v)
        {
            for (auto &it2 : store)
            {
                if (it2->getName().compare(it1.first) == 0)
                {
                    res.push_back(it2);
                }
            }
        }
        return res;
    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord *record) const
    {
        int c = 0;
        string name = record->getName();
        stringstream nm(name);
        while(nm >> name)
        {
            c++;
        }
        return c;
    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string &filename)
    {
        string line, cmd, ele, name, org;
        fstream file(filename, ios::in);
        while (getline(file, line, '\n'))
        {
            stringstream input_line(line);
            vector<string> phonenum;
            getline(input_line, name, ',');
            while (getline(input_line, ele, ','))
            {
                phonenum.push_back(ele);
            }
            phonenum.pop_back();
            org = ele.substr(0, ele.length() - 1);
            PhoneRecord *PR_obj = new PhoneRecord(name, org, phonenum); 
            addContact(PR_obj);
        }
    }

    // Destructor
    ~PhoneBook()
    {
        
    }
};
