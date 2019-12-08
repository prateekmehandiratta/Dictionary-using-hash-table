#include <iostream>
#include <vector>
#include "entryclass.hpp"
#include "hashtableclass.hpp"
#include <fstream>
using namespace std;

int main()
{
    hash_table h(2000);
    /*****************FILE READING*********************/
    string line;
    fstream file;
	file.open("words.txt");
    while(!file.eof())
    {
        getline(file,line);
        h.add(line);
    }
    /**********************INTERFACE*****************************/
    int n=1;
    while(n)
    {
        cout << "DICTIONARY" << endl;
        cout << "1. Add word" << endl;
        cout << "2. Remove word" << endl;
        cout << "3. Number of entries" << endl;
        cout << "4. spell check" << endl;
		cout << "5. print" << endl;
        cout << "0. Exit" << endl;
        cin >> n;
        switch(n)
        {
            case 1:{string l;
            		getline(std::cin,l);
                    getline(std::cin,l);
                    h.add(l);
                    break;
            }
            case 2:{cout << "Enter the word - ";
                    string w1;
                    cin >> w1;
                    h.remove(w1);
                    break;
	    }
            case 3:{ cout << h.size() << endl;
                    break;
            }
            case 4:{cout << "Enter the word - ";
                    string w2;
                    cin >> w2;
                    h.spellcheck(w2);
                    break;
            }
	    	case 5:{ h.print();
		    break;
            }
            default:break;
        }
    }
    /************************************************************/
    return 0;
}
