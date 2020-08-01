#include "View/View.h"

using namespace std;

int main() {

    Controller myController{"99-1"};
    View myView{myController};
    myView.exec();
    return 0;
}
