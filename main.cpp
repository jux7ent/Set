#include <cstdlib>
#include <iostream>

template<class Type>
class array {

private:

    Type *value_;
    size_t size_;
    size_t capacity_;

public:

    array();

    array(Type val);

    array(const array &copy);

    ~array();

    void push_back(Type a);

    const Type &operator[](size_t index) const;

    Type &operator[](size_t index);

    array &operator=(const array &val);

    size_t size() const;

    bool empty() const;

    void insert(size_t pos, Type val);

    void reserve(size_t newCapacity);

    void pop_back();

    void remove(size_t pos);

    void delete_value(Type val);
};

template <class Type>
array<Type>::array() : size_(0), capacity_(1) {
    value_ = new Type[1];
}

template <class Type>
array<Type>::array(Type val) : size_(1), capacity_(1) {
    value_ = new Type[1];
    value_[0] = val;
}

template <class Type>
array<Type>::array(const array &copy) : size_(0), capacity_(1) {
    value_ = new Type[1];
    *this = copy;
}

template <class Type>
array<Type>::~array() {
    delete[] value_;
}

template <class Type>
void array<Type>::reserve(size_t newCapacity) {
    if (newCapacity > capacity_) {
        Type *temp = new Type[newCapacity];

        for (size_t i = 0; i < size_; ++i) {
            temp[i] = value_[i];
        }

        delete[] value_;

        value_ = temp;
        capacity_ = newCapacity;
    }
}

template <class Type>
void array<Type>::push_back(Type a) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }

    ++size_;

    value_[size_ - 1] = a;
}

template <class Type>
size_t array<Type>::size() const {
    return size_;
}

template <class Type>
bool array<Type>::empty() const {
    return size_ == 0;
}

template <class Type>
const Type &array<Type>::operator[](size_t index) const {
    return value_[index];
}

template <class Type>
Type &array<Type>::operator[](size_t index) {
    return value_[index];
}

template <class Type>
void array<Type>::insert(size_t pos, Type val) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }


    for (size_t i = size_; i > pos; --i) {
        value_[i] = value_[i - 1];
    }
    value_[pos] = val;

    ++size_;
}

template <class Type>
void array<Type>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template <class Type>
array<Type> &array<Type>::operator=(const array<Type> &val) {
    size_ = 0;

    for (size_t i = 0; i < val.size(); ++i) {
        push_back(val[i]);
    }

    return *this;
}

template <class Type>
void array<Type>::remove(size_t pos) {
    for (size_t i = pos; i < size_ - 1; ++i) {
        value_[i] = value_[i + 1];
    }

    --size_;
}

template <class Type>
void array<Type>::delete_value(Type val) {
    for (int i = 0; i < size_; ++i) {
        if (value_[i] == val) {
            remove(i);
        }
    }
}

template <class T>
class Set {
private:

    array<T> elements_;

public:

    Set();

    Set(int elements_count, ...);

    Set(const Set<T> &set);

    Set<T> operator+(const Set<T> &set) const;

    Set<T> operator-(const Set<T> &set) const;

    Set<T> operator*(const Set<T> &set);

    bool operator==(const Set<T> &set);

    bool operator<=(const Set<T> &set);

    bool operator>=(const Set<T> &set);

    Set<T> &operator<<(T value);

    template <class C>
    friend bool search(const Set<C> &set, C element);

    void print();
};

template <class T>
Set<T>::Set() : elements_() {}

template <class T>
Set<T>::Set(int elements_count, ...) {
    for (int i = 0; i <= elements_count; ++i) {
        if (!search(*this, elements_count)) {
            elements_.push_back((&elements_count)[i]);
        }
    }
}

template <class T>
Set<T>::Set(const Set<T> &set) {
    for (int i = 0; i < set.elements_.size(); ++i) {
        elements_.push_back(set.elements_[i]);
    }
}

template <class T>
bool search(const Set<T> &set, T element) {
    bool result = false;
    for (int i = 0; i < set.elements_.size(); ++i) {
        if (set.elements_[i] == element) {
            result = true;
            break;
        }
    }

    return result;
}

template <class T>
Set<T> Set<T>::operator+(const Set<T> &set) const {
    Set<T> result;
    for (int i = 0; i < elements_.size(); ++i) {
        result.elements_.push_back(elements_[i]);
    }

    for (int i = 0; i < set.elements_.size(); ++i) {
        if (!search(*this, set.elements_[i])) {
            result.elements_.push_back(set.elements_[i]);
        }
    }

    return result;
}

template <class T>
Set<T> Set<T>::operator-(const Set<T> &set) const {
    Set<T> result = *this;

    for (int i = 0; i < set.elements_.size(); ++i) {
        if (search(*this, set.elements_[i])) {
            result.elements_.delete_value(set.elements_[i]);
        }
        else {
            result.elements_.push_back(set.elements_[i]);
        }
    }

    return result;
}

template <class T>
Set<T> Set<T>::operator*(const Set<T> &set) {
    Set<T> result;

    for (int i = 0; i < elements_.size(); ++i) {
        if (search(set, elements_[i])) {
            result.elements_.push_back(elements_[i]);
        }
    }

    return result;
}

template <class T>
bool Set<T>::operator==(const Set<T> &set) {

    if (elements_.size() != set.elements_.size()) {
        return false;
    }

    for (int i = 0; i < elements_.size(); ++i) {
        if (!search(set, elements_[i])) {
            return false;
        }
    }

    return true;
}

template <class T>
bool Set<T>::operator<=(const Set<T> &set) {
    for (int i = 0; i < elements_.size(); ++i) {
        if (!search(set, elements_[i])) {
            return false;
        }
    }

    return true;
}

template <class T>
bool Set<T>::operator>=(const Set<T> &set) {
    return !(*this <= set);
}

template<typename T>
Set<T> &Set<T>::operator<<(T value) {
    if (!search(*this, value)) {
        elements_.push_back(value);
    }
    return *this;
}

template <class T>
void Set<T>::print() {
    for (int i = 0; i < elements_.size(); ++i) {
        std::cout << elements_[i] << std::endl;
    }
}


int main() {
    Set<int> set_f, set_s;
    set_f << 1 << 2 << 1 << 2;
    set_s << 1 << 2 << 3;
    (set_f * set_s).print();
    std::cout << (set_f >= set_s) << std::endl;
}
