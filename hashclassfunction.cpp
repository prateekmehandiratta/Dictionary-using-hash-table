#include <iostream>
#include "entryclass.hpp"
#include "hashtableclass.hpp"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

unsigned long long int hash_table::pow(int a,int b)
{
    if(b==0)
        return 1;
    int result=1;
    for(int i=1;i<=b;i++)
    {
    result = (result*a)%table_size;
    }
        
    return result;
}

int minc(int a,int b,int c)
{
    int temp;
    if(a<=b)
        temp=a;
    else
        temp=b;
    if(c<temp)
        temp=c;
    return temp;
}

int dist(string str1 , string str2,int m,int n)
{
    if (m == 0)
        return n;
    if (n == 0)
        return m;
    if (str1[m-1] == str2[n-1])
        return dist(str1, str2, m-1, n-1);
    int a,b,c;
    a=dist(str1,  str2, m, n-1);
    b=dist(str1,  str2, m-1, n);
    c=dist(str1,  str2, m-1, n-1);
    return 1 + minc (a,b,c);
}


hash_table::hash_table(int ts)
{
    no_of_entries = 0;
    table_size = ts;
    table.resize(ts);
    for(int i=0;i<ts;i++)
        table[i] = NULL;
}

unsigned long long int hash_table::hash_function(string str)
{
    int k=str.size();
    unsigned long long int key=0;
    for(int i=0;i<k;i++)
    {
        int ASCII = str[i];
        key +=( (ASCII)*pow(7,k-1-i) )%table_size;;
    }
    return key;
}

unsigned long long int hash_table::hash_compress1(unsigned long long int k)
{
    return k%table_size;
}

unsigned long long int hash_table::hash_compress2(unsigned long long int k)
{
    int prime = 31;
    k = prime - (k%prime);
    return k;
}

int hash_table::size()
{
    return no_of_entries;
}

void hash_table::add(string l)
{
	if(no_of_entries == table_size)
	{
		cout << "NOW THE TABLE IS FULL," << table_size << " entries are in the table";
		return;
	}
    transform(l.begin(),l.end(),l.begin(),::tolower);
    int i=0;
    string w="";
    while(isalpha(l[i]))
    {
    	w = w + l[i];
    	i++;
    }
    string m = &l[i];
    entry* e = new entry(w,m);
    unsigned long long int key = hash_function(w);
    unsigned long long int a = hash_compress1(key),b = hash_compress2(key);
    unsigned long long int loc = a;
    while( table[loc] != NULL && table[loc]->word != w && table[loc]->word != "xxxxx")
    {
    	loc += b;
    }
    if(table[loc] == NULL || table[loc]->word == "xxxxx")
        no_of_entries++;
    loc = loc%table_size;
    table[loc] = e;
}

void hash_table::remove(string w)
{
    transform(w.begin(),w.end(),w.begin(),::tolower);
    unsigned long long int key = hash_function(w);
    unsigned long long int a = hash_compress1(key),b = hash_compress2(key);
    unsigned long long int loc = a;
    while(table[loc] != NULL)
    {
    	if(table[loc]->word == w)
    		break;
    	loc +=b;
    }
    if(table[loc]!=NULL)
    {
    	table[loc]->word = "xxxxx";
        table[loc]->mean = "xxxxx";
        no_of_entries--;
    }
}

void hash_table::spellcheck(string w)
{
    transform(w.begin(),w.end(),w.begin(),::tolower);
    for(int i=0;i<table_size;i++)
    {
        if(table[i]!=NULL)
        {
            if(table[i]->word == w)
            {
                cout << w << " is there in the dictionary with the meaning - " << table[i]->mean << endl;
                return;
            }
        }
    }
    int check=0;
    cout << "List of the words for " << w << " after spellCheck ->\n";
    for(int i=0;i<table_size;i++)
    {
        if(table[i]!=NULL)
        {
            /*********************************************************************************************************/
            int m=w.size();
            int n=table[i]->word.size();
            int diff;
            if(m>n)
                diff=m-n;
            else
                diff=n-m;
            if(diff==1)
            {
                if(dist(w,table[i]->word,m,n)==1)
                {
                    cout << check+1 << ". " << table[i]->word << endl;
                    check++;
                }
            }
            else if(diff==0)
            {
            	if(dist(w,table[i]->word,m,n)==1)
				{
					cout << check+1 << ". " << table[i]->word << endl;
                    check++;
				}
				else if(dist(w,table[i]->word,m,n)==2)
				{
					int flag=0;
					for(int j=0;j<m;j++)
					{
						if(w[j] != table[i]->word[j] )
						{
							if(i<(m-1) )
							{
								if(w[j+1] == table[i]->word[j] && w[j] == table[i]->word[j+1])
									flag=1;
							}
						}
					}
					if(flag==1)
					{
						cout << check+1 << ". " << table[i]->word << endl;
                    	check++;
					}
				}
			}
            /*********************************************************************************************************/
        }
    }
    if(check==0)
        cout << "SORRY ! No words" << endl;
}

void hash_table::print()
{
    for(int i=0;i<table_size;i++)
    {
        if(table[i] != NULL)
            cout << table[i]->word << " " << i << " " << table[i]->mean << "\n";
    }
}

