#include <iostream>

template<typename T>
class Vector {
private:
    T* ptr;
    int size;
    int capacity;

public:
    Vector(int size) : size(size), capacity(size) {
        ptr = new T[capacity];
    }

    virtual ~Vector() {
        delete[] ptr;
    }


    Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        ptr = new T[capacity];
        for (int i = 0; i < size; ++i) {
            ptr[i] = other.ptr[i];
        }
    }


    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] ptr;
        size = other.size;
        capacity = other.capacity;
        ptr = new T[capacity];
        for (int i = 0; i < size; ++i) {
            ptr[i] = other.ptr[i];
        }
        return *this;
    }

    Vector(Vector&& other) : ptr(other.ptr), size(other.size), capacity(other.capacity) {
        other.ptr = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Vector& operator=(Vector&& other) {
        if (this == &other) {
            return *this;
        }
        delete[] ptr;
        ptr = other.ptr;
        size = other.size;
        capacity = other.capacity;
        other.ptr = nullptr;
        other.size = 0;
        other.capacity = 0;
        return *this;
    }
    T& operator[](int index) {
        if (index >= size) {
            throw "Index out of range";
        }
        return ptr[index];
    }
public:
    int getSize() const {
        return size;
    }
    int getCapacity()const {
        return capacity;
    }
    bool empty()const {
        return size == 0;
    }

    T& at(int index) {
        if (index <size) {
            return ptr[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }
    void push_back(const T& value) {
        if (size == capacity) {
            capacity *= 2;
            T* newPtr = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newPtr[i] = ptr[i];
            }
            delete[] ptr;
            ptr = newPtr;
        }
        ptr[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }
};
int main() {
    Vector<int> intVec(12);
    try {
        std::cout << intVec.at(4) << std::endl;
        std::cout << intVec.at(374) << std::endl;
    }
    catch (std::out_of_range& er) {
        std::cerr << "Error: " << er.what() << std::endl;

    }
    return 0;
}