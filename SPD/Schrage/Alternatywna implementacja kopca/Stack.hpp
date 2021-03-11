#ifndef STACK_HPP
#define STACK_HPP

template<typename TYPE>
struct StackElem
{
	TYPE elem;
	StackElem<TYPE>* next_elem;
};

// Required for faster Heap implementation
// TYPE must be copyable, assignable. Basically not-pointer
// Usable methods:
// 'size()' number of elements
// 'front()' element on top of Stack
// 'push(const TYPE&)' put element on top of Stack
// 'pop()' remove element from top of Stack
template<typename TYPE>
class Stack
{
	protected:
		StackElem<TYPE>* front_elem;
		unsigned int number_of_elem;
	public:
		// Consts
		inline unsigned int size(void) const { return number_of_elem; };
		inline const TYPE& front(void) const { return (front_elem->elem); };
		// Modifiers
		void push(const TYPE& inp)
		{
			StackElem<TYPE>* temp = front_elem;
			front_elem = new StackElem<TYPE>;
			front_elem->next_elem = temp;
			front_elem->elem = inp;
			++number_of_elem;
		}
		void pop(void)
		{
			StackElem<TYPE>* temp = front_elem;
			front_elem = temp->next_elem;
			delete temp;
			--number_of_elem;
		}
		void clear(void)
		{
			while(number_of_elem)
			{
				pop();
			}
		}
		// Constructors
		Stack() { number_of_elem = 0; front_elem = nullptr; }
		~Stack() { clear(); }
};

#endif
