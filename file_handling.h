#ifndef _FILE_HANDLING_H_
#define _FILE_HANDLING_H_

#include <fstream>
#include "university.h"

void put_university(Subject* subjects = NULL, int num_sub = 0, Student* students = NULL, int num_st = 0, Teacher* teachers = NULL, int num_tch = 0, std::string path = "data.nvrst");
void read_university(Subject*& subjects, int& num_sub, Student*& students, int& num_st, Teacher*& teachers, int& num_tch, std::string path = "data.nvrst");

#endif