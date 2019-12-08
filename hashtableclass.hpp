#pragma once
#include <iostream>
#include <vector>
#include "entryclass.hpp"
using namespace std;

class hash_table
{
private:
    long table_size;
    long no_of_entries;
    vector<entry*> table;
    unsigned long long int hash_function(string);
    unsigned long long int hash_compress1(unsigned long long int);
    unsigned long long int hash_compress2(unsigned long long int);
public:
	unsigned long long int pow(int,int);
    hash_table(int);
    int size(void);
    void add(string);
    void remove(string);
    void spellcheck(string);
    void print(void);
};
