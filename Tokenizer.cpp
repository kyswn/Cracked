#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
	vector<char> m_separators;
	bool isinvector(char a, vector<char> b) const
	{
		if (b.size() == 0) return false;
		for (int i = 0; i < b.size(); i++)
		{
			if (a == b[i]) return true;
		}
		return false;
	}
};

TokenizerImpl::TokenizerImpl(string separators)
{
	for (int i = 0; i < separators.size(); i++)
	{
		m_separators.push_back(separators[i]);
	}
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
	vector<string> a;
	if (s.size() == 0) return a;
	for (int i = 0, j = 0; i < s.size(), j <= s.size(); j++)//i would be start and j would be end
	{
		if (j == s.size()||isinvector(s[j], m_separators))
		{
			if(i!=j) 
			a.push_back(s.substr(i, j-i));
			i = j + 1;
		}
	}
	return a;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}
