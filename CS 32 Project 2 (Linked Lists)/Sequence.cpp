#include "Sequence.h"
Sequence::Sequence()
{
	//cerr << "Constructed" << endl;
	m_head = new Node; //declaring the head pointer pointing to the dummy node
	m_size = 0; // circularly linked; dummy node does not add to size
	//m_pos and m_data are not assigned, the first node to get this will be m_head->m_next
	m_head->m_next = m_head; //dummy node connects back to itself originally
	m_head->m_previous = m_head; //same as above

};
Sequence::~Sequence()
{
	int counter = -1; //counting the dummy node as -1 so the first real node will be at position 0
	Node* tmp2 = m_head->m_previous;
	for (Node* tmp = m_head->m_next; tmp != m_head->m_previous; tmp = tmp->m_next)
	{
		
		delete tmp->m_previous;
		//cerr << "deleted node" << counter;
		counter++;

		if (counter == this->size() - 1) //you've reached the last node!
		{
			delete tmp2;
			//cerr << "last node was destroyed" << endl;
		}
	}
	//cerr << "destructed" << endl;
}
Sequence::Sequence(const Sequence &other)
{
	//cerr << "Constructed" << endl;
	m_head = new Node; //declaring the head pointer pointing to the dummy node
	m_size = 0; // circularly linked; dummy node does not add to size
	//m_pos and m_data are not assigned, the first node to get this will be m_head->m_next
	m_head->m_next = m_head; //dummy node connects back to itself originally
	m_head->m_previous = m_head; //same as above
	for (int i = 0; i < other.size(); i++)
	{
		ItemType x;
		other.get(i, x);
		this->insert(i, x);
	}
}
Sequence& Sequence::operator=(Sequence rhs)
{
	rhs.swap(*this);
	return *this;
}
bool Sequence::empty() const
{
	if (size() == 0)
		return true;
	return false;
};
int Sequence::size() const
{
	return m_size;
};
bool Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > size())
	{
		cerr << "Attempting to insert outside the bounds of the currently existing list." << endl;
		return false;
	}
	//first create a node containing the data within the argument passed
	Node* tmp = new Node;
	tmp->m_data = value;
	tmp->m_position = pos;
	if (size() == 0)
	{
		m_head->m_next = tmp;
		m_head->m_previous = tmp;
		tmp->m_next = m_head;
		tmp->m_previous = m_head;
		tmp->m_position = 0;
		m_size++;
		tmp->m_position = 0;
		return true;
	}
	Node* pos_finder; //will go through the list, searching for the first position == to the value passed
	for (pos_finder = m_head->m_next; pos_finder != m_head && pos_finder->m_position <= pos; pos_finder = pos_finder->m_next)
	{
		if (pos_finder->m_position == pos)
			break;
		;
	} //the loop will break with pos_finder either pointing to the dummy node(pos_finder = head) or with pos_finder 
	//pointing to the node that has the m_data larger than the value passed
	if (pos_finder == m_head->m_next) //the first node in the list had a larger value. now inserting between head and previous 1st node
	{
		tmp->m_next = pos_finder;
		tmp->m_previous = m_head;
		m_head->m_next = tmp;
		tmp->m_next->m_previous = tmp;
		m_size++;
		tmp->m_position = 0; //this is the new first node
		//now must execute a for loop to update position of subsequent nodes
		for (Node* pos_updater = tmp->m_next; pos_updater != m_head; pos_updater = pos_updater->m_next)
		{
			pos_updater->m_position++;
		}
		return true;
	}
	if (pos_finder == m_head) //we know that nothing in the list had an m_pos larger than the value passed, therefore it will be inserted at the end
	{
		tmp->m_next = m_head; //last element's next links to head
		tmp->m_previous = m_head->m_previous; //the element head is connected to now will be the 2nd to last element
		tmp->m_previous->m_next = tmp; //the element preceding the last element must connect to the last element via it's next pointer
		m_head->m_previous = tmp; //head links back to last element
		m_size++;
		tmp->m_position = tmp->m_previous->m_position + 1; //just increment the previous last node's position
		return true; //yet to be implemented
	}
	//not a special case, just being inserted between 2 already existing nodes
	tmp->m_next = pos_finder;
	tmp->m_previous = pos_finder->m_previous;		//the insertion code
	tmp->m_next->m_previous = tmp;
	tmp->m_previous->m_next = tmp;
	tmp->m_position = tmp->m_next->m_position;
	//now increment subsequent node positions
	for (Node* pos_updater = tmp->m_next; pos_updater != m_head; pos_updater = pos_updater->m_next)
	{
		pos_updater->m_position++;
	}
	m_size++;
	return true;
};
bool Sequence::insert(const ItemType& value)
{
	//first create a node containing the data within the argument passed
	Node* tmp = new Node;
	tmp->m_data = value;
	if (size() == 0)
	{
		m_head->m_next = tmp;
		m_head->m_previous = tmp;
		tmp->m_next = m_head;
		tmp->m_previous = m_head;
		tmp->m_position = 0;
		m_size++;
		tmp->m_position = 0;
		return true;
	}
	Node* val_finder; //will go through the list, searching for the first value >= to the value passed
	for (val_finder = m_head->m_next; val_finder != m_head && val_finder->m_data <= value; val_finder = val_finder->m_next)
	{
		; 
	} //the loop will break with val_finder either pointing to the dummy node(val_finder = head) or with val_finder 
	  //pointing to the node that has the m_data larger than the value passed
	if (val_finder == m_head->m_next) //the first node in the list had a larger value. now inserting between head and previous 1st node
	{
		tmp->m_next = val_finder;
		tmp->m_previous = m_head;
		m_head->m_next = tmp;
		tmp->m_next->m_previous = tmp;
		m_size++;
		tmp->m_position = 0; //this is the new first node
		//now must execute a for loop to update position of subsequent nodes
		for (Node* pos_updater = tmp->m_next; pos_updater != m_head; pos_updater = pos_updater->m_next)
		{
			pos_updater->m_position++;
		}
		return true;
	}
	if (val_finder == m_head) //we know that nothing in the list had an m_data larger than the value passed, therefore it will be inserted at the end
	{
		tmp->m_next = m_head; //last element's next links to head
		tmp->m_previous = m_head->m_previous; //the element head is connected to now will be the 2nd to last element
		tmp->m_previous->m_next = tmp; //the element preceding the last element must connect to the last element via it's next pointer
		m_head->m_previous = tmp; //head links back to last element
		m_size++;
		tmp->m_position = tmp->m_previous->m_position + 1; //just increment the previous last node's position
		return true; //yet to be implemented
	}
	//not a special case, just being inserted between 2 already existing nodes
	tmp->m_next = val_finder;
	tmp->m_previous = val_finder->m_previous;		//the insertion code
	tmp->m_next->m_previous = tmp;
	tmp->m_previous->m_next = tmp;
	tmp->m_position = tmp->m_next->m_position;
	//now increment subsequent node positions
	for (Node* pos_updater = tmp->m_next; pos_updater != m_head; pos_updater = pos_updater->m_next)
	{
		pos_updater->m_position++;
	}
	m_size++;
	return true;
};
bool Sequence::erase(int pos)
{
	if (pos < 0 || pos >= size() || size() == 0)
	{//invalid positions or nothing to delete
		cerr << "Error in deletion: Either out of bounds or nothing to delete.";
		return false;
	}
	Node* pos_finder;
	for (pos_finder = m_head->m_next; pos_finder != m_head; pos_finder = pos_finder->m_next)
	{
		if (pos_finder->m_position == pos)
			break;
	}
	//At this point pos_finder is either pointing to the node needing to be deleted, or
	//If nothing matches that position(which should never occur due to the initial checks), 
	//it's pointing to the same place as m_head
	
	//Now rearranging the pointers
	pos_finder->m_next->m_previous = pos_finder->m_previous;
	pos_finder->m_previous->m_next = pos_finder->m_next;
	Node* pos_updater;
	for (pos_updater = pos_finder->m_next; pos_updater != m_head; pos_updater = pos_updater->m_next)
	{
		pos_updater->m_position--;
	}
	delete pos_finder; //deletes the node, freeing up space again
	m_size--;
	return true;

};
int Sequence::remove(const ItemType& value)
{
	//Node* val_finder;
	int items_deleted = 0;
	for (Node* val_finder = m_head->m_next; val_finder != m_head; val_finder = val_finder->m_next)
	{
		if (val_finder->m_data == value){
			val_finder = val_finder->m_next; //Tricky! At the end of erase, it deletes the node, so val_finder would be pointing to nothing and the loop can't progress
			erase(val_finder->m_previous->m_position);
			val_finder = val_finder->m_previous; //gotta put it back or it will skip elements
			items_deleted++;
		}
	}
	return items_deleted;
};
bool Sequence::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos >= size())
	{
		cerr << "Attempting to get a value from a position not in the range of the currently existing list.";
		return false;
	}
	Node* pos_finder;
	for (pos_finder = m_head->m_next; pos_finder != m_head; pos_finder = pos_finder->m_next)
	{
		if (pos_finder->m_position == pos)
		{
			value = pos_finder->m_data;
			break;
		}
	}
	return true;
};
bool Sequence::set(int pos, const ItemType& value)
{
	if (pos < 0 || pos >= this->size())
	{
		cerr << "Out of bounds";
		return false;
	}
	Node* pos_finder;
	for (pos_finder = m_head->m_next; pos_finder != m_head; pos_finder = pos_finder->m_next)
	{
		if (pos_finder->m_position == pos)
		{
			pos_finder->m_data = value;
			break;
		}
	}
	return true;
};
int Sequence::find(const ItemType& value) const
{
	Node* val_finder; //will go through the list, searching for the first value == to the value passed
	int counter = 0;
	for (val_finder = m_head->m_next; val_finder != m_head; val_finder = val_finder->m_next)
	{
		
		if (val_finder->m_data == value)
			return counter;
		counter++;
	}
	return -1;
};
void Sequence::swap(Sequence& other)
{
	int size_tmp = this->m_size;
	this->m_size = other.m_size;
	other.m_size = size_tmp;
	Node* tmp;
	tmp = this->m_head;
	m_head = other.m_head;
	other.m_head = tmp;
	tmp = nullptr;
};
void Sequence::dump() const
{
	if (m_size != 0)
	{
		Node* tmp = m_head->m_next;
		if (tmp == nullptr)
			cerr << "null";
		for (tmp; tmp != m_head; tmp = tmp->m_next)
		{
			cerr << "Value:" << tmp->m_data << " (position: " << tmp->m_position << ")" << endl;
		}
	}
	else
		cerr << "The list was empty. No contents to display.";
	cerr << endl;
};
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	//If seq2 is a subsequence of seq 1, return the position of the first item in seq1 where the subsequence starts
	//If seq2 is empty or not a subsequence of seq1, return -1
	if (seq2.empty())
		return -1;
	for (int i = 0; i < seq1.size(); i++)
	{
		int seq2sizecounter = 0; //if in the next loop you've iterated through it x times without breaking and x is equal to seq2.size(), you know you've found a subsequence
		int potential_pos = i; //storing this position now as a potential starting position for the subsequence
		int othercounter = 0; //tracks how far you've progressed in i when comparing values in the following loop
		for (int k = 0; k < seq2.size(); k++) 
		{
			//if (i + othercounter >= seq1.size()) //you could potentially fall off the end 
			//	break;
			ItemType seq2data, seq1data;
			seq2.get(k, seq2data);
			seq1.get(i, seq1data); //getting data ready to compare
			if (seq2data != seq1data)
			{
				for (int p = 0; p < othercounter; p++)
					i--; //sets i back to where it was before this loop started
				break;
			}
			else //they were equal
			{
				i++; //to compare the next element in seq1
				seq2sizecounter++; //getting closer to seq2.size()
				othercounter++; //this is how far we've gone along in seq1
				if (seq2sizecounter == seq2.size())
					return potential_pos;
				if ( i >= seq1.size())
					return -1; //you're going to exceed the size of seq1, meaning seq2 hasn't been finished yet but you're out of elements to compare in seq1
			}
		}
	}
	return -1; //no subsequence found
}
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	//currently only works for sequences of the same size being interweaved
	Sequence s1 = seq1;
	Sequence s2 = seq2;
	Sequence s3 = result;
	//delete all of s3 so you don't have to fiddle with inserting vs. setting
	int z = s3.size(); //if i just put in the s3.size() then the loop wouldn't execute properly
	for (int i = 0; i < z; i++)
	{
		s3.erase(0); //
	}
	//compare the sequences' size to find the smaller one
	int s1length = s1.size();
	int s2length = s2.size();
	int bigger, smaller;
	//have a bool to keep track of which sequence is larger
	bool seq1isLarger;
	if (s1length > s2length)
	{
		bigger = s1length;
		smaller = s2length;
		seq1isLarger = true;
	}
	else if (s2length > s1length)
	{
		bigger = s2length;
		smaller = s1length;
		seq1isLarger = false;
	}
	else
	{//they're the same size
		bigger = smaller = s1length;
		seq1isLarger = false; //won't matter because the second
							  //for loop won't execute
	}
	int difference = bigger - smaller;
	int insertioncounter = 0;
	int i; //we'll need this for the second loop
	for (i = 0; i < smaller*2; i++)
	{
		if (i % 2 == 0) //0, 2, 4... basically the items of s1
		{
			ItemType x;
			s1.get(i / 2, x);
			s3.insert(i, x);
		}
		else //it's an odd number and we're dealing with items of s2
		{
			insertioncounter++;
			ItemType y;
			s2.get((i - insertioncounter), y);
			s3.insert(i, y);
		}
	}
	for (int k = 0; k < difference; k++)
	{
		int p = i / 2;
		if (seq1isLarger)
		{
			ItemType x;
			seq1.get(p + k, x);
			s3.insert(i + k, x);
		}
		else //seq2 is larger
		{
			ItemType x;
			seq2.get(p + k, x);
			s3.insert(i + k, x);
		}
	}
	result = s3;
}