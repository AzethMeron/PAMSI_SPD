#ifndef KOPIEC_HPP
#define KOPIEC_HPP

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// You need to pass function in constructor that will be used to compare values
// bool Comp(const TYPE& l, const TYPE& r) 
// Return TRUE if LEFT is bigger than RIGHT to get asceding order

// Useful methods: 
// 'push(const TYPE&)' to properly add new element to Heap
// 'front()' to get element on top of Heap
// 'pop()' to remove element on top
// 'size()' to get size of Heap
// 'remove(const int&)' to remove element from given index in internal container
// operator [] allows to GET, but not SET value in internal container. Useful for searching
// 'find(const TYPE& elem, bool FUNCTION(const TYPE&, const TYPE&))' get index of elem in internal container. Return -1 if not found

// for some reason, function named 'equal' didnt work, and 'func' and 'arc' worked fine
// maybe there is limit of functions' name length?
template<typename TYPE>
class Heap 
{
	private:
		void UpdateNode(const int& node);
		inline int Parent(const int& node) const { return ((node-1)/2); }
		inline int LChild(const int& node) const { int wyjscie = -1; if(((node+1)*2-1) < (int)size()) wyjscie = ((node+1)*2-1); return wyjscie; }
		inline int RChild(const int& node) const { int wyjscie = -1; if(((node+1)*2) < (int)size()) wyjscie = ((node+1)*2); return wyjscie; }
	protected:
		vector<TYPE> data;
		std::function<bool(const TYPE&, const TYPE&)> Comp;
	public:
		// Consts
		inline unsigned int size(void) const { return data.size(); }
		inline const TYPE& front(void) const { return data.front(); }
		inline const TYPE& operator [] (const int& ind) const { return data[ind]; }
		int find(const TYPE& elem, std::function<bool(const TYPE&, const TYPE&)> ifequal) const;
		// Modifiers
		inline void push(const TYPE& inp)	{ data.push_back(inp); UpdateNode(size()-1); }
		inline void pop(void)	{ swap(data.front(),data.back()); data.pop_back(); UpdateNode(0); }
		inline void remove(const int& ind)	{ swap(data[ind],data.back()); data.pop_back(); UpdateNode(ind); }
		// Constructors
		Heap(std::function<bool(const TYPE&, const TYPE&)> comp, const vector<TYPE>& newdata)	{ Comp = comp; for(unsigned int i = 0; i < newdata.size(); ++i) { push(newdata[i]);	} }
		Heap(std::function<bool(const TYPE&, const TYPE&)> comp) { Comp = comp; }
};

template<typename TYPE>
void Heap<TYPE>::UpdateNode(const int& node)
{
	int parent = Parent(node);
	int lchild = LChild(node); // -1 if non-existant
	int rchild = RChild(node); // -1 if non-existant

	// Parent
	if(node > 0)
	{
		if( Comp(data[parent],data[node]) )
		{
			swap(data[node],data[parent]); UpdateNode(parent); UpdateNode(node); return;
		}
	}
	// Childs
	if( lchild > 0 )
	{
		if( Comp(data[node],data[lchild]) )
		{
			swap(data[node],data[lchild]); UpdateNode(lchild); UpdateNode(node); return;
		}
	}
	if( rchild > 0 )
	{
		if( Comp(data[node],data[rchild]) )
		{
			swap(data[node],data[rchild]); UpdateNode(rchild); UpdateNode(node); return;
		}
	}
}

template<typename TYPE>
int Heap<TYPE>::find(const TYPE& elem, std::function<bool(const TYPE&, const TYPE&)> ifequal) const
{
	for(int i = 0; i < (int)size(); ++i)
	{
		if(ifequal(elem,data[i]))
			return i;
	}
	return -1;
}

#endif
