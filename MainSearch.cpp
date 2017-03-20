#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <random>
#include "wordSearch.h"

using namespace std;

bool addWordFile(WordSearch& inWordSearch,const string inFile,const int inSeed,const int maxWords = 50);

int main()
{
	random_device rd;
	int seed = rd();
	seed = 2442;
	WordSearch* myWordSearch = new WordSearch(20,20,seed);
	addWordFile(*myWordSearch,"words.txt",seed,5);
	myWordSearch->checkForMatch(2,0,2,9);
	myWordSearch->checkForMatch(1,3,4,4);
	myWordSearch->complete();
	myWordSearch->print();
	
	return 0;
}




bool addWordFile(WordSearch& inWordSearch,const string inFile,const int inSeed,const int maxWords)
{
	list<string> wordList;
	list<string>::iterator iter;
	int randomValue = 0;
	default_random_engine generator(inSeed);
	
	string line;
	ifstream myFile(inFile);
	if(myFile.is_open())
	{
		while(getline(myFile,line))
		{
			transform(line.begin(), line.end(), line.begin(), ::toupper);
			wordList.push_back(line);
		}
		int wordListSize = wordList.size();
		for(int j = 0;j < maxWords && j < wordListSize;j++)
		{
			uniform_int_distribution<int> distribution(0,wordList.size()-1);
			randomValue = distribution(generator);
			iter = wordList.begin();
			for(int i = 0;i < randomValue;i++)
			{
				iter++;
			}
			inWordSearch.addWord(*iter);
			wordList.erase(iter);
		}
		
	}
	return true;
}
