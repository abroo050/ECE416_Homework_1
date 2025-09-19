#include <iostream>
#include <string>

using namespace std;

struct element
{
	
element* prev = nullptr;
element* next = nullptr; 

char letter = 'a';

int rownum = 0;
int colnum = 0;	

};

element* createAlphabet();

element* createMatrix();

bool checkKey(element* alphabetHead, string key);

string menuKey(element* alphabetHead);

int main()
{
	
	element* alphabetHead = createAlphabet();
	element* matrixHead = createMatrix();
	bool keyGood = getKey(alphabetHead);
	cout << endl << keyGood;
}

element* createAlphabet()
{
	int i = 0;

	element* e1 = new element;
	element* temp1 = e1;
	
	while(i < 26)
	{
		element* temp = e1; 
		e1->next = new element;
		e1->letter = 'A' + i;
		cout << e1->letter << endl;
		e1 = e1->next;
		e1->prev = temp;
		i++;	
	}
	
	
	return temp1;
}

element* createMatrix()
{
	int i = 0;

	element* e1 = new element;
	element* temp1 = e1;
	
	while(i < 25)
	{
		element* temp = e1;
		e1->rownum = (i % 5) + 1;
		e1->colnum = (i/5) + 1;
		e1->next = new element;
		e1->letter = 'b';
		cout << e1->letter << " " << e1->rownum << " " << e1->colnum << endl;
		e1 = e1->next;
		e1->prev = temp;
		i++;
	}
	delete e1;
	
	return temp1;
}

void menuKey(element* alphabetHead)

       string key = "";
        
       cout << "Please enter key: ";
       cin >> key;

	while(!checkKey(alphabetHead))
	{
		cout << endl << Invalid Key! Can not include spaces, non capital alphabet, or be longer than 25 characters!" << endl;
	}
	


}

bool checkKey(element* alphabetHead, string key)
{
	bool verified = false;
	
	element* temp = alphabetHead;
	
	string key;
	getline(cin, key);
	
	int i = 0;
	
	if(key.length() > 25)
	{
		return 0;
	}
	
	while(i < key.length())
	{
		int j = 0;
		verified = false;
		alphabetHead = temp;
		while(j < 26)
		{
			if(key[i] == alphabetHead->letter)
			{
				verified = true;
			}
			alphabetHead = alphabetHead->next;
	                j++;
          	}
		if(!verified)
		{
			return 0;
		}
		i++;
	}
	return 1;
}
