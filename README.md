# University Database (C++ Console App)

A console-based university records manager written in C++. It keeps track of **students**, **teachers** and **subjects**, handles registrations and grading, and saves everything to a custom plain-text `.nvrst` file.

The project is built around object-oriented design: an abstract `Person` base class, `Student` and `Teacher` classes derived from it, manual dynamic memory management (copy constructors, assignment operators, destructors) and exception-based error handling.

## Features

**Students**
- Add, edit or delete students (name, date of birth, sex, major)
- Register for subjects and drop them
- Credit total and GPA (average of graded subjects) are calculated automatically
- Each student has a password that must be entered before their data can be changed

**Teachers**
- Add, edit or delete teachers (name, date of birth, sex, faculty)
- Take or drop subjects to teach
- See the students enrolled in each of their subjects
- Give grades to students
- Each teacher has a password too

**Subjects**
- Add, edit or delete subjects (title, number of credits, registration limit)
- Registration limits are enforced
- See the list of students who took the subject

**Storage**
- Load and save the whole database to a `.nvrst` file (default: `data.nvrst`, or any path you enter)
- Passwords are XOR-obfuscated before they are written to disk

## Project structure

```
Database.sln               Visual Studio solution
Database/
├── main.cpp               Interactive console menu
├── university.h / .cpp    Subject, Person, Student and Teacher classes
├── file_handling.h / .cpp Reading and writing .nvrst files
├── data.nvrst             Default data file
└── example.nvrst          Sample database
```

## Building and running

### Visual Studio (recommended)
1. Open `Database.sln` in Visual Studio 2022 (toolset v143) with the **Desktop development with C++** workload installed.
2. Build with **Ctrl+Shift+B** and run with **Ctrl+F5**.

### Command line (MSVC)
From a *Developer Command Prompt*:
```bat
cd Database
cl /EHsc /std:c++17 main.cpp university.cpp file_handling.cpp /Fe:Database.exe
Database.exe
```

> The program clears the screen with `system("cls")`, so it is meant to run on Windows.

Run the program from the `Database/` folder so it can find the default `data.nvrst` file.

## Usage

When the program starts, the main menu appears:

```
What do you want to do?
1.Read data from the file
2.Save data
3.Modify students
4.Modify teachers
5.Modify subjects
6.Leave
```

A typical session:
1. Choose **1** and press Enter to load `data.nvrst`, or type a path such as `example.nvrst`.
2. Use options **3–5** to add or change students, teachers and subjects. Changing a person's data asks for their password.
3. Choose **2** to save. Changes are kept in memory only until you save.

### Error codes when loading

| Code | Meaning |
|------|---------|
| 1 | The file could not be opened (wrong path) |
| 2, 3 | The file is not in a valid `.nvrst` format |

## The `.nvrst` file format

A line-based text format with three sections, in this order: subjects (`sub`), students (`st`) and teachers (`tch`). Every section starts with its tag, which is prefixed with the `\x1E` control character, and is followed by the number of records. Here is the start of `example.nvrst`:

```
sub
3
Calculus      ← title
6             ← credits
80            ← registration limit
...
```

Text fields must not start with the `\x1E` character, which the format reserves as a separator.

## License

No license has been chosen yet. Add one (MIT, for example) before publishing if you want others to be able to reuse the code.
