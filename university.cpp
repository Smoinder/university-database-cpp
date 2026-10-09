#include "university.h"

std::string format(int form, int num)
{
	std::string res = "";
	int digits;
	if (num == 0)
	{
		digits = 1;
	}
	else
	{
		int cpy = num;
		digits = 0;
		while (cpy != 0)
		{
			cpy /= 10;
			digits++;
		}
	}
	if (digits >= form)
	{
		return std::to_string(num);
	}
	int dif = form - digits;
	for (int i = 0; i < dif; i++)
	{
		res += "0";
	}
	res += std::to_string(num);
	return res;
}

std::string print(Subject* subjects, int num_sub, Student* students, int num_st, Teacher* teachers, int num_tch)
{
	std::string res;
	res += "Students:\n";
	for (int i = 0; i < num_st; i++)
	{
		res += std::to_string(i + 1);
		res += ".\n";
		res += students[i].list_data();
		res += "\n\n";
	}
	res += "\nSubjects:\n";
	for (int i = 0; i < num_sub; i++)
	{
		res += std::to_string(i + 1);
		res += ".\n";
		res += subjects[i].list_data();
		res += "\n\n";
	}
	res += "\nTeachers:\n";
	for (int i = 0; i < num_tch; i++)
	{
		res += std::to_string(i + 1);
		res += ".\n";
		res += teachers[i].list_data();
		res += "\n\n";
	}
	return res;
}

//Subject

bool Subject::operator==(const Subject& s) const
{
	if (title != s.title)
	{
		return false;
	}
	if (num_credits != s.num_credits)
	{
		return false;
	}
	if (registered != s.registered)
	{
		return false;
	}
	if (reg_lim != s.reg_lim)
	{
		return false;
	}
	if (related != s.related)
	{
		return false;
	}
	for (int i = 0; i < registered; i++)
	{
		if (students[i] != s.students[i])
		{
			return false;
		}
	}
	return true;
}

bool Subject::operator!=(const Subject& s) const
{
	return !(*this == s);
}

Subject& Subject::operator=(const Subject& s)
{
	if (*this == s)
	{
		return *this;
	}
	title = s.title;
	num_credits = s.num_credits;
	reg_lim = s.reg_lim;
	related = s.related;
	registered = s.registered;
	delete[] students;
	std::string* new_students = new std::string[s.registered];
	for (int i = 0; i < registered; i++)
	{
		new_students[i] = s.students[i];
	}
	students = new_students;
	return *this;
}

Subject::Subject(std::string title, int num_credits, int reg_lim, int registered, std::string* students)
{
	if (title[0] != '\x1E')
	{
		this->title = title;
	}
	else
	{
		int j;
		for (j = 0; title[j] == '\x1E'; j++);
		std::string res = title.substr(j);
		this->title = res;
	}
	if (num_credits >= 0)
	{
		this->num_credits = num_credits;
	}
	else
	{
		this->num_credits = 0;
	}
	if (reg_lim >= 0)
	{
		this->reg_lim = reg_lim;
	}
	else
	{
		this->reg_lim = 0;
	}
	this->related = 0;
	if (registered >= 0 && registered <= reg_lim)
	{
		this->registered = registered;
	}
	else
	{
		this->registered = 0;
	}
	std::string* new_students = new std::string[this->registered];
	for (int i = 0; i < this->registered; i++)
	{
		new_students[i] = students[i];
	}
	this->students = new_students;
}

Subject::Subject(const Subject& sub)
{
	title = sub.title;
	num_credits = sub.num_credits;
	reg_lim = sub.reg_lim;
	related = sub.related;
	registered = sub.registered;
	std::string* new_students = new std::string[sub.registered];
	for (int i = 0; i < registered; i++)
	{
		new_students[i] = sub.students[i];
	}
	students = new_students;
}

Subject::~Subject()
{
	delete[] students;
}

void Subject::Set_title(std::string title)
{
	if (title[0] != '\x1E')
	{
		this->title = title;
	}
	else
	{
		int j;
		for (j = 0; title[j] == '\x1E'; j++);
		std::string res = title.substr(j);
		this->title = res;
	}
}

void Subject::Set_num_credits(int num_credits)
{
	if (num_credits >= 0)
	{
		this->num_credits = num_credits;
	}
	else
	{
		this->num_credits = 0;
	}
}

void Subject::Set_reg_lim(int reg_lim)
{
	if (reg_lim >= 0)
	{
		this->reg_lim = reg_lim;
	}
	else
	{
		this->reg_lim = 0;
	}
}

std::string Subject::Get_title() const
{
	return title;
}

std::string Subject::list_data() const
{
	std::string res = "";
	res += title;
	res += '\n';
	res += "Number of credits: ";
	res += std::to_string(num_credits);
	res += "\nRegistration limit: ";
	res += std::to_string(reg_lim);
	res += ", Amount of students who took this subject: ";
	res += std::to_string(registered);
	return res;
}

std::string Subject::list_students() const
{
	std::string res = "";
	if (registered == 0)
	{
		res += "No one took this subject";
		return res;
	}
	for (int i = 0; i < registered; i++)
	{
		res += std::to_string(i + 1);
		res += ". ";
		res += this->students[i];
		if (i != registered - 1)
		{
			res += ", ";
		}
	}
	return res;
}

int Subject::Get_num_credits() const
{
	return num_credits;
}

int Subject::Get_reg_lim() const
{
	return reg_lim;
}

int Subject::Get_registered() const
{
	return registered;
}

int Subject::Get_related() const
{
	return related;
}

//Person

std::string Person::Get_name(bool last_name_first) const
{
	if (!last_name_first)
	{
		return firstname + " " + lastname;
	}
	return lastname + " " + firstname;
}

std::string Person::Get_first_name() const
{
	return firstname;
}

std::string Person::Get_last_name() const
{
	return lastname;
}

std::string Person::Get_birth_date(bool hun_format) const
{
	if (!hun_format)
	{
		return format(2, d_birth) + "." + format(2, m_birth) + "." + format(4, y_birth);
	}
	return format(4, y_birth) + "." + format(2, m_birth) + "." + format(2, d_birth);
}

int Person::Get_day_of_birth() const
{
	return d_birth;
}

int Person::Get_month_of_birth() const
{
	return m_birth;
}

int Person::Get_year_of_birth() const
{
	return y_birth;
}

Sex Person::Get_sex() const
{
	return sex;
}

//Student

int Student::num_used_ids = 0;

const char Student::cipher_password = 0xE;

int Student::generate_id()
{
	int res = num_used_ids;
	Student::num_used_ids++;
	return res;
}

std::string Student::encrypt_password(std::string input) const
{
	std::string output = input;
	int size = output.length();
	for (int i = 0; i < size; i++)
	{
		output[i] = input[i] ^ Student::cipher_password;
	}
	return output;
}


bool Student::operator==(const Student& s) const
{
	if (firstname != s.firstname)
	{
		return false;
	}
	if (lastname != s.lastname)
	{
		return false;
	}
	if (d_birth != s.d_birth)
	{
		return false;
	}
	if (m_birth != s.m_birth)
	{
		return false;
	}
	if (y_birth != s.y_birth)
	{
		return false;
	}
	if (sex != s.sex)
	{
		return false;
	}
	if (num_subjects != s.num_subjects)
	{
		return false;
	}
	for (int i = 0; i < num_subjects; i++)
	{
		if (taken_subjects[i] != s.taken_subjects[i])
		{
			return false;
		}
	}
	if (major != s.major)
	{
		return false;
	}
	return true;
}

bool Student::operator!=(const Student& s) const
{
	return !(*this == s);
}

Student& Student::operator=(const Student& s)
{
	if (*this == s)
	{
		return *this;
	}
	this->firstname = s.firstname;
	this->lastname = s.lastname;
	this->d_birth = s.d_birth;
	this->m_birth = s.m_birth;
	this->y_birth = s.y_birth;
	this->sex = s.sex;
	this->id = s.id;
	this->password = s.password;

	Subject** copy = new Subject * [s.num_subjects];
	for (int i = 0; i < s.num_subjects; i++)
	{
		copy[i] = s.taken_subjects[i];
	}
	delete[] taken_subjects;
	this->taken_subjects = copy;
	int* gcopy = new int[s.num_subjects];
	for (int i = 0; i < s.num_subjects; i++)
	{
		gcopy[i] = s.grades[i];
	}
	delete[] grades;
	this->grades = gcopy;
	this->num_subjects = s.num_subjects;
	this->major = s.major;
	this->id = s.id;
	this->password = s.password;
	return *this;
}

void Student::Set_first_name(std::string password, std::string firstname)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (firstname[0] != '\x1E')
	{
		this->firstname = firstname;
	}
	else
	{
		int j;
		for (j = 0; firstname[j] == '\x1E'; j++);
		std::string res = firstname.substr(j);
		this->firstname = res;
	}
}

void Student::Set_last_name(std::string password, std::string lastname)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (lastname[0] != '\x1E')
	{
		this->lastname = lastname;
	}
	else
	{
		int j;
		for (j = 0; lastname[j] == '\x1E'; j++);
		std::string res = lastname.substr(j);
		this->lastname = res;
	}
}

void Student::Set_day_of_birth(std::string password, int d_birth)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (d_birth >= 1 && d_birth <= 31)
	{
		this->d_birth = d_birth;
	}
	else
	{
		this->d_birth = 0;
	}
}

void Student::Set_month_of_birth(std::string password, int m_birth)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (m_birth >= 1 && m_birth <= 12)
	{
		this->m_birth = m_birth;
	}
	else
	{
		this->m_birth = 0;
	}
}

void Student::Set_year_of_birth(std::string password, int y_birth)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (y_birth >= 1920)
	{
		this->y_birth = y_birth;
	}
	else
	{
		this->y_birth = 0;
	}
}

void Student::Set_sex(std::string password, Sex sex)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	this->sex = sex;
}

Student::Student(std::string firstname, std::string lastname, int d_birth, int m_birth, int y_birth, Sex sex, std::string major, std::string password, int num_subjects, Subject** taken_subjects, int* grades) : taken_subjects(taken_subjects)
{
	if (firstname[0] != '\x1E')
	{
		this->firstname = firstname;
	}
	else
	{
		int j;
		for (j = 0; firstname[j] == '\x1E'; j++);
		std::string res = firstname.substr(j);
		this->firstname = res;
	}
	if (lastname[0] != '\x1E')
	{
		this->lastname = lastname;
	}
	else
	{
		int k;
		for (k = 0; lastname[k] == '\x1E'; k++);
		std::string res = lastname.substr(k);
		this->lastname = res;
	}
	if (d_birth >= 1 && d_birth <= 31)
	{
		this->d_birth = d_birth;
	}
	else
	{
		this->d_birth = 0;
	}
	if (m_birth >= 1 && m_birth <= 12)
	{
		this->m_birth = m_birth;
	}
	else
	{
		this->m_birth = 0;
	}
	if (y_birth >= 1920)
	{
		this->y_birth = y_birth;
	}
	else
	{
		this->y_birth = 0;
	}
	this->sex = sex;
	this->grades = grades;
	if (num_subjects>=0)
	{
		this->num_subjects = num_subjects;
	}
	else
	{
		this->num_subjects = 0;
	}
	this->id = generate_id();
	if (major[0] != '\x1E')
	{
		this->major = major;
	}
	else
	{
		int n;
		for (n = 0; major[n] == '\x1E'; n++);
		std::string res = major.substr(n);
		this->major = res;
	}
	this->password = encrypt_password(password);
}

Student::Student(const Student& st)
{
	this->firstname = st.firstname;
	this->lastname = st.lastname;
	this->d_birth = st.d_birth;
	this->m_birth = st.m_birth;
	this->y_birth = st.y_birth;
	this->sex = st.sex;
	this->id = st.id;
	this->password = st.password;

	Subject** copy = new Subject*[st.num_subjects];
	for (int i = 0; i < st.num_subjects; i++)
	{
		copy[i] = st.taken_subjects[i];
	}
	this->taken_subjects = copy;
	int* gcopy = new int[st.num_subjects];
	for (int i = 0; i < st.num_subjects; i++)
	{
		gcopy[i] = st.grades[i];
	}
	this->grades = gcopy;
	this->num_subjects = st.num_subjects;
	this->id = generate_id();
	this->major = st.major;
}

Student::~Student()
{
	delete[] taken_subjects;
	delete[] grades;
}

int Student::Get_num_subjects() const
{
	return num_subjects;
}

int Student::Get_id() const
{
	return id;
}

std::string Student::Get_major() const
{
	return major;
}

int Student::num_of_credits() const
{
	int res = 0;
	for (int i = 0; i < num_subjects; i++)
	{
		res += taken_subjects[i]->num_credits;
	}
	return res;
}

double Student::GPA() const
{
	double gpa = 0;
	int cnt_of_sbjct_wthout_grade = 0;
	for (int i = 0; i < num_subjects; i++)
	{
		if (grades[i] != 0)
		{
			gpa += grades[i];
		}
		else
		{
			cnt_of_sbjct_wthout_grade++;
		}
	}
	if (num_subjects - cnt_of_sbjct_wthout_grade != 0)
	{
		gpa /= num_subjects - cnt_of_sbjct_wthout_grade;
	}
	return gpa;
}

std::string Student::list_data(bool last_name_first, bool hun_format) const
{
	std::string res = "";
	res += this->Get_name(last_name_first);
	res += "\nDate of birth : ";
	res += this->Get_birth_date(hun_format);
	res += "\nSex: ";
	if (sex == f)
	{
		res += "female";
	}
	else
	{
		res += "male";
	}
	res += "\nID: ";
	res += std::to_string(id);
	res += "\nMajor: ";
	res += major;
	res += "\nTaken subjects:\n";
	for (int i = 0; i < num_subjects; i++)
	{
		res += std::to_string(i + 1);
		res += ". ";
		res += taken_subjects[i]->Get_title();
		if (grades[i] == 0)
		{
			if (i != num_subjects - 1)
			{
				res += " : not evaluated, ";
			}
			else
			{
				res += " : not evaluated";
			}
		}
		else if (grades[i] >= 1 && grades[i] <= 5)
		{
			res += " : ";
			res += std::to_string(grades[i]);
			if (i != num_subjects - 1)
			{
				res += ", ";
			}
		}
	}
	res += "\nTotal number of credits: ";
	res += std::to_string(this->num_of_credits());
	res += "\nGPA: ";
	res += std::to_string(this->GPA());
	return res;
}

std::string Student::list_subjects() const
{
	std::string res = "";
	for (int i = 0; i < num_subjects; i++)
	{
		res += std::to_string(i + 1);
		res += ". ";
		res += this->taken_subjects[i]->title;
		if (i != num_subjects - 1)
		{
			res += "\n";
		}
	}
	return res;
}

void Student::Add_subject(std::string password, Subject& sub)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	for (int i = 0; i < num_subjects; i++)
	{
		if (sub == *taken_subjects[i])
		{
			return;
		}
	}
	if (sub.registered >= sub.reg_lim)
	{
		return;
	}
	Subject** new_subjects = new Subject*[num_subjects + 1];
	int* new_grades = new int[num_subjects + 1];
	std::string* new_students = new std::string[sub.registered + 1];
	for (int i = 0; i < num_subjects; i++)
	{
		new_subjects[i] = taken_subjects[i];
		new_grades[i] = grades[i];
	}
	for (int i = 0; i < sub.registered; i++)
	{
		new_students[i] = sub.students[i];
	}
	new_students[sub.registered] = this->firstname + " " + this->lastname;
	sub.registered++;
	sub.related++;
	delete[] sub.students;
	sub.students = new_students;
	new_subjects[num_subjects] = &sub;
	new_grades[num_subjects] = 0;
	delete[] taken_subjects;
	delete[] grades;
	num_subjects++;
	grades = new_grades;
	taken_subjects = new_subjects;
}

void Student::Remove_subject(std::string password, int index)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	index--;
	if (index < 0 || index>=num_subjects)
	{
		return;
	}
	std::string* new_students = new std::string [taken_subjects[index]->registered - 1];
	for (int i = 0, j = 0; i < taken_subjects[index]->registered; i++)
	{
		if (taken_subjects[index]->students[i] != this->Get_name())
		{
			new_students[j] = taken_subjects[index]->students[i];
			j++;
		}
	}
	taken_subjects[index]->registered--;
	taken_subjects[index]->related--;
	delete[] taken_subjects[index]->students;
	taken_subjects[index]->students = new_students;
	Subject** new_subjects = new Subject*[num_subjects - 1];
	int* new_grades = new int[num_subjects - 1];
	for (int i = 0, j = 0; i < num_subjects; i++)
	{
		if (i != index)
		{
			new_subjects[j] = taken_subjects[i];
			new_grades[j] = grades[i];
			j++;
		}
	}
	delete[] taken_subjects;
	delete[] grades;
	num_subjects--;
	taken_subjects = new_subjects;
	grades = new_grades;
}

void Student::Set_major(std::string password, std::string major)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (major[0] != '\x1E')
	{
		this->major = major;
	}
	else
	{
		int j;
		for (j = 0; major[j] == '\x1E'; j++);
		std::string res = major.substr(j);
		this->major = res;
	}
}

void Student::Reset_password(std::string current, std::string reseted)
{
	if (this->password != this->encrypt_password(current))
	{
		throw 0;
		return;
	}
	this->password = this->encrypt_password(reseted);
}

bool Student::Validate_password(std::string password) const
{
	if (this->password != this->encrypt_password(password))
	{
		return false;
	}
	return true;
}

void Student::Change_ptr_subject(Subject* new_ptr)
{
	int i;
	for (i = 0; i < num_subjects; i++)
	{
		if (*new_ptr == *taken_subjects[i])
		{
			taken_subjects[i] = new_ptr;
		}
	}
}

//Teacher

int Teacher::num_used_ids = 0;

const char Teacher::cipher_password = 0xF;

int Teacher::generate_id()
{
	int res = num_used_ids;
	Teacher::num_used_ids++;
	return res;
}

std::string Teacher::encrypt_password(std::string input) const
{
	std::string output = input;
	int size = output.length();
	for (int i = 0; i < size; i++)
	{
		output[i] = input[i] ^ Teacher::cipher_password;
	}
	return output;
}

bool Teacher::operator==(const Teacher& tch) const
{
	if (firstname != tch.firstname)
	{
		return false;
	}
	if (lastname != tch.lastname)
	{
		return false;
	}
	if (d_birth != tch.d_birth)
	{
		return false;
	}
	if (m_birth != tch.m_birth)
	{
		return false;
	}
	if (y_birth != tch.y_birth)
	{
		return false;
	}
	if (sex != tch.sex)
	{
		return false;
	}
	if (faculty != tch.faculty)
	{
		return false;
	}
	if (num_subjects != tch.num_subjects)
	{
		return false;
	}
	for (int i = 0; i < num_subjects; i++)
	{
		if (given_subjects[i] != tch.given_subjects[i])
		{
			return false;
		}
	}
	return true;
}

bool Teacher::operator!=(const Teacher& tch) const
{
	return !(*this == tch);
}

Teacher& Teacher::operator=(const Teacher& tch)
{
	if (*this == tch)
	{
		return *this;
	}
	this->firstname = tch.firstname;
	this->lastname = tch.lastname;
	this->d_birth = tch.d_birth;
	this->m_birth = tch.m_birth;
	this->y_birth = tch.y_birth;
	this->sex = tch.sex;
	this->id = id;
	this->password = password;

	Subject** copy = new Subject * [tch.num_subjects];
	for (int i = 0; i < tch.num_subjects; i++)
	{
		copy[i] = tch.given_subjects[i];
	}
	delete[] given_subjects;
	this->given_subjects = copy;
	this->faculty = tch.faculty;
	this->num_subjects = tch.num_subjects;
	this->id = tch.id;
	this->password = tch.password;
	return *this;
}

void Teacher::Set_first_name(std::string password, std::string firstname)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (firstname[0] != '\x1E')
	{
		this->firstname = firstname;
	}
	else
	{
		int j;
		for (j = 0; firstname[j] == '\x1E'; j++);
		std::string res = firstname.substr(j);
		this->firstname = res;
	}
}

void Teacher::Set_last_name(std::string password, std::string lastname)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (lastname[0] != '\x1E')
	{
		this->lastname = lastname;
	}
	else
	{
		int j;
		for (j = 0; lastname[j] == '\x1E'; j++);
		std::string res = lastname.substr(j);
		this->lastname = res;
	}
}

void Teacher::Set_day_of_birth(std::string password, int d_birth)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (d_birth >= 1 && d_birth <= 31)
	{
		this->d_birth = d_birth;
	}
	else
	{
		this->d_birth = 0;
	}
}

void Teacher::Set_month_of_birth(std::string password, int m_birth)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (m_birth >= 1 && m_birth <= 12)
	{
		this->m_birth = m_birth;
	}
	else
	{
		this->m_birth = 0;
	}
}

void Teacher::Set_year_of_birth(std::string password, int y_birth)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (y_birth >= 1920)
	{
		this->y_birth = y_birth;
	}
	else
	{
		this->y_birth = 0;
	}
}

void Teacher::Set_sex(std::string password, Sex sex)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	this->sex = sex;
}

Teacher::Teacher(std::string firstname, std::string lastname, int d_birth, int m_birth, int y_birth, Sex sex, std::string faculty, std::string password, int num_subjects, Subject** given_subjects) : given_subjects(given_subjects)
{
	if (firstname[0] != '\x1E')
	{
		this->firstname = firstname;
	}
	else
	{
		int j;
		for (j = 0; firstname[j] == '\x1E'; j++);
		std::string res = firstname.substr(j);
		this->firstname = res;
	}
	if (lastname[0] != '\x1E')
	{
		this->lastname = lastname;
	}
	else
	{
		int k;
		for (k = 0; lastname[k] == '\x1E'; k++);
		std::string res = lastname.substr(k);
		this->lastname = res;
	}
	if (d_birth >= 1 && d_birth <= 31)
	{
		this->d_birth = d_birth;
	}
	else
	{
		this->d_birth = 0;
	}
	if (m_birth >= 1 && m_birth <= 12)
	{
		this->m_birth = m_birth;
	}
	else
	{
		this->m_birth = 0;
	}
	if (y_birth >= 1920)
	{
		this->y_birth = y_birth;
	}
	else
	{
		this->y_birth = 0;
	}
	this->sex = sex;
	if (faculty[0] != '\x1E')
	{
		this->faculty = faculty;
	}
	else
	{
		int l;
		for (l = 0; faculty[l] == '\x1E'; l++);
		std::string res = faculty.substr(l);
		this->faculty = res;
	}
	this->password = this->encrypt_password(password);
	if (num_subjects >= 0)
	{
		this->num_subjects = num_subjects;
	}
	else
	{
		this->num_subjects = 0;
	}
	this->id = this->generate_id();
}

Teacher::Teacher(const Teacher& tch)
{
	this->firstname = tch.firstname;
	this->lastname = tch.lastname;
	this->d_birth = tch.d_birth;
	this->m_birth = tch.m_birth;
	this->y_birth = tch.y_birth;
	this->sex = tch.sex;
	this->id = tch.id;
	this->password = tch.password;

	Subject** copy = new Subject*[tch.num_subjects];
	for (int i = 0; i < tch.num_subjects; i++)
	{
		copy[i] = tch.given_subjects[i];
	}
	this->given_subjects = copy;
	this->faculty = tch.faculty;
	this->num_subjects = tch.num_subjects;
}

Teacher::~Teacher()
{
	delete[] given_subjects;
}

std::string Teacher::Get_faculty() const
{
	return faculty;
}

int Teacher::Get_num_subjects() const
{
	return num_subjects;
}

int Teacher::Get_id() const
{
	return id;
}

int Teacher::Num_students() const
{
	int res = 0;
	for (int i = 0; i < num_subjects; i++)
	{
		res += given_subjects[i]->registered;
	}
	return res;
}

int Teacher::Num_students_subject(int index_sub) const
{
	index_sub--;
	if (index_sub < 0 || index_sub >= num_subjects)
	{
		return 0;
	}
	return this->given_subjects[index_sub]->Get_registered();
}

Subject Teacher::Get_subject(int index_sub) const
{
	index_sub--;
	if (index_sub < 0 || index_sub >= num_subjects)
	{
		return Subject();
	}
	return *this->given_subjects[index_sub];
}

std::string Teacher::Get_student(int index_sub, int index_st) const
{
	index_sub--;
	index_st--;
	if (index_sub < 0 || index_sub >= num_subjects)
	{
		return "";
	}
	if (index_st < 0 || index_st >= this->given_subjects[index_sub]->registered)
	{
		return "";
	}
	return this->given_subjects[index_sub]->students[index_st];
}

std::string Teacher::list_data(bool last_name_first, bool hun_format) const
{
	std::string res = "";
	res += this->Get_name(last_name_first);
	res += "\nDate of birth : ";
	res += this->Get_birth_date(hun_format);
	res += "\nSex: ";
	if (sex == f)
	{
		res += "female";
	}
	else
	{
		res += "male";
	}
	res += "\nID: ";
	res += std::to_string(id);
	res += "\nFaculty: ";
	res += faculty;
	res += "\nSubjects:\n";
	for (int i = 0; i < num_subjects; i++)
	{
		res += std::to_string(i + 1);
		res += ". ";
		res += given_subjects[i]->title;
		if (i != num_subjects - 1)
		{
			res += ", ";
		}
	}
	return res;
}

std::string Teacher::list_subjects() const
{
	std::string res = "";
	for (int i = 0; i < num_subjects; i++)
	{
		res += std::to_string(i + 1);
		res += ". ";
		res += this->given_subjects[i]->title;
		if (i != num_subjects - 1)
		{
			res += "\n";
		}
	}
	return res;
}

std::string Teacher::list_students(int index_sub) const
{
	index_sub--;
	if (index_sub<0 || index_sub>=num_subjects)
	{
		return "";
	}
	return this->given_subjects[index_sub]->list_students();
}

void Teacher::Set_faculty(std::string password, std::string faculty)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	if (faculty[0] != '\x1E')
	{
		this->faculty = faculty;
	}
	else
	{
		int j;
		for (j = 0; faculty[j] == '\x1E'; j++);
		std::string res = faculty.substr(j);
		this->faculty = res;
	}
}

void Teacher::Add_subject(std::string password, Subject& sub)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	for (int i = 0; i < num_subjects; i++)
	{
		if (sub == *given_subjects[i])
		{
			return;
		}
	}
	Subject** new_subjects = new Subject*[num_subjects + 1];
	for (int i = 0; i < num_subjects; i++)
	{
		new_subjects[i] = this->given_subjects[i];
	}
	new_subjects[num_subjects] = &sub;
	delete[] given_subjects;
	this->num_subjects++;
	sub.related++;
	this->given_subjects = new_subjects;
}

void Teacher::Remove_subject(std::string password, int index)
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	index--;
	if (index < 0 || index >= num_subjects)
	{
		return;
	}
	Subject** new_subjects = new Subject*[num_subjects - 1];
	for (int i = 0, j = 0; i < num_subjects; i++)
	{
		if (i != index)
		{
			new_subjects[j] = given_subjects[i];
			j++;
		}
	}
	given_subjects[index]->related--;
	delete[] given_subjects;
	num_subjects--;
	given_subjects = new_subjects;
}

void Teacher::Set_grade(std::string password, Subject sub, Student& s, int grade) const
{
	if (this->password != this->encrypt_password(password))
	{
		throw 0;
		return;
	}
	int i;
	for (i = 0; i < this->num_subjects; i++)
	{
		if (sub == *(this->given_subjects[i]))
		{
			break;
		}
	}
	if (i == this->num_subjects)
	{
		throw 1;
		return;
	}
	int index_grade;
	for (index_grade = 0; index_grade < s.num_subjects; index_grade++)
	{
		if (sub == *(s.taken_subjects[index_grade]))
		{
			break;
		}
	}
	if (index_grade == s.num_subjects)
	{
		return;
	}
	if (grade >= 1 && grade <= 5)
	{
		s.grades[index_grade] = grade;
	}
	else
	{
		throw 2;
		return;
	}
}

void Teacher::Reset_password(std::string current, std::string reseted)
{
	if (this->password != this->encrypt_password(current))
	{
		throw 0;
		return;
	}
	this->password = this->encrypt_password(reseted);
}

bool Teacher::Validate_password(std::string password) const
{
	if (this->password != this->encrypt_password(password))
	{
		return false;
	}
	return true;
}

void Teacher::Change_ptr_subject(Subject* new_ptr)
{
	int i;
	for (i = 0; i < num_subjects; i++)
	{
		if (*new_ptr == *given_subjects[i])
		{
			given_subjects[i] = new_ptr;
		}
	}
}