#include "file_handling.h"

void put_university(Subject* subjects, int num_sub, Student* students, int num_st, Teacher* teachers, int num_tch, std::string path)
{
	std::ofstream fout;
	fout.open(path);
	if (!fout.is_open())
	{
		throw 1;
		return;
	}
	if (subjects == NULL && students == NULL && teachers == NULL)
	{
		return;
	}
	fout << '\x1E' << "sub" << std::endl;
	fout << num_sub << std::endl;
	for (int i = 0; i < num_sub; i++)
	{
		fout << subjects[i].title << std::endl;
		fout << subjects[i].num_credits << std::endl;
		fout << subjects[i].reg_lim << std::endl;
		fout << subjects[i].related << std::endl;
		fout << subjects[i].registered << std::endl;
		for (int k = 0; k < subjects[i].registered; k++)
		{
			fout << subjects[i].students[k] << std::endl;
		}
	}
	fout << '\x1E' << "st" << std::endl;
	fout << num_st << std::endl;
	fout << Student::num_used_ids << std::endl;
	for (int i = 0; i < num_st; i++)
	{
		fout << students[i].firstname << std::endl;
		fout << students[i].lastname << std::endl;
		fout << students[i].d_birth << std::endl;
		fout << students[i].m_birth << std::endl;
		fout << students[i].y_birth << std::endl;
		fout << (int)students[i].sex << std::endl;
		fout << students[i].num_subjects << std::endl;
		fout << students[i].id << std::endl;
		fout << students[i].major << std::endl;
		fout << students[i].password << std::endl;
		for (int j = 0; j < students[i].num_subjects; j++)
		{
			fout << students[i].grades[j] << std::endl;
		}
		for (int k = 0; k < students[i].num_subjects; k++)
		{
			fout << students[i].taken_subjects[k]->title << std::endl;
		}
	}
	fout << '\x1E' << "tch" << std::endl;
	fout << num_tch << std::endl;
	fout << Teacher::num_used_ids << std::endl;
	for (int i = 0; i < num_tch; i++)
	{
		fout << teachers[i].firstname << std::endl;
		fout << teachers[i].lastname << std::endl;
		fout << teachers[i].d_birth << std::endl;
		fout << teachers[i].m_birth << std::endl;
		fout << teachers[i].y_birth << std::endl;
		fout << (int)teachers[i].sex << std::endl;
		fout << teachers[i].faculty << std::endl;
		fout << teachers[i].num_subjects << std::endl;
		fout << teachers[i].password;
		if (i!=num_tch-1 || teachers[i].num_subjects!=0)
		{
			fout << std::endl;
		}
		for (int j = 0; j < teachers[i].num_subjects; j++)
		{
			fout << teachers[i].given_subjects[j]->title;
			if (i != num_tch - 1 || j != teachers[i].num_subjects - 1)
			{
				fout << std::endl;
			}
		}
	}
	fout.close();
}

void read_university(Subject*& subjects, int& num_sub, Student*& students, int& num_st, Teacher*& teachers, int& num_tch, std::string path)
{
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		throw 1;
		return;
	}
	std::string read;
	delete[] subjects;
	delete[] students;
	delete[] teachers;
	while (!fin.eof())
	{
		read = "";
		std::getline(fin, read);
		if (read == "\x1Esub")
		{
			std::getline(fin, read);
			num_sub = std::stoi(read);
			subjects = new Subject[num_sub];
			for (int i = 0; i < num_sub; i++)
			{
				std::getline(fin, read);
				subjects[i].title = read;
				std::getline(fin, read);
				subjects[i].num_credits = std::stoi(read);
				std::getline(fin, read);
				subjects[i].reg_lim = std::stoi(read);
				std::getline(fin, read);
				subjects[i].related = std::stoi(read);
				std::getline(fin, read);
				subjects[i].registered = std::stoi(read);
				subjects[i].students = new std::string[subjects[i].registered];
				for (int k = 0; k < subjects[i].registered; k++)
				{
					std::getline(fin, read);
					subjects[i].students[k] = read;
				}
			}
		}
		else if (read == "\x1Est")
		{
			std::getline(fin, read);
			num_st = std::stoi(read);
			students = new Student[num_st];
			std::getline(fin, read);
			Student::num_used_ids = std::stoi(read);
			for (int i = 0; i < num_st; i++)
			{
				std::getline(fin, read);
				students[i].firstname = read;
				std::getline(fin, read);
				students[i].lastname = read;
				std::getline(fin, read);
				students[i].d_birth = std::stoi(read);
				std::getline(fin, read);
				students[i].m_birth = std::stoi(read);
				std::getline(fin, read);
				students[i].y_birth = std::stoi(read);
				std::getline(fin, read);
				if (std::stoi(read) == 1)
				{
					students[i].sex = m;
				}
				else if (std::stoi(read) == 0)
				{
					students[i].sex = f;
				}
				else
				{
					throw 2;
				}
				std::getline(fin, read);
				students[i].num_subjects = std::stoi(read);
				students[i].grades = new int[students[i].num_subjects];
				students[i].taken_subjects = new Subject * [students[i].num_subjects];
				std::getline(fin, read);
				students[i].id = std::stoi(read);
				std::getline(fin, read);
				students[i].major = read;
				std::getline(fin, read);
				students[i].password = read;
				for (int j = 0; j < students[i].num_subjects; j++)
				{
					std::getline(fin, read);
					students[i].grades[j] = std::stoi(read);
				}
				for (int k = 0; k < students[i].num_subjects; k++)
				{
					std::getline(fin, read);
					for (int l = 0; l < num_sub; l++)
					{
						if (read == subjects[l].title)
						{
							students[i].taken_subjects[k] = &subjects[l];
							break;
						}
					}
				}
			}
		}
		else if (read == "\x1Etch")
		{
			std::getline(fin, read);
			num_tch = std::stoi(read);
			teachers = new Teacher[num_tch];
			std::getline(fin, read);
			Teacher::num_used_ids = std::stoi(read);
			for (int i = 0; i < num_tch; i++)
			{
				std::getline(fin, read);
				teachers[i].firstname = read;
				std::getline(fin, read);
				teachers[i].lastname = read;
				std::getline(fin, read);
				teachers[i].d_birth = std::stoi(read);
				std::getline(fin, read);
				teachers[i].m_birth = std::stoi(read);
				std::getline(fin, read);
				teachers[i].y_birth = std::stoi(read);
				std::getline(fin, read);
				if (std::stoi(read) == 1)
				{
					teachers[i].sex = m;
				}
				else if (std::stoi(read) == 0)
				{
					teachers[i].sex = f;
				}
				else
				{
					throw 2;
				}
				std::getline(fin, read);
				teachers[i].faculty = read;
				std::getline(fin, read);
				teachers[i].num_subjects = std::stoi(read);
				teachers[i].given_subjects = new Subject * [teachers[i].num_subjects];
				std::getline(fin, read);
				teachers[i].password = read;
				for (int j = 0; j < teachers[i].num_subjects; j++)
				{
					std::getline(fin, read);
					for (int k = 0; k < num_sub; k++)
					{
						if (read == subjects[k].title)
						{
							teachers[i].given_subjects[j] = &subjects[k];
							break;
						}
					}
				}
			}
		}
		else
		{
			throw 3;
		}
	}
	fin.close();
}