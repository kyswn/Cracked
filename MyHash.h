
// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(double maxLoadFactor = 0.5)
	{
		numitem = 0;
		numbucket = 100;
		ha = new node*[100];
		for (int i = 0; i < 100; i++)
			ha[i] = nullptr;
		if (maxLoadFactor <= 0) mlf = 0.5;
		else if (maxLoadFactor > 2) mlf = 2;
		else mlf = maxLoadFactor;

	}
	~MyHash()
	{
		for (int i = 0; i < numbucket; i++)
		{   
			node * temp = ha[i];
			while (temp!= nullptr)
			{
				node* tt = temp->next;
				delete temp;
				temp = tt;
			}
		}
		delete []ha;
	}
	void reset()
	{
		for (int i = 0; i < numbucket; i++)
		{
			node * temp = ha[i];
			while (temp != nullptr)
			{
				node* tt = temp->next;
				delete temp;
				temp = tt;
			}
		}
		delete [] ha;
		ha = new node*[100];
		for (int i = 0; i < 100; i++)
			ha[i] = nullptr;
		numbucket = 100;
		numitem = 0;
	}
	void associate(const KeyType& key, const ValueType& value)
	{
		if (find(key) != nullptr)
		{
			*(find(key)) = value;
			return;
		}
		if ((double)(numitem + 1) / numbucket <= mlf)
		{
			numitem++;
			unsigned int hasher(const KeyType& k); // prototype
			unsigned int h = hasher(key);//0-4 billion
			int bucket = h%numbucket;
			if (ha[bucket] == nullptr)
			{
				node *a = new node;
				a->m_kt = key;
				a->m_vt = value;
				a->next = nullptr;
				ha[bucket] = a;
			}
			else
			{
				node* temp = ha[bucket];
				while (temp->next != nullptr)
				{
					temp = temp->next;
				}
				node *a = new node;
				a->m_kt = key;
				a->m_vt = value;
				a->next = nullptr;
				temp->next = a;
			}
		}
		else
		{
			node** temp = new node* [2*numbucket];
			for (int i = 0; i < 2*numbucket; i++)
				temp[i] = nullptr;
			for (int i = 0; i < numbucket; i++)
			{
				if (ha[i] != nullptr)
				{
					node* tt = ha[i];
					while (tt != nullptr)
					{
						//tempassociate(tt->m_kt, tt->m_vt);
						unsigned int hasher(const KeyType& k); // prototype
						unsigned int h = hasher(tt->m_kt);//0-4 billion
						int bucket = h%(numbucket*2);
						if (temp[bucket] == nullptr)
						{
							node *a = new node;
							a->m_kt = tt->m_kt;
							a->m_vt = tt->m_vt;
							a->next = nullptr;
							temp[bucket] = a;
						}
						else
						{
							node* tempp = temp[bucket];
							while (tempp->next != nullptr)
							{
								tempp = tempp->next;
							}
							node *a = new node;
							a->m_kt = tt->m_kt;
							a->m_vt = tt->m_vt;
							a->next = nullptr;
							tempp->next = a;
						}
						tt = tt->next;
					}
				}

			}


			for (int i = 0; i < numbucket; i++)
			{
				node * temp = ha[i];
				while (temp != nullptr)
				{
					node* tt = temp->next;
					delete temp;
					temp = tt;
				}
				
			}
			delete[] ha;
			ha = temp;
			numbucket = numbucket * 2;
			associate(key, value);
			
		}
	}
	int getNumItems() const
	{
		return numitem;
	}
	double getLoadFactor() const
	{
		return (double)numitem / numbucket;
	}

      // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const
	{
		unsigned int hasher(const KeyType& k); // prototype
		unsigned int h = hasher(key);//0-4 billion
		int bucket = h%numbucket;
		if (ha[bucket] == nullptr) return nullptr;
		node* temp = ha[bucket];
		while (temp!= nullptr)
		{
			if (temp->m_kt == key)
			return &(temp->m_vt);
			temp = temp->next;
		}
		return nullptr;
	}

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
	struct node
	{
		KeyType m_kt;
		ValueType m_vt;
		node* next;
	};
	node** ha;
	double mlf;
	int numbucket;
	int  numitem;
};













