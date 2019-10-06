#include "provided.h"
#include <string>
#include "MyHash.h"
using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl();
	~TranslatorImpl();
	bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
	struct node
	{
		MyHash<char, char> zheng;
		MyHash<char, char> fan;
		node* next;
	};
	node* head;

};

TranslatorImpl::TranslatorImpl()
{

	head = new node;
	//for (int i = 0; i < 26; i++)
	//{
	//	head->zheng.associate('a' + i, '?');
	//}
	head->next = nullptr;
}

TranslatorImpl::~TranslatorImpl()
{
	node* temp = head;
	while (temp->next != nullptr)
	{
		node* a = temp->next;
		delete temp;
		temp = a;
	}
	delete temp;

}


bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	if (ciphertext.size() != plaintext.size())
		return false;
	for (int i = 0; i < ciphertext.size(); i++)
	{
		if (!isalpha(ciphertext[i]))
			return false;
	}
	for (int i = 0; i < plaintext.size(); i++)
	{
		if (!isalpha(plaintext[i]))
			return false;
	}
	for (int i = 0; i < ciphertext.size(); i++)
	{
		ciphertext[i] = tolower(ciphertext[i]);
	}
	for (int i = 0; i < plaintext.size(); i++)
	{
		plaintext[i] = tolower(plaintext[i]);
	}

	node* temp = head;
	while (temp->next != nullptr)
		temp = temp->next;

	//check for inconsistence
	for (int i = 0; i < ciphertext.size(); i++)
	{
		if (temp->zheng.find(ciphertext[i]) != nullptr&& *(temp->zheng.find(ciphertext[i])) != plaintext[i]) return false;
		else if (temp->fan.find(plaintext[i]) != nullptr&&*(temp->fan.find(plaintext[i])) != ciphertext[i]) return false;
	}
		
	node* jia = new node;
	temp->next = jia;
	jia->next = nullptr;
	//copy temp to jia
	for (int j = 0; j < 26; j++)
	{
		if (temp->zheng.find('a' + j) != nullptr)
		{
		   jia->zheng.associate('a' + j, *(temp->zheng.find('a' + j)));
			jia->fan.associate(*(temp->zheng.find('a' + j)), 'a' + j);
		}
	 }
	//add new things in		
	for (int i = 0; i < ciphertext.size(); i++)
	{
		jia->zheng.associate(ciphertext[i], plaintext[i]);
		jia->fan.associate(plaintext[i], ciphertext[i]);
	}
	return true;
	
	
	}



bool TranslatorImpl::popMapping()
{
	if (head->next == nullptr)
		return false;
	node* temp = head;
	while (temp->next->next != nullptr)
	{
		temp = temp->next;
	}
	delete temp->next;
	temp->next = nullptr;
	return true;

}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	node* current = head;
	while (current->next!= nullptr)
		current = current->next;
	string bian = ciphertext;//make a copy
	string a = "";
	for (int i = 0; i < bian.size(); i++)
	{
		if (!isalpha(bian[i])) a = a + ciphertext[i];
		else
		{
			bool da = isupper(bian[i]);
			bian[i] = tolower(bian[i]);
			if (current->zheng.find(bian[i]) != nullptr)
			{
				if (da == true)
				{
					char temp = toupper(*(current->zheng.find(bian[i])));
					a = a + temp;
				}
				else
				{
					char temp = *(current->zheng.find(bian[i]));
					a = a + temp;
				}
			}
			else a = a + '?';
		}
	}
	return a;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
