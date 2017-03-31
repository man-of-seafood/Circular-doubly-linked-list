#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED
#include <string>
#include <iostream>
using namespace std;
typedef unsigned long ItemType;

class Sequence
{
public:
	Sequence();
	~Sequence();
	Sequence(const Sequence &other);
	Sequence& operator=(Sequence rhs);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	bool insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
	int subsequence(const Sequence& seq1, const Sequence& seq2);
	void dump() const;
	
private:
	struct Node
	{
		ItemType m_data;
		int m_position;
		Node* m_next;
		Node* m_previous;
	};
	Node* m_head; //pointer to the initial node, the dummy node
	int m_size;
	
};
int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
#endif //SEQUENCE_INCLUDED