// The Handle class is a generic handle class through which
// other classes can be used. It will manage pointers to a class when
// they're created with new so the user doesn't have to.

#ifndef HANDLECLASS_H_
#define HANDLECLASS_H_
#include <stdexcept>

template <typename Type> class Handle
{
public:
	Handle(Type *pointer = 0): ptr(pointer), count(new std::size_t(1)) {}
	Handle(const Handle &h): ptr(h.ptr), count(h.count) {++*count;}
	Handle & operator=(const Handle &rhs);
	void AssignNewObject(Type *pointer);
	Type & operator*();
	Type * operator->();
	const Type & operator*() const;
	const Type * operator->() const;
	~Handle () {RemoveReference();}
private:
	Type *ptr;
	std::size_t *count;
	void RemoveReference();
};

// RemoveReference decrements the use count of handles pointing to an object.
// If the count reaches 0, the object and the count are deleted. 
template <typename Type>
void Handle<Type>::RemoveReference()
{
	if((--*count) == 0)
	{
		delete ptr;
		delete count;
	}
}

// Assigns a new object of the same type to the handle. Also explicitly calls
// RemoveReference() to delete the object that was pointed to previously.
template <typename Type>
void Handle<Type>::AssignNewObject(Type *pointer)
{
	RemoveReference();	// remove any old references to data
	ptr = pointer;
	count = new std::size_t(1);
}

// Assignment operator
template <typename Type>
Handle<Type> & Handle<Type>::operator=(const Handle &rhs)
{
	++*rhs.count;
	RemoveReference();
	ptr = rhs.ptr;
	count = rhs.count;
	return *this;
}

// Returns a reference to the underlying object pointed to by the ptr member.
template <typename Type>
inline Type & Handle<Type>::operator*()
{
	if(ptr) {return *ptr;}
	throw std::runtime_error("Dereference operator called on unbound Handle object.");
}

// Returns the memory address of the object to which ptr points.
template <typename Type>
inline Type * Handle<Type>::operator->()
{
	if(ptr) {return ptr;}
	throw std::runtime_error("Arrow operator called on unbound Handle object.");
}

// Returns a const-reference to the underlying object pointed to by the ptr member.
template <typename Type>
inline const Type & Handle<Type>::operator*() const
{
	if(ptr) {return *ptr;}
	throw std::runtime_error("Dereference operator called on unbound Handle object.");
}

// Returns a const-memory address of the object to which ptr points.
template <typename Type>
inline const Type * Handle<Type>::operator->() const
{
	if(ptr) {return ptr;}
	throw std::runtime_error("Arrow operator called on unbound Handle object.");
}
#endif