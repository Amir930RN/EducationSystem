#include "LeafMenu.h"

using namespace std;

LeafMenu::LeafMenu(std::string name, Menu* parent)
    : Menu{move(name), parent} {}

void LeafMenu:: showSubMenus() const {}

void LeafMenu::run() {
    setCurrentMenu(parent);

    if(name == "Show This Semester Courses"){
        controller.showSemesterCourses(controller.getCurrentSemester());
    }

    else if(name == "Take Course"){

        string id,cn;
        cout<<" Enter your student id and name of the course you want to take"<<endl;
        cin>>id>>cn;
        controller.takeCourse(id,cn);

    }

    else if(name == "Drop Course"){
        string id,cn;
        cout<<" Enter your student id and name of the course you want to drop"<<endl;
        cin>>id>>cn;
        controller.dropCourse(id,cn);
    }

    else if(name == "Show Student Courses In Current Semester"){

    }

    else if(name == "Calculate Student Salary"){

    }

    else if(name == "Show Professor Courses In Current Semester"){

    }

    else if(name == "Submit Grade"){

    }

    else if(name == "Calculate Professor Salary"){

    }

    else if(name == "Add Professor"){

    }

    else if(name == "Show Professors"){

    }

    else if(name == "Add Student"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        string first;
        cout << "Enter First Name: ";
        cin >> first;
        string last;
        cout << "Enter Last Name: ";
        cin >> last;
        controller.addStudent(ID, first, last);
    }

    else if(name == "Show Students"){

    }

    else if(name == "Add Course"){

    }

    else if(name == "Show All Courses"){

    }

    else{
        throw invalid_argument("This Menu hase not been defined!!");
    }
}
