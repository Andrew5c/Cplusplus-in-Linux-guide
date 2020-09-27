/*************************************************************************
	> File Name: functionCall.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月20日 星期日 08时42分10秒
 ************************************************************************/
// 实现function object 并应用

#include<iostream>
#include<functional>
#include<vector>
using namespace std;

class LessThan{
    public:
    LessThan(int val):_val(val) {}
    int get_val(void) const {return _val;}
    void set_val(int new_val) {_val = new_val;}
    // 重载function call运算符，实现类似函数的功能
    bool operator() (int ) const ;

    private:
    int _val;
};

inline bool LessThan::operator() (int value) const {
    return (value < _val);
}

int less_than_count(const vector<int>& vec, int comp) {
    LessThan lt(comp);
    int cnt = 0;
    for(int i=0; i<vec.size(); i++){
        // 函数的方式调用这个function object
        if(lt(vec[i]))
            cnt++;
    }
    return cnt;
}

int main() {
    int a[] = {1, 3, 23, 45, 100};
    vector<int> myvec(a, a+5); 
    int cm = 50;
    cout << "The value less than 50 conunt: " << less_than_count(myvec, cm) << endl;
    
	return 0;
}
