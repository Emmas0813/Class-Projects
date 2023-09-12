// Emma Smith
// Project 6
// CS 2413 Data Structures
// Spring 2023

// g++ project6.cpp -o p1
// get-content input6.txt | ./p1

#include <iostream>
#include <string> // for storing string
#include <fstream> // for reading a file again and again
#include <map> 
#include <unordered_map> 
#include <vector>
#include <time.h> // for timing experiments

using namespace std;

// write hash function
int hashFunction(const std::string& key){
	int hashVal= 0; // initialize the hash value to 0 for summation
	int count = 1; // unique number to avoid collisions
	for(char c : key){ // for every character in the string
		hashVal = hashVal + (c * count); // add the ASCII value of the character to the product of the hashVal and the unique prime number
		count++; // increment counter to be unique to characters placement
	}
	return hashVal; // return the sum of all unique values
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// write display functions for map and unordered map
void displayMap(map <int, vector<string>> m){ 
	cout << "Map: " << endl;
	for(auto& it : m){ // iterate through the map
		if(!it.second.empty()){ // ensure the current key contains a value
			cout << it.first << ": "; // display the hash value
			for(auto& name : it.second){ // iterate the vector of strings 
				cout << name << " "; // display the strings
			}
			cout << endl;
		}
	}
}
void displayUnorderedMap(unordered_map<int, vector<string>> m2){
	cout << "unordered map: " << endl;
	for(auto& it : m2){ // iterate through the unordered map
		if(!it.second.empty()){ // ensure the current key contains a value
			cout << it.first << ": "; // display the hash values
			for(auto& name : it.second){  // iterate the vector of stings
				cout << name << " "; // display the strings
			}
			cout << endl;
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// find function to remove elements from the map
void removeMap(map<int, vector<string>>& m, const string& temp, int hash) {  
    auto& vec = m[hash]; // store the current values at given hash
    for (int i = 0; i < vec.size(); i++) { // iterate each element in the vector
        if (vec[i] == temp) { // if the current element in the vector is found
            vec.erase(vec.begin() + i); // delete the value at hash
        }
    }
}
void removeUnorderedMap(unordered_map<int, vector<string>> m, const string& temp, int hash){
	auto it = m.find(hash); // find and store the current values at given hash
    if (it != m.end()) { // ensure that the end of map is not being checked
        vector<string>& vec = it->second; // store the current values at given hash
        for (auto iter = vec.begin(); iter != vec.end(); iter++) { // iterate through the vector of strings at hash
            if (*iter == temp) { // if the current element in the vector is found
                vec.erase(iter); // erase the value
                break;
            }
        }
    }
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
	string fileName; // to read in the name of the fileInput from redirected input

	cin >> fileName;
	cout << "Name of fileInput: " << fileName << endl;

	// MAP
	map <int, vector<string> > m1;

	// open a fileName in read mode
	ifstream fI; 
	fI.open(fileName);

	char option;
	string temp;

    // reading and performing operations
    // start timer
	// clock_t start = clock(); 

	while(fI >> option) // while options to insert or remove are read
	{
		fI >> temp; // read the string

		if(option == 'I'){ // if the option is to insert
			int hash = hashFunction(temp); // create hash value
			m1[hash].push_back(temp); // add the string to the vector of strings at given hash value
		} 
		else if(option == 'R'){ // if the option is to remove
			int hash = hashFunction(temp); // create hash value
    		removeMap(m1, temp, hash); // remove the value from the vector of strings at the given hash value
		}
	}

    // stop timer
	// clock_t end = clock();

	// close the opened file
	fI.close();
	// cout << "time for map of size 1000: " << (float)(end - start) / CLOCKS_PER_SEC << endl;
	
	// UNORDERED MAP
	unordered_map<int, vector<string> > m2;
	// open a file again in read mode
	fI.open(fileName);

	// start timer
	//clock_t start2 = clock();

	while(fI >> option) // while operations to insert or remove are read
	{
		fI >> temp; // read the string

		if(option == 'I'){ // if the option is to insert
			int hash = hashFunction(temp); // create hash value
			m2[hash].push_back(temp); // add the string to the vector of strings at given hash value
		} 
		else if(option == 'R'){ // if the option is to remove
			int hash = hashFunction(temp); // create hash value
			removeUnorderedMap(m2, temp, hash); // remove the value from the vector of strings at the given hash value
		}
	}

	//clock_t end2 = clock();
    // stop timer
	// cout << "time for unordered of size 1000: " << (float)(end2 - start2 ) / CLOCKS_PER_SEC << endl;

	// close the opened file
	fI.close();

	displayMap(m1); // display hash map
	displayUnorderedMap(m2); // display unordered map

	return 0;
}
