#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
    string words;
    map<string, int> names;

    names["andrew"] = 1;

    cout << "please input a string :";
    cin >> words;

    // 下面使用三种方式查找words是否存在于names的map中

    
    // 查询
    int count2 = 0;
    map<string, int>::iterator iter;
    iter = names.find(words);
    if(iter != names.end())
        cout << "Yes!\n";
    else
        cout << "No!\n";

    // 计数
    if(names.count(words))
        cout << "Yes!\n";
    else
        cout << "No!\n";

    // 直接将words当做索引, 但是此时,不管有没有,words将被放在names中
    int count1 = 0;
    if(!(count1 = names[words]))
        cout << "No!\n";
    else
        cout << "Yes!\n";


    return 0;
}