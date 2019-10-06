#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
	Translator trans;
	WordList wl;
	void Crack(string ciphertext_message, vector<string>& output);
	bool fulltransed(string s)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '?') return false;
		}
		return true;
	}
	vector<string> result;
};

bool DecrypterImpl::load(string filename)
{
	return(wl.loadWordList(filename));
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	vector<string> tokenized;
	
		for (int i = 0; i < ciphertext.size(); i++)
		{
			if ((!isalpha(ciphertext[i])) && ciphertext[i] != ' '&&ciphertext[i] != ','&&ciphertext[i] != ';'
				&&ciphertext[i] != ':'&&ciphertext[i] != '.'&&ciphertext[i] != '!'&&ciphertext[i] != '('
				&&ciphertext[i] != ')'&&ciphertext[i] != '['&&ciphertext[i] != ']'
				&&ciphertext[i] != '{'&&ciphertext[i] != '}'&&ciphertext[i] != '-'
				&&ciphertext[i] != '\"'&&ciphertext[i] != '#'&&ciphertext[i] != '$'
				&&ciphertext[i] != '%'&&ciphertext[i] != '^'&&ciphertext[i] != '&'
				&&ciphertext[i] != '\'' && (!isdigit(ciphertext[i])))
				return tokenized;
		}

	Tokenizer token(",;:.!()[]{}-\"#$%^&0123456789 ");
	tokenized= token.tokenize(ciphertext);

	Crack(ciphertext, tokenized);
	if (result.size() == 0) return result;
	else sort(result.begin(), result.end());
	vector<string> loc = result;
	while (!result.empty()) result.pop_back();
	return loc;
}


void DecrypterImpl::Crack(string ciphertext_message, vector<string>& tokenied )
{
	vector<string> copy = tokenied;
	for (int i = 0; i < copy.size(); i++)
	{
		copy[i]=trans.getTranslation(copy[i]);
	}
	
	int most = 0; int index = 0;
	for (int i = 0; i < copy.size(); i++)
	{
		int wenhao = 0;
		for (int j = 0; j < copy[i].size(); j++)
		{
			if (copy[i][j] == '?') wenhao++;
		}
		if (wenhao >= most)
		{
			most = wenhao;
			index = i;
		}
	}
	vector<string> possible = wl.findCandidates(tokenied[index], copy[index]);
	
	if (possible.size() == 0)
	{
		trans.popMapping();
		return;
	}//kenengyouwenti

	for (int i = 0; i < possible.size(); i++)
	{
		bool guo = false;
		if (!trans.pushMapping(tokenied[index], possible[i]))
			continue;
		vector<string> partdone = tokenied;
		for (int j = 0; j < tokenied.size(); j++)
		{
			partdone[j] = trans.getTranslation(partdone[j]);
		}
		int fully = 0;
		int notfully = 0;
		for (int j = 0; j < partdone.size(); j++)
		{
			if (fulltransed(partdone[j])) fully++;
			else notfully++;
		}
		for (int j = 0; j < partdone.size(); j++)
		{
			if (fulltransed(partdone[j])) 
				if (!wl.contains(partdone[j]))
				{
					trans.popMapping();
					guo = true;
					break;
				}

		}
		if (guo == true) continue;
		if (notfully > 0)
		{
			
			
			Crack(ciphertext_message, tokenied);


		}
		////////////////
		else {
			string s = trans.getTranslation(ciphertext_message);
			result.push_back(s);
			trans.popMapping();
		}
		
	}
	trans.popMapping();
	
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
