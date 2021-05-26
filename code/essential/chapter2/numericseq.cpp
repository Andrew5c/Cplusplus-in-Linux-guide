#include "numericseq.h"



void display(const vector<int> &vec, ostream &os) {
    for(int i=0; i<vec.size(); i++) {
        os << vec[i] << ' ';
    }
    os << endl;
}


int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    vector<int> myVec(arr, arr+5);

    display(myVec);
    return 0;
}