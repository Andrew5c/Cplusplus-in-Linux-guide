/*************************************************************************
	> File Name: roma2Int.cpp
	> Author: Andrew. Q 
	> Mail: 
	> Created Time: 2020年09月16日 星期三 13时57分28秒
 ************************************************************************/
// 罗马数字转换成整数
#include<iostream>
#include<string>

using namespace std;
int romaToInt(string roma){
    int res = 0;
    int len = roma.size();
    int *pt = new int(len);
    for(int i=0; i<len; i++){
        switch(roma[i]){
            case 'I': pt[i] = 1; break;
            case 'V': pt[i] = 5; break;
            case 'X': pt[i] = 10; break;
            case 'L': pt[i] = 50; break;
            case 'C': pt[i] = 100; break;
            case 'D': pt[i] = 500; break;
            case 'M': pt[i] = 1000; break;
            default: break;
        }
    }

    for(int j=0; j<len-1; j++){
        if(pt[j] >= pt[j+1])
            res += pt[j];
        else
            res -= pt[j]; 
    }
    res += pt[len-1];
    delete [] pt;
    return res;
}
    
int main(){
    string roma = "VXL";
    int sum = romaToInt(roma);

    cout << roma << " is the num: " << sum << endl;

    return 0;
}
