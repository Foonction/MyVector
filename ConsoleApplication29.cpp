#include <iostream>
#include <vector>
template <typename T = int, typename Allocator = std::allocator<T>>
class MyVector
{
public:

	using allocator_int = Allocator; 

	allocator_int get_allocator() noexcept
	{
		return _alloc;
	}
	[[nodiscard]] allocator_int get_allocator() const noexcept
	{
		return _alloc;
	}
	MyVector() : size(0), capacity(1)
	{
		data = _alloc.allocate(1);
	}

	~MyVector()
	{
		_alloc.deallocate(data, capacity);
	}

	// copy constructor (deep copy)
	MyVector(const MyVector& other)
		: data(_alloc.allocate(other.capacity)), size(other.size), capacity(other.capacity)
	{
		for (size_t i = 0; i < size; ++i) 
			data[i] = other.data[i];
	}

	auto begin() 
	{
		auto it = data;
		return it;
	}

	auto end() 
	{
		auto it = data;
		it += size;
		return it;
	}
	// copy assignment (deep copy)
	MyVector& operator=(const MyVector& other)
	{
		if (this == &other)	
			return *this;

		int* newData = _alloc.allocate(other.capacity);

		for (size_t i = 0; i < other.size; ++i) 
			newData[i] = other.data[i];

		_alloc.deallocate(data, capacity);
		data = newData;
		size = other.size;
		capacity = other.capacity;
		return *this;
	}

	size_t size() const
	{
		return size;
	}

	void erase(auto begin, auto end) {
		int b = -1, e = -1;
		auto it = data;

		for (int i = 0; i < size; i++) {
			if (it == begin) 
				b = i;

			if (it == end) 
				e = i;
			it++; 
		}
		
		if (it == end) 
			e = size;
		
		if (b == -1 || e == -1 || b >= e) 
			return;

		size_t newSize = size - (e - b);
		auto n_data = _alloc.allocate(capacity);

		int current = 0;
		for (int i = 0; i < size; i++) {
			if (i < b || i >= e) {
				n_data[current++] = data[i];
			}
		}

		_alloc.deallocate(data, capacity);
		data = n_data;
		size = newSize;
	}

	int front()
	{
		return data;
	}

	void pop_back() 
	{
		int* new_data = _alloc.allocate(size - 1);

		for (int i = 0, j = 0; i < size; ++i) {
			if (i == size - 1) {
				continue; 
			}
			new_data[j] = data[i];
			j++;
		}

		_alloc.deallocate(data, capacity);
		data = new_data;
		size--;
	}

	void resize(int new_size)
	{
		if (new_size >= size)
		{
			size = new_size;
			int* new_data = _alloc.allocate(new_size);
			for (size_t i = 0; i < size; i++)
			{
				new_data[i] = data[i];
			}
			_alloc.deallocate(data, capacity);
			data = new_data;
		}
	}

	size_t capacity()
	{
		return capacity;
	}

	int& at(size_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range("index out of range");
		}
		return data[index];
	}

	const int& at(size_t index) const
	{
		if (index >= size)
		{
			throw std::out_of_range("index out of range");
		}
		return data[index];
	}
	
	void insert(auto it, int num) 
	{
		size_t index = it - data;
		size_t newCapacity = capacity + 1;
		int* newData = new int[newCapacity];

		for (size_t i = 0; i < index; ++i) 
		{
			newData[i] = data[i];
		}
		newData[index] = num;

		for (size_t i = index; i < size; ++i) 
		{
			newData[i + 1] = data[i];
		}
		_alloc.deallocate(data, capacity);
		data = newData;
		capacity = newCapacity;
		size++; 
	}

	void emplace(int* it, int val)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (data == it)
			{
				data[i] = val;
			}
			data++;
		}
		data -= size;
	}
	bool empty()
	{
		if (size == 0)
		{
			return true;
		}
		return false;
	}
	
	int& back()
	{
		if (!empty())
		{
			int& ref = data[size - 1];
			return ref;
		}
		throw std::runtime_error("vector is empty");
	}
	
	const int* crbegin() const
	{
		const int* cr = data + size - 1;
		return cr;
	}

	const int* crend() const
	{
		return data - 1;
	}

	int* data()
	{
		return data;
	}

	void push_back(int num)
	{
		if (size == capacity)
		{
			size_t newCapacity = capacity * 2;
			int* newData = _alloc.allocate(newCapacity);
			for (size_t i = 0; i < size; i++)
			{
				newData[i] = data[i];
			}
			_alloc.deallocate(data, capacity);
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

	void assign(size_t new_size, int value)
	{
		int* new_data = _alloc.allocate(new_size);
		_alloc.deallocate(data, capacity);
		size = new_size;
		capacity = new_size;
		data = new_data;
		for (size_t i = 0; i < new_size; i++)
		{
			data[i] = value;
		}
	}

	int& operator[](int index)
	{
		return data[index];
	}
	void clear()
	{
		_alloc.deallocate(data, capacity);
		size = 0;
		capacity = 0;
	}

private:
	int* data;
	size_t size;
	size_t capacity;
	Allocator _alloc;
};

int main()
{
	MyVector vec;
	std::vector<int> vec2;
	//vec2.push_back(1);
	vec.push_back(123321);
	vec.push_back(148);
	vec.push_back(124421);
	
}

