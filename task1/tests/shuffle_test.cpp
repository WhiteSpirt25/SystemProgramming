//#include <myproject/MyVector.h>

#include <algorithm>
#include <random>
#include <fstream>

#include <iostream>
#include <string>

template <typename T>
class MyVector {

	T* first;
	T* last;// points to the last added element
	T* end_of_storage;// points to the last reserved memory cell

	
	void increase_size() {
		const unsigned int new_size = 2 * this->capacity();

		// new allocated memory 
		T* newarr = new T[new_size];

		const unsigned int number_of_elements = this->size();


		//copying contents
		for (int i = 0; i < number_of_elements; i++) {
			newarr[i] = std::move(first[i]);
		}

		// clearing memory
		delete[] first;
		// updating pointers
		first = newarr;
		end_of_storage = first + new_size - 1 ;//-1 is for pointing on the last cell & not past it (due to existing of pointer "first")
		last = first + number_of_elements-1;
	}


public:
	MyVector() {
		first = nullptr;
		last = nullptr;
		end_of_storage = nullptr;
	}

	//move constructor
	MyVector(MyVector&& x) :first(x.first), last(x.last), end_of_storage(x.end_of_storage) { 
		x.first = nullptr;
		x.last = nullptr;
		x.end_of_storage = nullptr;
	}
	//copy constructor
	MyVector(const MyVector& x) :first(nullptr), last(nullptr), end_of_storage(nullptr){

		auto ptr = x.first;
		
		while (ptr != x.last){
			this->push_back(*(ptr++));
		}
	}
	//destructor
	~MyVector() {
		if (first != nullptr)
			delete[] first;
	}
	
	// number of elements in the vector
	const int size() {
		return last - first + 1;
	}
	// Returns the number of elements that the container has currently allocated space for. 
	const int capacity() {
		return end_of_storage - first + 1;
	}

	// copy assignement 
	MyVector& operator=(MyVector& vec){	

		// when vec const breaks - FIX

		//allocated memory
		T* arr = new T[vec.capacity()];

		// copying data
		for (int i = 0; i < vec.size(); i++) {
			arr[i] = vec[i];
		}

		// clearing memory
		delete[] first;

		// updating pointers
		first = arr;
		end_of_storage = first + vec.capacity() - 1;//-1 is for pointing on the last cell & not past it (due to existing of pointer "first")
		last = first + vec.size() - 1;


		return *this;
	}
	//move assignement 
	MyVector& operator=(MyVector&& vec) {

		delete[] first;

		first = vec.first;
		last = vec.last;
		end_of_storage = vec.end_of_storage;

		vec.first = nullptr;
		vec.last = nullptr;
		vec.end_of_storage = nullptr;


		return *this;
	}

	T& operator[](int idx) {
		return *(first + idx);
	}
	   	
	//copy push back
	void push_back(const T& elem) {
		//in case of empty array
		if (first == nullptr) {

			// intitial size of array
			const unsigned int initial_size = 3;

			// memory allocation

			T* arr = new T[initial_size];
			arr[0] = elem;

			// pointers
			first = arr;
			last = first;
			end_of_storage = first + initial_size-1;//-1 is for pointing on the last cell & not past it
		}
		else // case if array already have elements
		{
			if (last == end_of_storage)
				increase_size();

			*(++last) = elem;
		}
	}
	//move version push back
	void push_back(T&& elem) {
		if (first == nullptr) {

			// intitial size of array
			const unsigned int initial_size = 3;

			// memory allocation

			T* arr = new T[initial_size];
			arr[0] = std::move(elem);

			// pointers
			first = arr;
			last = first;
			end_of_storage = first + initial_size - 1;//-1 is for pointing on the last cell & not past it
		}
		else
		{
			if (last == end_of_storage)
				increase_size();

			*(++last) = std::move(elem);
		}
	}

	void erase(const int idx) {
		//finding the erased element and using pointer as iterator to move the data in place of erased
		T* elem = first + idx;

		while (elem != last) {
			*elem = *(elem + 1);
			++elem;
		}
		// and updating pointer to the last element 
		--last;
	}
	void pop_back() {
		--last;
	}

	T* begin() {
		return first;
	}
	T* end() {
		if (last == end_of_storage)
			increase_size();
		return last + 1;
	}

	void swap(MyVector& vec) {
		//memorizing pointers of this array
		T* tmpfirst = first;
		T* tmplast = last;
		T* tmpend_of_storage = end_of_storage;

		//changing this pointers with ones from vec
		first = vec.first;
		last = vec.last;
		end_of_storage = vec.end_of_storage;

		// changing vec pointers
		vec.first = tmpfirst;
		vec.last = last;
		vec.end_of_storage = end_of_storage;
	}
	

};
template<typename T>
void swap (MyVector<T>& a,MyVector<T>& b){
	a.swap(b);
}

int main() {
	
	/*
	MyVector<std::ofstream> v;

	const int num = 10;

	for (int i = 0; i < num; i++) {
		std::ofstream a ("tests/results/"+std::to_string(i) + ".txt");
		v.push_back(std::move(a));
	}
	
	std::random_device rd;
	std::shuffle(v.begin(), v.end(), rd);

	for (int i = 0; i < v.size(); i++) {
		v[i] << i;
	}
	*/
	MyVector<int> v;
	for (int i = 0; i < 10; i++){
		v.push_back(i);
	}
	v.erase(3);
	MyVector<int> w(v);
	for (int i = 0; i < w.size(); i++){
		std::cout<<w[i]<<'\n';
	}

	return 0;
}