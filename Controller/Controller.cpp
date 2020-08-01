#include "Controller.h"
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
#include <stdexcept>


using namespace std;

Controller::Controller(std::string currentSemester)
   : currentSemester{move(currentSemester)} {}


void Controller:: load(){
    ifstream inputStu("students.txt");
    int studentSize;
    inputStu >> studentSize;
    Student stu;
    for( size_t i{0}; i < studentSize; ++i ){
        inputStu >> stu;
        students.push_back(stu);
    }
    inputStu.close();

    ifstream inputProf("professors.txt");
    int profSize;
    inputProf >> profSize;
    Professor prof;
    for( size_t i{0}; i < profSize; ++i){
        inputProf >> prof;
        professors.push_back(prof);
    }
    inputProf.close();

    ifstream inputCourse("courses.txt");
    int courseSize;
    inputCourse >> courseSize;
    Course crs;
    for( size_t i{0}; i < courseSize; ++i){
        inputCourse >> crs;
        courses.push_back(crs);
        if(crs.semester == currentSemester){
            currentSemesterCourses.push_back(crs);
        }
    }
    inputCourse.close();
}

void Controller::save() const{
    ofstream outputStu("students.txt", ios::out);
    outputStu << students.size() << endl;
    for( auto const& stu : students ){
        outputStu << stu << endl;
    }
    outputStu.close();

    ofstream outputProf("professors.txt");
    outputProf << professors.size() << endl;
    for( const auto& prof : professors ){
        outputProf << prof << endl;
    }
    outputProf.close();

    ofstream outputCourse("courses.txt");
    outputCourse << courses.size() << endl;
    for( auto const& crs : courses ){
        outputCourse << crs << endl;
    }
    outputCourse.close();
}

void Controller:: addStudent(std::string ID, std::string first, std::string last){
    if(!inStudents(ID)){
        Student stu{move(ID), move(first), move(last), 0,
                    vector<string>{}, map<string, double>{}};
        students.push_back(stu);
    }
}

void Controller:: addProfessor(std::string ID, std::string first,
        std::string last, std::string title){
    if(!inProfessors(ID)){
        Professor prof{move(ID), move(first), move(last), 0, move(title)};
        professors.push_back(prof);
    }
}

void Controller:: addCourse(std::string courseName, std::string profLast, std::string semester,
               std::vector<std::string> pre){
    if( !inCourses(courseName) && inProfessorsByLastName(profLast) ){
        Course crs{move(courseName), move(profLast), move(semester), move(pre)};
        courses.push_back(crs);
        if( crs.semester == currentSemester){
            currentSemesterCourses.push_back(crs);
        }
    }

}

bool Controller::inStudents(const std::string& ID) const{
    for( const auto& stu : students ){
        if( stu.studentId == ID){
            return true;
        }
    }
    return false;
}

bool Controller::inProfessors(const std::string& ID) const{
    for( const auto& prof : professors ){
        if( prof.profId == ID){
            return true;
        }
    }
    return false;
}

bool Controller::inCourses(const std::string& courseName) const{
    for( const auto& crs : courses ){
        if( crs.courseName == courseName){
            return true;
        }
    }
    return false;
}

bool Controller:: inProfessorsByLastName(const std::string& last) const{
    for( const auto& prof : professors ){
        if( prof.getLastName() == last){
            return true;
        }
    }
    return false;
}

Student& Controller:: findStudent(string ID){
    for( auto& stu : students ){
        if(stu.studentId == ID){
            return stu;
        }
    }
    throw invalid_argument("The Student was not found!!");
}

Course& Controller:: findCourse(const string& name){
    for( auto& c : courses ){
        if(c.courseName == name){
            return c;
        }
    }
    throw invalid_argument("The Course was not found!!");
}

void Controller:: takeCourse(const std::string& studentID, const std::string& courseName){

    if (!inStudents(studentID)) throw invalid_argument("The Student was not found!!");

    if(inCourses(courseName)){
        findStudent(studentID).currentSemesterCourses.insert({courseName, 0});
        cout<<"Course has added successfully!"<<endl;
    }
    throw invalid_argument("The Course dose not exits!");
}

void Controller:: dropCourse(const std::string& studentID, const std::string& courseName){

    if (!inStudents(studentID)) throw invalid_argument("The Student was not found!!");

    if(inCourses(courseName)){
        findStudent(studentID).currentSemesterCourses.erase(studentID);
        cout<<"Course has dropped successfully!"<<endl;
    }
    throw invalid_argument("The Course dose not exits!");
}

void Controller:: showStudentCoursesInCurrentSemester(const std::string& studentID){

    if (!inStudents(studentID)) throw invalid_argument("The Student was not found!!");
    Student st = findStudent(studentID);
    for ( auto& c : st.currentSemesterCourses ) {
        cout<<findCourse(c.first)<<endl;
    }

}

void Controller::showSemesterCourses(const std::string& semester ) const {

    for( auto& c : courses ){
        if(c.semester == semester ){
            cout<<c<<endl;
        }
    }

}


const std::string &Controller::getCurrentSemester() const {
    return currentSemester;
}


void Controller::readMembersFromFile() {

    string command;
    char * cmd = new char[1000];
    ifstream input("members.txt");

    for(size_t i{1}; i <= 6; ++i){
        try {
            input.getline(cmd, 1000);
            command = (string) cmd;
            istringstream iss{command};
            vector<string> results{istream_iterator<string>{iss}, istream_iterator<string>()};

            if (results[0] == "P") {
                auto* p = new Professor(results[1],results[2],results[3],stod(results[5]),results[4]);
                mathClass.push_back(p);

            } else if (results[0] == "S") {
                auto* s = new Student(results[1],results[2],results[3],stod(results[4]),vector<string>{}, map<string, double>{});
                mathClass.push_back(s);

            } else if (results[0] == "D") {
                auto* s = new DoubleMajorStudent(results[1],results[2],results[3],stod(results[4]),vector<string>{}, map<string, double>{});
                mathClass.push_back(s);
            }else {
                throw invalid_argument("Error!");
            }
        }
        catch( const invalid_argument& e){
            cout << e.what() << endl;
        }

    }

}


double Controller::calculateTotalSalary() const {

    double sum = 0;
    for( auto& p : mathClass ){
        sum+=p->calculateSalary();
    }


}

