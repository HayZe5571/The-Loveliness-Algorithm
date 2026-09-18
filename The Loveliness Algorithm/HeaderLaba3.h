#pragma once

class Learner;
class Pupil;
class Student;
class StudentEmployee;

extern vector<Learner*> learners;
extern void Laba3();

extern double chekDouble(const string& prompt = "");
extern int chekInt(const string& prompt = "");

extern void addLearners();
extern void displayAllLearners();
extern void displayTopLearners();
extern void saveAllToFile(const string& filename);
extern void saveBestToFile(const string& filename);
extern void loadAllFromFile(const string& filename);
extern void loadBestFromFile(const string& filename);
extern void clearLearners();

class Learner {
protected:
    string name;
    string lastname;
    double averageMark = 0;
    string studyPlace;

public:
    Learner() = default;
    Learner(string name, string lastname, double averageMark, string studyPlace) {
        setName(name);
        setLastname(lastname);
        setAverageMark(averageMark);
        setStudyPlace(studyPlace);
    }
    Learner(const Learner& other) = default;
    virtual ~Learner() = default;

    void setName(const string& name)             { this->name = name; }
    void setLastname(const string& lastname)     { this->lastname = lastname; }
    void setAverageMark(double averageMark)      { this->averageMark = averageMark; }
    void setStudyPlace(const string& studyPlace) { this->studyPlace = studyPlace; }

    string getName() const        { return name; }
    string getLastname() const    { return lastname; }
    double getAverageMark() const { return averageMark; }
    string getStudyPlace() const  { return studyPlace; }

    virtual void input() {
        cout << "Введите имя: ";
        getline(cin, name);
        cout << "Введите фамилию: ";
        getline(cin, lastname);
        averageMark = chekDouble("Введите средний балл: ");
        cout << "Введите место учебы: ";
        getline(cin, studyPlace);
    }
    virtual void printInfo(int number) const = 0;

    static void printTableHeader() {
        cout << "+-----+------------------+----------------+----------------+--------------+-------------+-------+---------------+--------------+-------------+" << endl;
        cout << "|  №  |       Тип        |      Имя       |    Фамилия     | Средний балл | Место учебы | Класс | Курс обучения | Место работы |    Доход    |" << endl;
        cout << "+-----+------------------+----------------+----------------+--------------+-------------+-------+---------------+--------------+-------------+" << endl;
    }
    static void printTableFooter() {
        cout << "+-----+------------------+----------------+----------------+--------------+-------------+-------+---------------+--------------+-------------+" << endl;
    }
};

class Pupil : public Learner {
    int grade = 0;

public:
    Pupil() = default;
    Pupil(string name, string lastname, double averageMark, string studyPlace, int grade)
        : Learner(name, lastname, averageMark, studyPlace) {
        setGrade(grade);
    }
    Pupil(const Pupil& other) = default;
    ~Pupil() override = default;

    void setGrade(int grade) { this->grade = grade; }

    int getGrade() const { return grade; }

    void input() override {
        Learner::input();
        do {
            grade = chekInt("Введите класс: ");
            if (grade < 1 || grade > 11) cout << "Школьники учатся только с 1 по 11 класс, попробуйсте ввести еще раз" << endl;
        } while (grade < 1 || grade > 11);
    }
    void printInfo(int number) const override {
        cout << "| " << setw(3) << number + 1 << " | "
            << setw(16) << "        Школьник" << " | "
            << setw(14) << name.substr(0, 14) << " | "
            << setw(14) << lastname.substr(0, 14) << " | "
            << setw(12) << fixed << setprecision(2) << averageMark << " | "
            << setw(11) << studyPlace.substr(0, 11) << " | "
            << setw(5) << grade << " | "
            << setw(12) << "" << " | "
            << setw(11) << "" << " | "
            << setw(12) << "" << " |"
            << endl;
    }
};

class Student : public Learner {
protected:
    int academicYear = 0;
    string type = "Студент";

public:
    Student() = default;
    Student(string name, string lastname, double averageMark, string studyPlace, int academicYear)
        : Learner(name, lastname, averageMark, studyPlace) {
        setAcademicYear(academicYear);
    }
    Student(const Student& other) = default;
    virtual ~Student() override = default;

    void setAcademicYear(int academicYear) { this->academicYear = academicYear; }

    int getAcademicYear() const { return academicYear; }

    void input() override {
        Learner::input();
        do {
            academicYear = chekInt("Введите курс обучения: ");
            if (academicYear < 1 || academicYear > 6) cout << "Студенты учатся только с 1 по 6 курсы, попробуйсте ввести еще раз" << endl;
        } while (academicYear < 1 || academicYear > 6);
    }
    virtual void printInfo(int number) const override {
        cout << "| " << setw(3) << number + 1 << " | "
            << setw(16) << type.substr(0, 16) << " | "
            << setw(14) << name.substr(0, 14) << " | "
            << setw(14) << lastname.substr(0, 14) << " | "
            << setw(12) << fixed << setprecision(2) << averageMark << " | "
            << setw(11) << studyPlace.substr(0, 11) << " | "
            << setw(5) << "" << " | "
            << setw(12) << academicYear << " | "
            << setw(11) << "" << " | "
            << setw(12) << "" << " |"
            << endl;
    }
};

class StudentEmployee : public Student {
    string workplace;
    double income = 0;
    string type = "Студент-работник";

public:
    StudentEmployee() = default;
    StudentEmployee(string name, string lastname, double averageMark, string studyPlace, int academicYear, string workplace, double income)
        : Student(name, lastname, averageMark, studyPlace, academicYear) {
        setWorkplace(workplace);
        setIncome(income);
    }
    StudentEmployee(const StudentEmployee& other) = default;
    ~StudentEmployee() override = default;

    void setWorkplace(const string& workplace) { this->workplace = workplace; }
    void setIncome(double income)              { this->income = income; }

    string getWorkplace() const { return workplace; }
    double getIncome() const    { return income; }

    void input() override {
        Student::input();
        cout << "Введите место работы: ";
        getline(cin, workplace);
        income = chekDouble("Введите доход: ");
    }
    void printInfo(int number) const override {
        cout << "| " << setw(3) << number + 1 << " | "
            << setw(16) << type.substr(0, 16) << " | "
            << setw(14) << name.substr(0, 14) << " | "
            << setw(14) << lastname.substr(0, 14) << " | "
            << setw(12) << fixed << setprecision(2) << averageMark << " | "
            << setw(11) << studyPlace.substr(0, 10) << " | "
            << setw(5) << "" << " | "
            << setw(12) << academicYear << " | "
            << setw(11) << workplace.substr(0, 10) << " | "
            << setw(12) << fixed << setprecision(2) << income << " |"
            << endl;
    }
};