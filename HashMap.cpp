#include <iostream>
#include "HashMap.h"

void Iterator::operator++()//
{
	//check to see if index is size array 

	if (current != nullptr && current->next != nullptr)
	{
		current = current->next;
		return;
		//check the chained list
		current = hashArray[index];
	}
	else
	{
		while (++index < sizeOfArray && hashArray[index] == nullptr)
		{
			;
		}
		if (index == sizeOfArray)
		{
			current = nullptr;
			return;
		}
		else
		{
			current = hashArray[index];
			return;
		}

	}
}

Iterator::Iterator(int index, Node** hashArray, int sizeOfArray)// external iterator to iterate over the HashMap
{
	current = hashArray[index];
	this->index = index;
	this->hashArray = hashArray;
	this->sizeOfArray = sizeOfArray;

	if (hashArray[index] == nullptr)
	{
		++(*this);
	}
	if (index == sizeOfArray)
	{
		current = nullptr;
	}

	/*while (this->index < sizeOfArray && this->hashArray[this->index] == nullptr)
	{
		this->index++;
		if (this->index = sizeOfArray)
		{
			current = nullptr;
		}
		else
		{
			current = hashArray[this->index];
		}
	}*/
}

Iterator::Iterator()
{
	this->index = 0;
	this->sizeOfArray = 0;
	this->current = nullptr;
	this->hashArray = nullptr;
}


HashMap::HashMap(int size) // size of array 500 //do I need to assign all values in node?
{
	hashArray = new Node * [size];
	for (int i = 0; i < size; i++)
	{
		hashArray[i] = nullptr;
	}
	sizeOfArray = size;

}

HashMap::~HashMap()//
{
	int i = 0;
	Node* head = hashArray[i];//initialize to beginning of list
	while (i < sizeOfArray)
	{
		while (head != nullptr)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		i++;
	}
	delete[] hashArray;//must also delete the nodes
}

bool HashMap::IsKeyPresent(string const& key) const //is this correct?
{
	int index = GenerateHash(key);

	Node* ptr = hashArray[index];
	//search for  the index
	for (int i = 0; i < sizeOfArray; i++)//iterate through the array of linked lists
	{
		//check for Nullptr in the array
		while (ptr != nullptr)
		{
			//go into the chained list and check for the key
			if (ptr->key == key)//check if its a match reutrn true
			{
				return true;
			}
			else//move to next in chain
			{
				ptr = ptr->next;
			}
		}
	}
	//check for NULL at end of array?
	return false;
}

void HashMap::SetKeyValue(string const& key, int value) //insert into the the array
{
	int index = GenerateHash(key);
	Node* ptr = hashArray[index];
	//check for null

	while (ptr != nullptr)
	{
		//occupied key
		if (ptr->key == key)
		{
			ptr->value = value;
			return;
		}
		//not occupied key
		else
		{
			ptr = ptr->next;
		}
	}
	//key doesn't exist
	Node* temp = new  Node(key, value, hashArray[index]);
	hashArray[index] = temp;
}

bool HashMap::GetKeyValue(string const& key, int& value) // if key is not present, return false
{
	int index = GenerateHash(key);

	Node* ptr = hashArray[index];
	while (ptr != nullptr)
	{
		if (key == ptr->key)
		{
			value = ptr->value;
			return true;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	//if key is not present, return false
	return false;
}

int HashMap::GenerateHash(string key) const // converts the key to an value used to index into the array
{
	int hash = 0;
	int index = 0;

	for (size_t i = 0; i < key.length(); i++)
	{
		hash = hash + (int)key[i];
	}
	index = (hash * 3) % sizeOfArray;
	return index;
}

Iterator HashMap::begin()
{
	return Iterator(0, hashArray, sizeOfArray);
}

Iterator HashMap::end()
{
	return Iterator(sizeOfArray, hashArray, sizeOfArray);
}

bool Iterator::is_item()
{
	//return true if node is present
	if (current != nullptr)
	{
		return true;
	}
	return false;
}

string Iterator::operator*()
{
	if (current != nullptr)
	{
		return current->key;
	}
	else
	{
		return string();
	}
}



bool Iterator::operator!=(Iterator& other)//if not equal return true //??
{
	if (current != other.current)//not sure what I want to compare here
	{
		return true;
	}
	return false;
}