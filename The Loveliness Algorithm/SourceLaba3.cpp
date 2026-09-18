#include "MyIncludes.h"
#include "HeaderLaba3.h"

vector<Learner*> learners;

extern double chekDouble(const string& prompt) {
    if (!prompt.empty()) cout << prompt;

    double n;
    while (!(cin >> n) || n <= 0) {
        cout << "Значение должно быть положительным числом, попробуйте ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}
extern int chekInt(const string& prompt) {
    if (!prompt.empty()) cout << prompt;

    int n;
    while (!(cin >> n)) {
        cout << "Значение должно быть целым числом, попробуйте ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}

extern void addLearners() {
    cout << "\n=== ДОБАВЛЕНИЕ УЧАЩИХСЯ ===" << endl;

    int pupilCount, studentCount, studentEmployeeCount;

    do {
        pupilCount = chekInt("Сколько школьников добавить: ");
        studentCount = chekInt("Сколько студентов добавить: ");
        studentEmployeeCount = chekInt("Сколько студентов-работников добавить: ");
        if (pupilCount + studentCount + studentEmployeeCount < 1) cout << "Введите хотя бы одного учащегося" << endl;
    } while (pupilCount + studentCount + studentEmployeeCount < 1);

    for (int i = 0; i < pupilCount; i++) {
        cout << "\n--- Школьник " << i + 1 << " ---" << endl;
        Pupil* pupil = new Pupil();
        pupil->input();
        learners.push_back(pupil);
    }
    for (int i = 0; i < studentCount; i++) {
        cout << "\n--- Студент " << i + 1 << " ---" << endl;
        Student* student = new Student();
        student->input();
        learners.push_back(student);
    }
    for (int i = 0; i < studentEmployeeCount; i++) {
        cout << "\n--- Студент-работник " << i + 1 << " ---" << endl;
        StudentEmployee* studentEmp = new StudentEmployee();
        studentEmp->input();
        learners.push_back(studentEmp);
    }

    cout << "\nУспешно добавлено: " << learners.size() << " учащихся" << endl;
}
extern void displayAllLearners() {
    if (learners.empty()) {
        cout << "\nНет данных об учащихся!" << endl;
        return;
    }

    vector<Learner*> sortedLearners = learners;
    sort(sortedLearners.begin(), sortedLearners.end(), [](Learner* a, Learner* b) {
        auto getPriority = [](Learner* l) {
            if (dynamic_cast<Pupil*>(l)) return 1;
            if (dynamic_cast<Student*>(l) && !dynamic_cast<StudentEmployee*>(l)) return 2;
            if (dynamic_cast<StudentEmployee*>(l)) return 3;
            return 4;
            };
        return getPriority(a) < getPriority(b);
        });

    cout << "\n=== ВСЯ ИНФОРМАЦИЯ ОБ УЧАЩИХСЯХ ===" << endl;
    Learner::printTableHeader();
    for (int i = 0; i < (int)sortedLearners.size(); i++) { sortedLearners[i]->printInfo(i); }
    Learner::printTableFooter();
    cout << "Всего учащихся: " << learners.size() << endl;
}
extern void displayTopLearners() {
    if (learners.empty()) {
        cout << "\nНет данных об учащихся!" << endl;
        return;
    }

    Pupil* topPupil = nullptr;
    Student* topStudent = nullptr;

    for (Learner* learner : learners) {
        if (auto pupil = dynamic_cast<Pupil*>(learner)) {
            if (!topPupil || pupil->getAverageMark() > topPupil->getAverageMark())
                topPupil = pupil;
        } else if (auto student = dynamic_cast<Student*>(learner)) {
            if (!topStudent || student->getAverageMark() > topStudent->getAverageMark())
                topStudent = student;
        }
    }

    bool foundAny = false;

    if (topPupil) {
        cout << "\n=== САМЫЙ УСПЕШНЫЙ ШКОЛЬНИК ===" << endl;
        Learner::printTableHeader();
        topPupil->printInfo(0);
        Learner::printTableFooter();
        foundAny = true;
    }
    if (topStudent) {
        if (foundAny) cout << endl;
        cout << "=== САМЫЙ УСПЕШНЫЙ СТУДЕНТ ===" << endl;
        Learner::printTableHeader();
        topStudent->printInfo(0);
        Learner::printTableFooter();
        foundAny = true;
    }
    if (!foundAny) {
        cout << "\nНет данных для отображения успешных учащихся!" << endl;
    }
}

extern void saveAllToFile(const string& filename) {
    ofstream allFile(filename);
    if (!allFile.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    int allCount = (int)learners.size();
    allFile << allCount << endl;

    for (Learner* learner : learners) {
        if (auto pupil = dynamic_cast<Pupil*>(learner)) {
            allFile << "PUPIL" << endl;
            allFile << pupil->getName() << endl;
            allFile << pupil->getLastname() << endl;
            allFile << pupil->getAverageMark() << endl;
            allFile << pupil->getStudyPlace() << endl;
            allFile << pupil->getGrade() << endl;
        }
        else if (auto student = dynamic_cast<Student*>(learner)) {
            if (auto studentEmp = dynamic_cast<StudentEmployee*>(learner)) {
                allFile << "STUDENT_EMPLOYEE" << endl;
                allFile << studentEmp->getName() << endl;
                allFile << studentEmp->getLastname() << endl;
                allFile << studentEmp->getAverageMark() << endl;
                allFile << studentEmp->getStudyPlace() << endl;
                allFile << studentEmp->getAcademicYear() << endl;
                allFile << studentEmp->getWorkplace() << endl;
                allFile << studentEmp->getIncome() << endl;
            }
            else {
                allFile << "STUDENT" << endl;
                allFile << student->getName() << endl;
                allFile << student->getLastname() << endl;
                allFile << student->getAverageMark() << endl;
                allFile << student->getStudyPlace() << endl;
                allFile << student->getAcademicYear() << endl;
            }
        }
    }

    allFile.close();
    cout << "Все данные об учащихся сохранены в файл: " << filename << " (" << allCount << " записей)" << endl;
}
extern void loadAllFromFile(const string& filename) {
    ifstream allFile(filename);
    if (!allFile.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return;
    }

    for (Learner* learner : learners) delete learner;
    learners.clear();

    int allCount;
    allFile >> allCount;
    allFile.ignore();

    for (int i = 0; i < allCount; i++) {
        string type;
        getline(allFile, type);

        if      (type == "PUPIL") {
            string name, lastname, studyPlace;
            double averageMark;
            int grade;

            getline(allFile, name);
            getline(allFile, lastname);
            allFile >> averageMark;
            allFile.ignore();
            getline(allFile, studyPlace);
            allFile >> grade;
            allFile.ignore();

            Pupil* pupil = new Pupil(name, lastname, averageMark, studyPlace, grade);
            learners.push_back(pupil);
        }
        else if (type == "STUDENT") {
            string name, lastname, studyPlace;
            double averageMark;
            int academicYear;

            getline(allFile, name);
            getline(allFile, lastname);
            allFile >> averageMark;
            allFile.ignore();
            getline(allFile, studyPlace);
            allFile >> academicYear;
            allFile.ignore();

            Student* student = new Student(name, lastname, averageMark, studyPlace, academicYear);
            learners.push_back(student);
        }
        else if (type == "STUDENT_EMPLOYEE") {
            string name, lastname, studyPlace, workplace;
            double averageMark, income;
            int academicYear;

            getline(allFile, name);
            getline(allFile, lastname);
            allFile >> averageMark;
            allFile.ignore();
            getline(allFile, studyPlace);
            allFile >> academicYear;
            allFile.ignore();
            getline(allFile, workplace);
            allFile >> income;
            allFile.ignore();

            StudentEmployee* studentEmp = new StudentEmployee(name, lastname, averageMark, studyPlace, academicYear, workplace, income);
            learners.push_back(studentEmp);
        }
    }
    allFile.close();
    cout << "Данные загружены из файла " << filename << ". Загружено учащихся: " << allCount << endl;
}

extern void clearLearners() {
    if (learners.empty()) {
        cout << "\nНет данных для очистки!" << endl;
        return;
    }
    
    bool confirm = danetka("Вы уверены, что хотите удалить все данные об учащихся? (yes/no): ");
    if (!confirm) {
        cout << "Очистка отменена" << endl;
        return;
    }
    for (Learner* learner : learners) delete learner;
    learners.clear();
    cout << "Все данные об учащихся удалены!" << endl;
}