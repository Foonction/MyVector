#include <iostream>
#include <vector>
class MyVector
{
public:
	MyVector() : data(new int[1]), size(0), capacity(1)
	{
	
	}

	~MyVector()
	{
		delete[] data;
	}

	// copy constructor (deep copy)
	MyVector(const MyVector& other)
		: data(new int[other.capacity]), size(other.size), capacity(other.capacity)
	{
		for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
	}

	// copy assignment (deep copy)
	MyVector& operator=(const MyVector& other)
	{
		if (this == &other) return *this;
		int* newData = new int[other.capacity];
		for (size_t i = 0; i < other.size; ++i) newData[i] = other.data[i];
		delete[] data;
		data = newData;
		size = other.size;
		capacity = other.capacity;
		return *this;
	}

	size_t Size() const
	{
		return size;
	}



	void PushBack(int num)
	{
		if (size == capacity)
		{
			size_t newCapacity = capacity * 2;
			int* newData = new int[newCapacity];
			for (size_t i = 0; i < size; ++i)
				newData[i] = data[i];
			delete[] data;
			data = newData;
			capacity = newCapacity;
		}
		data[size++] = num;
	}

	friend std::ostream& operator <<(std::ostream& os, const MyVector& v)
	{
		if (v.size == 0)
			return os;

		os << '[';
		for (size_t i = 0; i < v.size; ++i)
		{
			if (i) os << ", ";
			os << v.data[i];
		}
		os << ']';
		return os;
	}

	void Clear()
	{
		delete[] data;

	}

private:
	int* data;
	size_t size;
	size_t capacity;
};








int main()
{
	MyVector vec;
	std::vector<int> vec2;
	vec.PushBack(123);
	vec.Clear();
	std::cout << vec;
	
	
}

