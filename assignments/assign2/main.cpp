/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <random>
#include <ctime>
#include "utils.h"

std::string kYourName = "Bryan Austin"; // Don't forget to change this!
std::string INPUT_FILE_PATH = "students.txt";
/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::set<std::string> return_set;
  std::ifstream inputFile(filename);
  if(inputFile.is_open()){
      
      std::string line;
      while(getline(inputFile, line)){
          return_set.insert(line);
          //std::cout << line << std::endl;
      }
  }
  return return_set;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::istringstream ss(name);
  std::string my_first_name, my_last_name;
  ss >> my_first_name >> my_last_name;
  std::queue<const std::string*> return_queue;
  for(const auto& student:students){   // 一定要加const auto& 而不能直接auto，一是因为auto会取消原有的const和&
    std::string first_name, last_name; // 二是不用&，添加的只是student的临时副本的指针
    std::istringstream ss_tmp(student);
    ss_tmp >> first_name >> last_name;
    //std:: cout << first_name << " " <<  my_first_name << std::endl;
    if(first_name[0] == my_first_name[0] && last_name[0] == my_last_name[0]){
      return_queue.push(&student);   // std::set 内部存储的元素默认为const，因此&student 即为const string*
    }
  }

  return return_queue;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.

  std::vector<const std::string*> vec_copy;
  while(!matches.empty()){
    std::cout << *matches.front() << std::endl;
    vec_copy.push_back(matches.front());
    matches.pop();
  }
  if(vec_copy.empty())  return "NO STUDENT FOUND.";
  else{
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<std::size_t> dist(0, vec_copy.size() - 1);

    auto randomElement = vec_copy[dist(rng)];
    return *randomElement;
  }
}

/* #### Please don't modify this call to the autograder! #### */
int main() { 
  
  auto students = get_applicants(INPUT_FILE_PATH);
  auto matches = find_matches(kYourName, students);

  auto match = get_match(matches);
  std::cout << match << std::endl;
  return run_autograder(); 
  //return 0;

}
