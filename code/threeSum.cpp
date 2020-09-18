/*************************************************************************
	> File Name: threeSum.cpp
	> Author: Andrew. Q
	> Mail:
	> Created Time: 2020年09月17日 星期四 20时49分07秒
 ************************************************************************/
// 三数之和，数组中有n个整数，找出所有满足之和为0且不重复的三元组


#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

vector<vector<int> > threeSum(vector<int>& nums){
    // 函数内部定义一个vector， 返回时，返回的是该临时对象的一个拷贝
    // 因此，当数据量很大的时候，不适合这种方法
    vector<vector<int> > res;
    int len = nums.size();
    vector<int>::iterator endPt = nums.end();
    vector<int>::iterator startPt = nums.begin();
    vector<int>::iterator pt;
    set<int> save;
    int cnt = 0; // 满足要求的三元组计数器
    for(int i=0; i<len-2; i++){
        for(int j=i+1; j<len-1; j++){
            int temp = nums[i] + nums[j];
            pt = find(startPt+j+1, endPt, -temp);
            // 判断是否检索到第三个数，并且是否和之前的三元组重复
            if(pt != endPt && !(0 != save.count(nums[i]) && 0 != save.count(nums[j]))){
                res[cnt][0] = nums[i]; save.insert(nums[i]);
                res[cnt][1] = nums[j]; save.insert(nums[j]);
                res[cnt][2] = *pt; save.insert(*pt);
                cnt++;
            }
        }
    }
    return res;
}

int main(){
    int a[] = {-1, 0, 1, 2, -1, -4};
    vector<int> num(a, a+6);
    vector<vector<int> > res = threeSum(num);

    // 输出二维数组的内容
    for(int i=0; i<res.size(); i++){
        cout << res[i][0] << ' ' << res[i][1] << ' ' << res[i][2] << endl;
    }
    return 0;
}
