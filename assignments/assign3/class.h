#pragma once
#include <string>
#include <stdexcept> 
//normal class
class studentId{   
private:
    std::string name;
    int id;
    std::string getIdAndName() const;
public:
    studentId();
    ~studentId();
    studentId(std::string name, int id);
    std::string getName() const;
    int getId() const;
    void setName(std::string name);
    void setId(int id);
};


//template class
template <typename T>
class myContainer{
public:
    using iter = T*;

    myContainer();
    myContainer(size_t size, size_t capacity, T* data): size(size), capacity(capacity), data(data) {};
    ~myContainer();

    void push_back(const T& element);
    T& at(size_t index);
    T& operator[](size_t index);

    size_t length();
    bool empty();
    iter begin();
    iter end();

private:
    size_t size;
    size_t capacity;
    T* data;
    void expansion();
};

//#include "../assign3/class.cpp"