#ifndef _UNIVERSITY_H_

#define _UNIVERSITY_H_
#include <string>

enum Sex
{
	f,
	m
};

std::string format(int form, int num);

class Student;
class Subject;
class Teacher;

std::string print(Subject* subjects, int num_sub, Student* students, int num_st, Teacher* teachers, int num_tch);

class Subject
{
	std::string title;
	int num_credits, reg_lim, registered;
	std::string* students;
	int related; //Amount of students and teachers who took this subject
public:

	friend void put_university(Subject* subjects, int num_sub, Student* students, int num_st, Teacher* teachers, int num_tch, std::string path);
	//So we can write all of the attributes to the file
	friend void read_university(Subject*& subjects, int& num_sub, Student*& students, int& num_st, Teacher*& teachers, int& num_tch, std::string path);
	//So we can read all the attributes from the file
	friend class Teacher;
	friend class Student; //So student and teacher can have an access to students, register, reg_lim, etc.

	bool operator==(const Subject& s) const;
	bool operator!=(const Subject& s) const;
	Subject& operator=(const Subject& s);

	Subject(std::string title = "", int num_credits = 0, int reg_lim = 0 , int registered = 0, std::string* students = NULL);
	//title can't start with '\x1E'
	Subject(const Subject& sub);
	~Subject();
	void Set_title(std::string title);
	//title can't start with '\x1E'
	void Set_num_credits(int num_credits);
	void Set_reg_lim(int reg_lim);
	std::string Get_title() const;
	std::string list_data() const; //Listing all the data of the subject
	std::string list_students() const; // Listing all the students who took this subject
	int Get_num_credits() const;
	int Get_reg_lim() const;
	int Get_registered() const;
	int Get_related() const;
};

class Person //Abstract class only with getters and setters
{
protected:
	std::string firstname, lastname;
	int d_birth, m_birth, y_birth;
	Sex sex;
public:
	std::string Get_name(bool last_name_first = false) const;
	std::string Get_first_name() const;
	std::string Get_last_name() const;
	std::string Get_birth_date(bool hun_format = false) const;
	int Get_day_of_birth() const;
	int Get_month_of_birth() const;
	int Get_year_of_birth() const;
	Sex Get_sex() const;
	virtual void Set_first_name(std::string password, std::string firstname) = 0;
	virtual void Set_last_name(std::string password, std::string lastname) = 0;
	virtual void Set_day_of_birth(std::string password, int d_birth) = 0;
	virtual void Set_month_of_birth(std::string password, int m_birth) = 0;
	virtual void Set_year_of_birth(std::string password, int y_birth) = 0;
	virtual void Set_sex(std::string password, Sex sex) = 0;
};

class Student :public Person
{
	Subject** taken_subjects;
	int* grades;
	int num_subjects;
	int id;
	std::string major, password;
	static int num_used_ids;
	static const char cipher_password;

	static int generate_id();
	std::string encrypt_password(std::string input) const;
	
public:

	friend void put_university(Subject* subjects, int num_sub, Student* students, int num_st, Teacher* teachers, int num_tch, std::string path);
	//So we can write all of the attributes to the file
	friend void read_university(Subject*& subjects, int& num_sub, Student*& students, int& num_st, Teacher*& teachers, int& num_tch, std::string path);
	//So we can read all the attributes from the file
	friend class Teacher; //so Teacher can access grades

	bool operator==(const Student& s) const;
	bool operator!=(const Student& s) const;
	Student& operator=(const Student& s);

	void Set_first_name(std::string password, std::string firstname) override;
	void Set_last_name(std::string password, std::string lastname) override;
	void Set_day_of_birth(std::string password, int d_birth) override;
	void Set_month_of_birth(std::string password, int m_birth) override;
	void Set_year_of_birth(std::string password, int y_birth) override;
	void Set_sex(std::string password, Sex sex) override;

	Student(std::string firstname = "", std::string lastname = "", int d_birth = 0, int m_birth = 0, int y_birth = 0, Sex sex = f, std::string major = "", std::string password = "", int num_subjects = 0, Subject** taken_subject = NULL, int* grades = NULL);
	//first and last names, id and major can't start with '\x1E'
	//Password is "" by default
	Student(const Student& st);
	~Student();
	int Get_num_subjects() const;
	int Get_id() const;
	std::string Get_major() const;
	int num_of_credits() const; //Calculating total number of credits
	double GPA() const;
	std::string list_data(bool last_name_first = false, bool hun_format = false) const;
	std::string list_subjects() const;
	//Listing all the data of the student
	void Add_subject(std::string password, Subject& sub);
	void Remove_subject(std::string password, int index); //Index starts from 1
	void Set_major(std::string password, std::string major);
	//major can't start with '\x1E'
	void Reset_password(std::string current, std::string reseted);
	bool Validate_password(std::string password) const;
	void Change_ptr_subject(Subject* new_ptr);
};

class Teacher :public Person
{
	std::string faculty, password;
	Subject** given_subjects;
	int num_subjects, id;
	static int num_used_ids;
	static const char cipher_password;

	static int generate_id();
	std::string encrypt_password(std::string input) const;
public:

	friend void put_university(Subject* subjects, int num_sub, Student* students, int num_st, Teacher* teachers, int num_tch, std::string path);
	//So we can write all of the attributes to the file
	friend void read_university(Subject*& subjects, int& num_sub, Student*& students, int& num_st, Teacher*& teachers, int& num_tch, std::string path);
	//So we can read all the attributes from the file

	bool operator==(const Teacher& tch) const;
	bool operator!=(const Teacher& tch) const;
	Teacher& operator=(const Teacher& tch);

	void Set_first_name(std::string password, std::string firstname) override;
	void Set_last_name(std::string password, std::string lastname) override;
	void Set_day_of_birth(std::string password, int d_birth) override;
	void Set_month_of_birth(std::string password, int m_birth) override;
	void Set_year_of_birth(std::string password, int y_birth) override;
	void Set_sex(std::string password, Sex sex) override;

	Teacher(std::string firstname = "", std::string lastname = "", int d_birth = 0, int m_birth = 0, int y_birth = 0, Sex sex = f, std::string faculty = "", std::string password = "", int num_subjects = 0, Subject** given_subjects = NULL);
	//first and last names and faculty can't start with '\x1E'
	//Password is "" by default
	Teacher(const Teacher& tch);
	~Teacher();
	std::string Get_faculty() const;
	int Get_num_subjects() const;
	int Get_id() const;
	int Num_students() const; // Get total number of students
	int Num_students_subject(int index_sub) const; // Index starts from 1, get number of students in specific subject
	Subject Get_subject(int index_sub) const; // Index starts from 1 
	std::string Get_student(int index_sub, int index_st) const; // Index starts from 1
	std::string list_data(bool last_name_first = false, bool hun_format = false) const;
	//Listing all the data of the teacher
	std::string list_subjects() const;
	std::string list_students(int index_sub) const; //Index starts from 1
	void Set_faculty(std::string password, std::string faculty);
	//Faculty can't start with '\x1E'
	void Add_subject(std::string password, Subject& sub);
	void Remove_subject(std::string password, int index); //Index starts from 1
	void Set_grade(std::string password, Subject sub, Student& s, int grade) const;
	void Reset_password(std::string current, std::string reseted);
	bool Validate_password(std::string password) const;
	void Change_ptr_subject(Subject* new_ptr);
};
#endif 