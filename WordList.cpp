#include "provided.h"
#include <string>
#include <vector>
#include "MyHash.h"
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

class WordListImpl
{
public:
	bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;


	
private:
	MyHash<string, vector<string>> m_mh;
	string makepattern(string s) const;
	bool checkstring(string s) const;
	bool checktrans(string lowerplain, string lowertrans) const;
};

bool  WordListImpl::checktrans(string lowerplain, string lowertrans) const
{
	for (int i = 0; i < lowerplain.size(); i++)
	{
		if (isalpha(lowertrans[i]))
		{
			if (lowertrans[i] != lowerplain[i])
				return false;
		}
		else if (lowertrans[i] == '?')
		{
			if (!isalpha(lowerplain[i]))
				return false;
		}
		else if (lowertrans[i] == '\'')
		{
			if (lowerplain[i] != '\'')
				return false;
		}
	}
	return true;
}
string WordListImpl::makepattern(string s) const //to lower case
{

	string pattern = "";
	int index = 0;
	int i = 1, j = 0;
	if (s.size() == 0) return pattern;
	for (int i = 0; i<s.size(); i++)
	{
		if(isalpha(s[i]))
		s[i] = tolower(s[i]);
	}
	pattern += '0';
	index++;
	for (i = 1; i < s.size(); i++)
	{
		for (j = 0; j < i; j++)
		{
			if (s[i] == s[j])
			{
				pattern += pattern[j];
				break;
			}
		}
		if (j == i)
		{
			char ch = '0' + index;
			pattern = pattern + ch;
			index++;
		}
	}
	return pattern;//is like 0011222
}

bool WordListImpl::checkstring(string s) const
{
	for (int i = 0; i < s.size(); i++)
	{
		if ((!isalpha(s[i])) && (s[i] != '\''))
			return false;
	}
	return true;
}

bool WordListImpl::loadWordList(string filename)
{
	m_mh.reset();
	ifstream infile(filename);    // infile is a name of our choosing
	if (!infile)		        // Did opening the file fail?
		return false;
	std::string s;
	// getline returns infile; the while tests its success/failure state
	while (getline(infile, s))
	{
		if (checkstring(s))
		{
			for (int i = 0; i < s.size(); i++)
			{
				if (isalpha(s[i]))
					s[i] = tolower(s[i]);
			}
			string p = makepattern(s);
			if (m_mh.find(p) != nullptr)
			{
				m_mh.find(p)->push_back(s);
			}

			else
			{
				vector<string> vs;
				vs.push_back(s);
				m_mh.associate(p, vs);
			}
		}

	}
	return true;

}

bool WordListImpl::contains(string word) const
{
	for (int i = 0; i < word.size(); i++)
	{
		if (isalpha(word[i]))
		word[i] = tolower(word[i]);
	}
	string s = makepattern(word);
	const vector<string>* temp = m_mh.find(s);
	if (temp == nullptr) return false;
	else {
		for (int i = 0; i <temp->size(); i++)
		{
			if ((*temp)[i] == word)
				return true;
		}
		return false;
	}

}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	vector<string> a;
	if (cipherWord.size() != currTranslation.size()) return a;
	if (!checkstring(cipherWord)) return a;
	for (int i = 0; i < currTranslation.size(); i++)
	{
		if ((!isalpha(currTranslation[i])) && (currTranslation[i] != '\'') && (currTranslation[i] != '?'))
			return a;
	}
	string s = makepattern(cipherWord);
	for (int i = 0; i < currTranslation.size(); i++)
	{
		if (isalpha(currTranslation[i]))
			currTranslation[i] = tolower(currTranslation[i]);
	}
	const vector<string>* temp = m_mh.find(s);
	if (temp == nullptr) return a;

	



	for (int i = 0; i < temp->size(); i++)
	{
		if (checktrans((*temp)[i],currTranslation))
			a.push_back((*temp)[i]);
	}

	return a;
}

//***** hash functions for string, int, and char *****

unsigned int hasher(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hasher(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hasher(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
