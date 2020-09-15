#include <iostream>
#include <vector>

using namespace std;
class Solution
{
public:
    // 暴力解法
    vector<int> twoSum(vector<int>& nums, int target){
        int i,j;
        for(i=0; i<nums.size()-1; i++){
            for(j=i+1; j<nums.size(); j++){
                if(target == nums[i]+nums[j]){
                    return {i, j};
                }
            }
        }
        return {i, j};
    };
};

int main()
{
    vector<int> myNums = {1, 2, 3, 4, 4};
    int target = 8;

    Solution solution;
    vector<int> res = solution.twoSum(myNums, target);

    cout << "The result is: " << endl;
    cout << res[0] << ' ' << res[1] << endl;
    return 0;
}
