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

/*
* 双指针法求解三数之和
* 当我们需要枚举数组中的两个元素时，如果我们发现随着第一个元素的递增，第二个元素是递减的，
* 那么就可以使用双指针的方法，将枚举的时间复杂度从 O(N^2) 降低至 O(N)。
* 在枚举的每一个过程中，左指针向右移动一个位置，右指针向左移动若干个位置。
* 当然可能需要保证左指针一直位于右指针的左侧
*/
vector<vector<int> > threeSum2(vector<int> &nums){
    int len = nums.size();
    vector<vector<int> > res;
    sort(nums.begin(), nums.end());
    // 每趟循环 固定第一个数
    for(int i=0; i<len; i++){
        // 这里有一个小技巧，就是如果想执行if(nums[i]==nums[i-1])类似的语句
        // 但是又不想执行i=0的情况，那么就可以学习下面这种写法，很棒！
        if(i>0 && nums[i]==nums[i-1])
            continue;
        int target = -nums[i];
        int pt2 = len - 1;  // 右指针
        // 左指针
        for(int pt1=i+1; pt1<len; pt1++){
            if(pt1>i+1 && nums[pt1]==nums[pt1-1])
                continue;
            // 在保证左指针小于右指针的情况下
            // 持续根据和的结果移动指针
            while(pt1<pt2 && nums[pt1]+nums[pt2]>target){
                    pt2--;
            }
            if(nums[pt1]+nums[pt2] == target && pt1!=pt2)
                res.push_back({nums[i], nums[pt1], nums[pt2]});
        }
    }
    return res;
}

int main(){
    int a[] = {-1, 0, 1, 2, -1, -4};
    vector<int> num(a, a+6);
    vector<vector<int> > res = threeSum2(num);

    // 输出二维数组的内容
    for(unsigned int i=0; i<res.size(); i++){
        cout << res[i][0] << ' ' << res[i][1] << ' ' << res[i][2] << endl;
    }
    return 0;
}

