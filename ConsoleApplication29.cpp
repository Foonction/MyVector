#include <iostream>
#include <vector>
template <typename T, typename Allocator = std::allocator<T>>
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
		for (size_t i = 0; i < size; ++i) 
			data[i] = other.data[i];
	}

	auto Begin() 
	{
		auto it = data;
		return it;
	}

	auto End() 
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

		int* newData = new int[other.capacity];

		for (size_t i = 0; i < other.size; ++i) 
			newData[i] = other.data[i];

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

	void Erase(auto begin, auto end) {
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
		auto n_data = new int[capacity]; 

		int current = 0;
		for (int i = 0; i < size; i++) {
			if (i < b || i >= e) {
				n_data[current++] = data[i];
			}
		}

		delete[] data;
		data = n_data;
		size = newSize;
	}

	int front()
	{
		return data[0];
	}

	void Pop_Back() 
	{
		int* new_data = new int[size - 1];

		for (int i = 0, j = 0; i < size; ++i) {
			if (i == size - 1) {
				continue; 
			}
			new_data[j] = data[i];
			j++;
		}

		delete[] data;
		data = new_data;
		size--;
	}

	void Resize(int new_size)
	{
		if (new_size >= size)
		{
			size = new_size;
			int* new_data = new int[new_size];
			for (size_t i = 0; i < size; i++)
			{
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
		}
	}

	size_t Capacity()
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
		delete[] data;
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
		int* cr = new int(size);
		for (size_t i = 0; i < size; i++)
		{
			cr[size - i - 1] = data[i];
		}
		const int* new_cr = cr + size;
		return new_cr;
	}

	int* Data()
	{
		return data;
	}

	void Push_Back(int num)
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

	void assign(size_t new_size, int value)
	{
		int* new_data = new int(new_size);
		delete[] data;
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
	void Clear()
	{
		delete[] data;

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
	vec2.push_back(123321);
	vec2.push_back(148);
	vec2.push_back(124421);
	
	auto it = vec2;
	//vec2.pop_back();
	//std::cout << vec2.at(0);
	//std::cout << vec2[0] << std::endl;
	//std::cout << *vec2.begin();
	vec.Push_Back(2);
	vec.Push_Back(123);
	vec.Push_Back(124);
	vec.insert(vec.End(), 1);
	vec.emplace(vec.Begin(), 123);
	std::cout << vec;
	//std::cout << vec;
	//std::cout << vec2.capacity();
	//std::cout << *(vec.crbegin() - 1);
	//std::cout << *(vec.crend() - 1);
	//std::cout << vec.front() + 1;
	//std::cout << vec[0];(
	std::cout << vec2.get_allocator().max_size();
	
	
}

