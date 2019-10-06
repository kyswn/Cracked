#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
#include "MyHash.h"

using namespace std;


const string WORDLIST_FILE = "wordlist.txt";
/*
string encrypt(string plaintext)
{
	  // Generate a to z
    char plaintextAlphabet[26+1];
	iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
	plaintextAlphabet[26] = '\0';

	  // Generate permutation
	string ciphertextAlphabet(plaintextAlphabet);
	default_random_engine e((random_device()()));
	shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);

	  // Run translator (opposite to the intended direction)
	Translator t;
	t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
	return t.getTranslation(plaintext);
}

bool decrypt(string ciphertext)
{
	Decrypter d;
	if ( ! d.load(WORDLIST_FILE))
	{
		cout << "Unable to load word list file " << WORDLIST_FILE << endl;
		return false;
	}
	for (const auto& s : d.crack(ciphertext))
		cout << s << endl;
	return true;
}

int main(int argc, char* argv[])
{
	if (argc == 3  &&  argv[1][0] == '-')
	{
		switch (tolower(argv[1][1]))
		{
		  case 'e':
			cout << encrypt(argv[2]) << endl;
			return 0;
		  case 'd':
			if (decrypt(argv[2]))
				return 0;
			return 1;
		}
	}

	cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
	cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
	return 1;
}

*/
int main()
{
	Decrypter a;
	a.load("C:/Users/surface/Desktop/cs32/project 4/skeleton/wordlist.txt");
	vector<string> b=a.crack("Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. -Rcmcy Xcmmcn");
	for (int i = 0; i < b.size(); i++)
		cout<< b[i]<<endl;
}

