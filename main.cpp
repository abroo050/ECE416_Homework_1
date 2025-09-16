#include <iostream>
#include <string>

using namespace std;

struct holder
{
	
holder* prev = nullptr;
int current = 0;
holder* next = nullptr; 	

};

holder* createMatrix();

int main()
{
holder* h1 = new holder;
 	
}

holder* createMatrix()
{
	int i = 0;

	while(i < 25)
	{
		holder* h1 = new holder;
		holder* temp = h1;
		h1->next = new holder;
		h1->current = i;
		cout << h1->current << endl;
		h1 = h1->next;
		h1->prev = temp;
		i++;
	}
	delete h1;	
}
	