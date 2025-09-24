/*
GITHUB LINK: https://github.com/abroo050/ECE416_Homework_1.git
*/

#include <iostream>
#include <string>

using namespace std;

struct element
{
	
element* prev = nullptr;
element* next = nullptr; 

char letter = 'a';

int row = 0;
int col = 0;	

};

element* createAlphabet();

element* createMatrix();

bool checkKey(element* alphabetHead, string key);

string getKey(element* alphabetHead);

bool contains(element* head, char ch);

void append(element*& head, element*& tail, char ch);

void deleteList(element* head);

string stripKey(string key);

void fillMatrix(element* matrixHead, const string& key, element* alphabetHead);

void displayMatrix(element* matrixHead);

string getMessage();

string encryptMessage(const string& message, element* matrix);

string encryptPair(char a, char b, element* matrix);

string decryptMessage(const string& encrypted, element* matrix);

string decryptPair(char a, char b, element* matrix);

element* findLetterByCoords(element* matrix, int row, int col);

element* findLetter(element* matrix, char ch);

int main()
{
	int choice = 0;
	
	bool lcv = true;
	
	string key = "";
	string message = "";
	
	element* alphabetHead = createAlphabet();
	element* matrixHead = createMatrix();
	
	cout << "Welcome to Playfair Cipher Encrypt and Decrypt!" << endl << endl << "Created by Austin Broome for ECE416" << endl << endl;
	
	while(lcv)
	{
	cout << "What would you like to do?" << endl;
	cout << "0) Quit" << endl << "1) Decrypt" << endl << "2) Encrypt" << endl << "Your Choice:";
	
	cin >> choice;
	
	cin.clear();                
	cin.ignore(10000, '\n');     

	switch(choice)
	{
	case 0:
	lcv = false;
	break;
	case 1:
	key = getKey(alphabetHead);
	fillMatrix(matrixHead, key, alphabetHead);
	displayMatrix(matrixHead);
	message = getMessage();
	cout << endl << "Decrypted Message: " << decryptMessage(message, matrixHead) << endl << endl;
	break;
	case 2:
	key = getKey(alphabetHead);
	fillMatrix(matrixHead, key, alphabetHead);
	displayMatrix(matrixHead);
	message = getMessage();
	cout << endl << "Encrypted Message: " << encryptMessage(message, matrixHead) << endl << endl;
	break;
	default:
	cout << endl << "Invalid Choice!" << endl;
	break;
	}
	}
	
	deleteList(alphabetHead);
	deleteList(matrixHead);

}

element* createAlphabet()
{
    element* head = new element;
    head->letter = 'A';

    element* current = head;
    for (int i = 1; i < 26; ++i)
    {
        current->next = new element;
        current->next->prev = current;
        current = current->next;
        current->letter = 'A' + i;
    }

    return head;
}

element* createMatrix()
{
    element* head = new element;
    element* current = head;

    for (int i = 1; i < 25; ++i)
    {
        current->next = new element;
        current->next->prev = current;
        current = current->next;
    }

    current = head;
    int index = 0;
    while (current != nullptr && index < 25)
    {
        current->row = index / 5;  
        current->col = index % 5;  
        current = current->next;
        index++;
    }

    return head;
}

bool checkKey(element* alphabetHead, string key)
{
	bool verified = false;
	
	element* temp = alphabetHead;
	
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
			return false;
		}
		i++;
	}
	return true;
}

string getKey(element* alphabetHead)
{
    string key = "";
    bool lcv = false;    
		
    cout << "Please enter key: ";
    getline(cin, key);

	while(!lcv)
	{
		lcv = checkKey(alphabetHead, key);
		if(!lcv)
		{
			cout << endl << "Invalid Key! Must be capital letters and be shorter than 25 characters!" << endl << endl << "Please enter key: ";
			getline(cin, key);
		}
	}
	
	key = stripKey(key);
	
	return key;
	
}

bool contains(element* head, char ch)
{
    element* current = head;
    while (current != nullptr) 
	{
        if (current->letter == ch)
            return true;
        current = current->next;
    }
    return false;
}

void append(element*& head, element*& tail, char ch)
{
    
	element* newElem = new element;
    newElem->letter = ch;

    if (head == nullptr) 
	{
        head = tail = newElem;
    } 
	else 
	{
        tail->next = newElem;
        newElem->prev = tail;
        tail = newElem;
    }
}

void deleteList(element* head) 
{
    while (head != nullptr) 
	{
        element* temp = head;
        head = head->next;
        delete temp;
    }
}

string stripKey(string key) {
    
	element* head = nullptr;
    element* tail = nullptr;

    for (char ch : key) {
        if (!contains(head, ch)) 
		{
			append(head, tail, ch);
        }
    }

    string result;
    element* current = head;
    
	while (current != nullptr) 
	{
        result += current->letter;
        current = current->next;
    }

    deleteList(head);

    return result;
}

void fillMatrix(element* matrixHead, const string& key, element* alphabetHead) 
{
    element* current = matrixHead;

    for (char ch : key) {
        if (current != nullptr) {
            current->letter = ch;
            current = current->next;
        }
    }
	
    for (element* a = alphabetHead; a != nullptr && current != nullptr; a = a->next) {

        bool found = false;
        for (char ch : key) {
            if (a->letter == ch) {
                found = true;
                break;
            }
        }

        if (a->letter == 'J')
            continue;

        if (!found) {
            current->letter = a->letter;
            current = current->next;
        }
    }
}

void displayMatrix(element* matrixHead)
{
	
	cout << endl;
	
    element* current = matrixHead;
    int count = 0;

    while (current != nullptr && count < 25) {
        cout << current->letter << " ";
        count++;
        current = current->next;

        if (count % 5 == 0)
            cout << endl;
    }
	cout << endl;
}

string getMessage()
{
    string input;
    bool valid = false;

    while (!valid)
    {
        cout << "Enter message to decode/encode: ";
        getline(cin, input);

        valid = true;
        for (char ch : input)
        {
            if (ch < 'A' || ch > 'Z')
            {
                valid = false;
                cout << "Invalid input! Only uppercase alphabet is allowed" << endl << endl;
                break;
            }
        }
    }

    string prepared = "";
    for (int i = 0; i < input.length(); )
    {
        char first = input[i];
        char second;

        if (i + 1 < input.length())
        {
            second = input[i + 1];
            if (first == second)
            {
                prepared += first;
                prepared += 'X';
                i += 1;
            }
            else
            {
                prepared += first;
                prepared += second;
                i += 2;
            }
        }
        else
        {
            prepared += first;
            prepared += 'X';
            i += 1;
        }
    }

    return prepared;
}

string encryptMessage(const string& message, element* matrix)
{
    string encrypted = "";

    for (int i = 0; i < message.length(); i += 2)
    {
        string pair = encryptPair(message[i], message[i + 1], matrix);
        encrypted += pair;
    }

    return encrypted;
}


string encryptPair(char a, char b, element* matrix)
{
    element* first = findLetter(matrix, a);
    element* second = findLetter(matrix, b);

    if (!first || !second)
        return string() + a + b; 

    if (first->row == second->row)
    {
        int row = first->row;
        int col1 = (first->col + 1) % 5;
        int col2 = (second->col + 1) % 5;

        char newA = findLetterByCoords(matrix, row, col1)->letter;
        char newB = findLetterByCoords(matrix, row, col2)->letter;
        return string() + newA + newB;
    }

    else if (first->col == second->col)
    {
        int col = first->col;
        int row1 = (first->row + 1) % 5;
        int row2 = (second->row + 1) % 5;

        char newA = findLetterByCoords(matrix, row1, col)->letter;
        char newB = findLetterByCoords(matrix, row2, col)->letter;
        return string() + newA + newB;
    }

    else
    {
        char newA = findLetterByCoords(matrix, first->row, second->col)->letter;
        char newB = findLetterByCoords(matrix, second->row, first->col)->letter;
        return string() + newA + newB;
    }
}

string decryptMessage(const string& encrypted, element* matrix)
{
    string decrypted = "";

    for (int i = 0; i < encrypted.length(); i += 2)
    {
        decrypted += decryptPair(encrypted[i], encrypted[i + 1], matrix);
    }

    return decrypted;
}


string decryptPair(char a, char b, element* matrix)
{
 
    element* first = findLetter(matrix, a);
    element* second = findLetter(matrix, b);

    if (!first || !second) 
        return "";  

    string result = "";

    if (first->row == second->row)
    {
        
        int newCol1 = (first->col + 4) % 5; 
        int newCol2 = (second->col + 4) % 5;

        element* firstNew = findLetterByCoords(matrix, first->row, newCol1);
        element* secondNew = findLetterByCoords(matrix, second->row, newCol2);

        result += firstNew->letter;
        result += secondNew->letter;
    }
    else if (first->col == second->col)
    {
        
        int newRow1 = (first->row + 4) % 5;
        int newRow2 = (second->row + 4) % 5;

        element* firstNew = findLetterByCoords(matrix, newRow1, first->col);
        element* secondNew = findLetterByCoords(matrix, newRow2, second->col);

        result += firstNew->letter;
        result += secondNew->letter;
    }
    else
    {
       
        element* firstNew = findLetterByCoords(matrix, first->row, second->col);
        element* secondNew = findLetterByCoords(matrix, second->row, first->col);

        result += firstNew->letter;
        result += secondNew->letter;
    }

    return result;
}

element* findLetterByCoords(element* matrix, int row, int col)
{
    element* current = matrix;

    while (current != nullptr)
    {
        if (current->row == row && current->col == col)
            return current;

        current = current->next;
    }

    return nullptr;
}

element* findLetter(element* matrix, char ch)
{
    element* current = matrix;
    while (current != nullptr)
    {
        if (current->letter == ch)
            return current;
        current = current->next;
    }
    return nullptr;
}
