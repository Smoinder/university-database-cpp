#include <iostream>
#include "university.h"
#include "file_handling.h"

using namespace std;

int main()
{
	int choice;
	Student* students = NULL;
	int num_st = 0;
	Teacher* teachers = NULL;
	int num_tch = 0;
	Subject* subjects = NULL;
	int num_sub = 0;
	while (true)
	{
		cout << "What do you want to do?\n1.Read data from the file\n2.Save data\n3.Modify students\n4.Modify teachers\n5.Modify subjects\n6.Leave\n";
		cin >> choice;
		if (choice == 1)
		{
			string path;
			cout << "Write the path of your file(if you want to use standard one, press enter):\n";
			cin.ignore(); //Killing last '\n' in the buffer
			getline(cin, path);
			if (path == "")
			{
				bool detect_error = false;
				try
				{
					read_university(subjects, num_sub, students, num_st, teachers, num_tch);
				}
				catch (int e)
				{
					detect_error = true;
					if (e == 1)
					{
						system("cls");
						cout << "Wrong path, reading the file ended with error code " << e << endl;
					}
					else if (e == 2 || e == 3)
					{
						system("cls");
						cout << "Wrong file format, reading the file ended with error code " << e << endl;
					}
				}
				if (!detect_error)
				{
					system("cls");
					cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
				}
			}
			else
			{
				bool detect_error = false;
				try
				{
					read_university(subjects, num_sub, students, num_st, teachers, num_tch, path);
				}
				catch (int e)
				{
					detect_error = true;
					if (e == 1)
					{
						system("cls");
						cout << "Wrong path, reading the file ended with error code " << e << endl;
					}
					else if (e == 2 || e == 3)
					{
						system("cls");
						cout << "Wrong file format, reading the file ended with error code " << e << endl;
					}
				}
				if (!detect_error)
				{
					system("cls");
					cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
				}
			}
		}
		else if (choice == 2)
		{
			string path;
			cout << "Write the path of your file(if you want to use standard one, press enter):\n";
			cin.ignore(); //Killing last '\n' in the buffer
			getline(cin, path);
			if (path == "")
			{
				bool detect_error = false;
				try
				{
					put_university(subjects, num_sub, students, num_st, teachers, num_tch);
				}
				catch (int e)
				{
					detect_error = true;
					system("cls");
					cout << "Wrong path, openning the file ended with error code " << e << endl;
				}
				if (!detect_error)
				{
					system("cls");
					cout << "Data has been saved successfully\n";
				}
			}
			else
			{
				bool detect_error = false;
				try
				{
					put_university(subjects, num_sub, students, num_st, teachers, num_tch, path);
				}
				catch (int e)
				{
					detect_error = true;
					system("cls");
					cout << "Wrong path, openning the file ended with error code " << e << endl;
				}
				if (!detect_error)
				{
					system("cls");
					cout << "Data has been saved successfully\n";
				}
			}
		}
		else if (choice == 3)
		{
			system("cls");
			for (int i = 0; i < num_st; i++)
			{
				cout << i+1 << ". " << students[i].list_data() << endl << endl;
			}
			cout << "What do you want to do?\n1.Add new student\n2.Modify specific student\n3.Leave\n";
			cin >> choice;
			if (choice == 1)
			{
				Student New;
				string name;
				cout << "First name of new student: ";
				cin.ignore();
				getline(cin, name);
				New.Set_first_name("", name);
				cout << "Last name of new student: ";
				getline(cin, name);
				New.Set_last_name("", name);
				int day;
				cout << "Day of birth of new student: ";
				cin >> day;
				New.Set_day_of_birth("", day);
				cout << "Month of birth of new student: ";
				cin >> day;
				New.Set_month_of_birth("", day);
				cout << "Year of birth of new student: ";
				cin >> day;
				New.Set_year_of_birth("", day);
				cout << "Sex of new student(0 - female, 1 - male): ";
				cin >> day;
				New.Set_sex("", (Sex)day);
				cout << "Major of new student: ";
				cin.ignore();
				getline(cin, name);
				New.Set_major("", name);
				cout << "Password of new student: ";
				getline(cin, name);
				New.Reset_password("", name);

				Student* incremented = new Student[num_st + 1];
				for (int i = 0; i < num_st; i++)
				{
					incremented[i] = students[i];
				}
				incremented[num_st] = New;
				delete[] students;
				num_st++;
				students = incremented;
				system("cls");
				cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
			}
			else if (choice == 2)
			{
				cout << "Write the index of the student you want modify: ";
				int index;
				cin >> index;
				index--;
				bool correct_index = false;
				if (index >= 0 && index < num_st)
				{
					correct_index = true;
				}
				if (!correct_index)
				{
					system("cls");
					cout << "Worng index\n";
				}
				else
				{
					cout << "What do you want to do with this student?\n1.Delete\n2.Change first name\n3.Change last name\n4.Change day of birth\n5.Change month of birth\n6.Change year of birth\n7.Change sex\n8.Change major\n9.Change password\n10.Register for new subject\n11.Drop the subject\n12.Leave\n";
					cin >> choice;
					if (choice == 1)
					{
						cout << "Write the password of this student: ";
						cin.ignore();
						string password;
						getline(cin, password);
						if (students[index].Validate_password(password))
						{
							for (int i = 0; i < students[index].Get_num_subjects(); i++)
							{
								students[index].Remove_subject(password, i + 1);
							}
							Student* decremented = new Student[num_st - 1];
							for (int i = 0, j = 0; i < num_st; i++)
							{
								if (i != index)
								{
									decremented[j] = students[i];
									j++;
								}
							}
							delete[] students;
							num_st--;
							students = decremented;
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
						else
						{
							system("cls");
							cout << "Wrong password\n";
						}
					}
					else if (choice == 2)
					{
						string name, password;
						cout << "Write new first name: ";
						cin.ignore();
						getline(cin, name);
						cout << "Write the password: ";
						getline(cin, password);
						bool detect_error = false;
						try
						{
							students[index].Set_first_name(password, name);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 3)
					{
						string name, password;
						cout << "Write new last name: ";
						cin.ignore();
						getline(cin, name);
						cout << "Write the password: ";
						getline(cin, password);
						bool detect_error = false;
						try
						{
							students[index].Set_last_name(password, name);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 4)
					{
						int day;
						string password;
						cout << "Write new day of birth: ";
						cin >> day;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							students[index].Set_day_of_birth(password, day);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 5)
					{
						int month;
						string password;
						cout << "Write new month of birth: ";
						cin >> month;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							students[index].Set_month_of_birth(password, month);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 6)
					{
						int year;
						string password;
						cout << "Write new year of birth: ";
						cin >> year;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							students[index].Set_year_of_birth(password, year);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 7)
					{
						int s;
						string password;
						cout << "Write new sex(0 - female, 1 - male): ";
						cin >> s;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							students[index].Set_sex(password, (Sex) s);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 8)
					{
						string major, password;
						cout << "Write new major: ";
						cin.ignore();
						getline(cin, major);
						cout << "Write the password: ";
						getline(cin, password);
						bool detect_error = false;
						try
						{
							students[index].Set_major(password, major);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 9)
					{
						string new_pass, old;
						cout << "Write new password: ";
						cin.ignore();
						getline(cin, new_pass);
						cout << "Write the old password: ";
						getline(cin, old);
						bool detect_error = false;
						try
						{
							students[index].Reset_password(old, new_pass);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << "Password was changed successfully\n";
						}
					}
					else if (choice == 10)
					{
						system("cls");
						for (int i = 0; i < num_sub; i++)
						{
							cout << i + 1 << ". " << subjects[i].Get_title() << endl;
						}
						cout << "\nWrite the index of the subject you want register to: ";
						int index_sub;
						cin >> index_sub;
						index_sub--;
						if (index_sub >= 0 && index_sub < num_sub)
						{
							cout << "Write the password of the student: ";
							string password;
							cin.ignore();
							getline(cin, password);
							bool detect_error = false;
							try
							{
								students[index].Add_subject(password, subjects[index_sub]);
							}
							catch (int e)
							{
								detect_error = true;
								system("cls");
								cout << "Wrong password\n";
							}
							if (!detect_error)
							{
								system("cls");
								cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
							}
						}
						else
						{
							system("cls");
							cout << "Wrong index\n";
						}
					}
					else if (choice==11)
					{
						system("cls");
						cout << students[index].list_subjects() << endl << endl;
						cout << "Write the index of the subject you want to drop: ";
						int index_sub;
						cin >> index_sub;
						if (index_sub >= 1 && index_sub <= students[index].Get_num_subjects())
						{
							cout << "Write the password of the student: ";
							string password;
							cin.ignore();
							getline(cin, password);
							bool detect_error = false;
							try
							{
								students[index].Remove_subject(password, index_sub);
							}
							catch (int e)
							{
								detect_error = true;
								system("cls");
								cout << "Wrong password\n";
							}
							if (!detect_error)
							{
								system("cls");
								cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
							}
						}
						else
						{
							system("cls");
							cout << "Wrong index\n";
						}
					}
					else
					{
						system("cls");
					}
				}
			}
			else
			{
				system("cls");
			}
		}
		else if (choice == 4)
		{
			system("cls");
			for (int i = 0; i < num_tch; i++)
			{
				cout << i + 1 << ". " << teachers[i].list_data() << endl << endl;
			}
			cout << "What do you want to do?\n1.Add new teacher\n2.Modify specific teacher\n3.Leave\n";
			cin >> choice;
			if (choice == 1)
			{
				Teacher New;
				string name;
				cout << "First name of new teacher: ";
				cin.ignore();
				getline(cin, name);
				New.Set_first_name("", name);
				cout << "Last name of new teacher: ";
				getline(cin, name);
				New.Set_last_name("", name);
				int day;
				cout << "Day of birth of new teacher: ";
				cin >> day;
				New.Set_day_of_birth("", day);
				cout << "Month of birth of new teacher: ";
				cin >> day;
				New.Set_month_of_birth("", day);
				cout << "Year of birth of new teacher: ";
				cin >> day;
				New.Set_year_of_birth("", day);
				cout << "Sex of new teacher(0 - female, 1 - male): ";
				cin >> day;
				New.Set_sex("", (Sex)day);
				cout << "Faculty of new teacher: ";
				cin.ignore();
				getline(cin, name);
				New.Set_faculty("", name);
				cout << "Password of new teacher: ";
				getline(cin, name);
				New.Reset_password("", name);

				Teacher* incremented = new Teacher[num_tch + 1];
				for (int i = 0; i < num_tch; i++)
				{
					incremented[i] = teachers[i];
				}
				incremented[num_tch] = New;
				delete[] teachers;
				num_tch++;
				teachers = incremented;
				system("cls");
				cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
			}
			else if (choice == 2)
			{
				cout << "Write the index of the teacher you want modify: ";
				int index;
				cin >> index;
				index--;
				bool correct_index = false;
				if (index >= 0 && index < num_tch)
				{
					correct_index = true;
				}
				if (!correct_index)
				{
					system("cls");
					cout << "Worng index\n";
				}
				else
				{
					cout << "What do you want to do with this teacher?\n1.Delete\n2.Change first name\n3.Change last name\n4.Change day of birth\n5.Change month of birth\n6.Change year of birth\n7.Change sex\n8.Change faculty\n9.Change password\n10.Take new subject\n11.Drop the subject\n12.Set the grade for a student\n13.Leave\n";
					cin >> choice;
					if (choice == 1)
					{
						cout << "Write the password of this teacher: ";
						cin.ignore();
						string password;
						getline(cin, password);
						if (teachers[index].Validate_password(password))
						{
							Teacher* decremented = new Teacher[num_tch - 1];
							for (int i = 0, j = 0; i < num_tch; i++)
							{
								if (i != index)
								{
									decremented[j] = teachers[i];
									j++;
								}
							}
							delete[] teachers;
							num_tch--;
							teachers = decremented;
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
						else
						{
							system("cls");
							cout << "Wrong password\n";
						}
					}
					else if (choice == 2)
					{
						string name, password;
						cout << "Write new first name: ";
						cin.ignore();
						getline(cin, name);
						cout << "Write the password: ";
						getline(cin, password);
						bool detect_error = false;
						try
						{
							teachers[index].Set_first_name(password, name);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 3)
					{
						string name, password;
						cout << "Write new last name: ";
						cin.ignore();
						getline(cin, name);
						cout << "Write the password: ";
						getline(cin, password);
						bool detect_error = false;
						try
						{
							teachers[index].Set_last_name(password, name);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 4)
					{
						int day;
						string password;
						cout << "Write new day of birth: ";
						cin >> day;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							teachers[index].Set_day_of_birth(password, day);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 5)
					{
						int month;
						string password;
						cout << "Write new month of birth: ";
						cin >> month;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							teachers[index].Set_month_of_birth(password, month);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 6)
					{
						int year;
						string password;
						cout << "Write new year of birth: ";
						cin >> year;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							teachers[index].Set_year_of_birth(password, year);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 7)
					{
						int s;
						string password;
						cout << "Write new sex(0 - female, 1 - male): ";
						cin >> s;
						cout << "Write the password: ";
						cin.ignore();
						getline(cin, password);
						bool detect_error = false;
						try
						{
							teachers[index].Set_sex(password, (Sex)s);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 8)
					{
						string faculty, password;
						cout << "Write new faculty: ";
						cin.ignore();
						getline(cin, faculty);
						cout << "Write the password: ";
						getline(cin, password);
						bool detect_error = false;
						try
						{
							teachers[index].Set_faculty(password, faculty);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
					}
					else if (choice == 9)
					{
						string new_pass, old;
						cout << "Write new password: ";
						cin.ignore();
						getline(cin, new_pass);
						cout << "Write the old password: ";
						getline(cin, old);
						bool detect_error = false;
						try
						{
							teachers[index].Reset_password(old, new_pass);
						}
						catch (int e)
						{
							detect_error = true;
							system("cls");
							cout << "Wrong password\n";
						}
						if (!detect_error)
						{
							system("cls");
							cout << "Password was changed successfully\n";
						}
					}
					else if (choice == 10)
					{
						system("cls");
						for (int i = 0; i < num_sub; i++)
						{
							cout << i + 1 << ". " << subjects[i].Get_title() << endl;
						}
						cout << "\nWrite the index of the subject you want to take: ";
						int index_sub;
						cin >> index_sub;
						index_sub--;
						if (index_sub >= 0 && index_sub < num_sub)
						{
							cout << "Write the password of the teacher: ";
							string password;
							cin.ignore();
							getline(cin, password);
							bool detect_error = false;
							try
							{
								teachers[index].Add_subject(password, subjects[index_sub]);
							}
							catch (int e)
							{
								detect_error = true;
								system("cls");
								cout << "Wrong password\n";
							}
							if (!detect_error)
							{
								system("cls");
								cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
							}
						}
						else
						{
							system("cls");
							cout << "Wrong index\n";
						}
					}
					else if (choice == 11)
					{
						system("cls");
						cout << teachers[index].list_subjects() << endl << endl;
						cout << "Write the index of the subject you want to drop: ";
						int index_sub;
						cin >> index_sub;
						if (index_sub >= 1 && index_sub <= teachers[index].Get_num_subjects())
						{
							cout << "Write the password of the teacher: ";
							string password;
							cin.ignore();
							getline(cin, password);
							bool detect_error = false;
							try
							{
								teachers[index].Remove_subject(password, index_sub);
							}
							catch (int e)
							{
								detect_error = true;
								system("cls");
								cout << "Wrong password\n";
							}
							if (!detect_error)
							{
								system("cls");
								cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
							}
						}
						else
						{
							system("cls");
							cout << "Wrong index\n";
						}
					}
					else if (choice == 12)
					{
						system("cls");
						cout << teachers[index].list_subjects() << endl << endl;
						cout << "Write the index of the subject in which you want to grade a student: ";
						int index_sub;
						cin >> index_sub;
						if (index_sub >= 1 && index_sub <= teachers[index].Get_num_subjects())
						{
							cout << teachers[index].list_students(index_sub) << endl << endl;
							cout << "Write the index of the student which you want to give a grade: ";
							int index_st;
							cin >> index_st;
							if (index_st >= 1 && index_st <= teachers[index].Num_students_subject(index_sub))
							{
								cout << "Write the grade you want to set: ";
								int grade;
								cin >> grade;
								cout << "Write the password of the teacher: ";
								string password;
								cin.ignore();
								getline(cin, password);
								bool detect_error = false;
								int index_student;
								for (int i = 0; i < num_st; i++)
								{
									if (teachers[index].Get_student(index_sub, index_st) == students[i].Get_name())
									{
										index_student = i;
									}
								}
								try
								{
									teachers[index].Set_grade(password, teachers[index].Get_subject(index_sub), students[index_student], grade);
								}
								catch (int e)
								{
									detect_error = true;
									system("cls");
									if (e == 0)
									{
										cout << "Wrong password\n";
									}
									else if (e == 2)
									{
										cout << "Wrong grade\n";
									}
								}
								if (!detect_error)
								{
									system("cls");
									cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
								}
							}
							else
							{
								system("cls");
								cout << "Wrong index\n";
							}
						}
						else
						{
							system("cls");
							cout << "Wrong index\n";
						}
					}
					else
					{
						system("cls");
					}
				}
			}
			else
			{
				system("cls");
			}
		}
		else if (choice == 5)
		{
			system("cls");
			for (int i = 0; i < num_sub; i++)
			{
				cout << i + 1 << ". " << subjects[i].list_data() << endl << endl;
			}
			cout << "What do you want to do?\n1.Add new subject\n2.Modify specific subject\n3.Leave\n";
			cin >> choice;
			if (choice == 1)
			{
				Subject New;
				string title;
				cout << "Title of new subject: ";
				cin.ignore();
				getline(cin, title);
				New.Set_title(title);
				int credits;
				cout << "Number of credits of new subject: ";
				cin >> credits;
				New.Set_num_credits(credits);
				cout << "Registration limit of new subject: ";
				cin >> credits;
				New.Set_reg_lim(credits);

				Subject* incremented = new Subject[num_sub + 1];
				for (int i = 0; i < num_sub; i++)
				{
					incremented[i] = subjects[i];
					for (int j = 0; j < num_st; j++)
					{
						students[j].Change_ptr_subject(&incremented[i]);
					}
					for (int k = 0; k < num_tch; k++)
					{
						teachers[k].Change_ptr_subject(&incremented[i]);
					}
				}
				incremented[num_sub] = New;
				delete[] subjects;
				num_sub++;
				subjects = incremented;
				system("cls");
				cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
			}
			else if (choice == 2)
			{
				cout << "Write the index of the subject you want modify: ";
				int index;
				cin >> index;
				index--;
				bool correct_index = false;
				if (index >= 0 && index < num_sub)
				{
					correct_index = true;
				}
				if (!correct_index)
				{
					system("cls");
					cout << "Worng index\n";
				}
				else
				{
					cout << "What do you want to do with this subject?\n1.Delete\n2.Change title\n3.Change number of credits\n4.Change registration limit\n5.See the students who took this subject\n6.Leave\n";
					cin >> choice;
					if (choice == 1)
					{
						if (subjects[index].Get_related() == 0)
						{
							Subject* decremented = new Subject[num_sub - 1];
							for (int i = 0, j = 0; i < num_sub; i++)
							{
								if (i != index)
								{
									decremented[j] = subjects[i];
									for (int k = 0; k < num_st; k++)
									{
										students[k].Change_ptr_subject(&decremented[j]);
									}
									for (int l = 0; l < num_tch; l++)
									{
										teachers[l].Change_ptr_subject(&decremented[j]);
									}
									j++;
								}
							}
							delete[] subjects;
							num_sub--;
							subjects = decremented;
							system("cls");
							cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
						}
						else
						{
							system("cls");
							cout << "Someone is still taking this subject\n";
						}
					}
					else if (choice == 2)
					{
						string title;
						cout << "Write new title: ";
						cin.ignore();
						getline(cin, title);
						subjects[index].Set_title(title);
						system("cls");
						cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
					}
					else if (choice == 3)
					{
						int credits;
						cout << "Write new number of credits: ";
						cin >> credits;
						subjects[index].Set_num_credits(credits);
						system("cls");
						cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
					}
					else if (choice == 4)
					{
						int limit;
						cout << "Write new registration limit: ";
						cin >> limit;
						subjects[index].Set_reg_lim(limit);
						system("cls");
						cout << print(subjects, num_sub, students, num_st, teachers, num_tch);
					}
					else if (choice == 5)
					{
						system("cls");
						cout << subjects[index].list_students() << endl << endl;
					}
					else
					{
						system("cls");
					}
				}
			}
			else
			{
				system("cls");
			}
		}
		else
		{
			break;
		}
	}
	delete[] students;
	delete[] teachers;
	delete[] subjects;
	return 0;
}