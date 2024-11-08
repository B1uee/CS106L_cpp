#include "class.h"


studentId::studentId(){
    this -> name = "Bryan";
    this -> id = 20241108;
}

studentId::studentId(std::string name, int id){
    this -> name = name;
    this -> id = id;
}

std::string studentId::getName() const{
    return this -> name;
}

int studentId::getId() const{
    return this -> id;
}

std::string studentId::getIdAndName() const{
    return "Name: " + this->name + " Id: " + std::to_string(this->id);
}

void studentId::setName(std::string name){
    this -> name = name;
}

void studentId::setId(int id){
    this -> id = id;
}


template <typename T>
myContainer<T>::myContainer(){
    this -> size = 0;
    this -> capacity = 65536;
    this -> data = new T[this->capacity];
}

template <typename T>
myContainer<T>::~myContainer(){
    delete[] this -> data;
}

template <typename T>
void myContainer<T>::expansion(){
    T* newData = new T[this->capacity*2];
    for (size_t i = 0; i < this->size; i++)
    {
        newData[i] = this -> data[i];
    }
    delete[] this -> data;
    this -> capacity *= 2;
    this -> size += 1;
}

template <typename T>
void myContainer<T>::push_back(const T& element){
    if(this->size == this->capacity)    expansion();
    this->data[this->size] = element;
    this -> size += 1;
}


template <typename T>
T& myContainer<T>::at(size_t index){
    if(index >= this->size) throw std::out_of_range("Error: Out of range");
    return this->data[index];
}

template <typename T>
T& myContainer<T>::operator[](size_t index){
    return this->data[index];
}

template <typename T>
size_t myContainer<T>::length(){
    return this -> size;
}

template <typename T>
bool myContainer<T>::empty(){
  return this->size == 0;
}

template <typename T>
typename myContainer<T>::iter myContainer<T>::begin()   // typename: this is a type
{                                                       // myContainer<T>::iter -> T*
  return this -> data;
}

template <typename T>
typename myContainer<T>::iter myContainer<T>::end()  
{
  return this -> data + this -> size;
}