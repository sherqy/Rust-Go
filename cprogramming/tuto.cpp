#include <iostream>
using namespace std;

class YoungHwan {
    public:
        int number;
        string dept;

        void printdept() {
            cout << dept << endl;
        }
};


int main() {
    YoungHwan young;
    young.dept = "IS";
    young.printdept();
    return 0;
}