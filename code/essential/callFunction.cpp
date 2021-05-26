/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-11-21.15.06
* Description :��Essential C++����2.2�ڵĴ����д
* ���ú����Ĳ�ͬ���÷�ʽ
*/
#include<iostream>
#include<vector>
using namespace std;

// ��ʾ�����Դ�ַ�ķ�ʽ����
// Ŀ����Ϊ�˱����ʵ�εĸ��Ʋ�������С�ڴ濪��
// const��ʹ�ã�Ϊ�˿ɶ��ԣ����ұ����������ᱻ�޸�
void display(const vector<int> &vec)
{
    for(int i=0; i<vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl;
}

// �����Դ�ַ�ķ�ʽ���У���Ϊ�˶�ʵ�ν���ʵ�ʵ��޸�
void mySwap(int &v1, int &v2)
{
    int temp = v1;
    v1 = v2;
    v2 = temp;
}
void myBubble(vector<int> &vec)
{
    int len = vec.size();
    for(int i=0; i<len; i++){
        for(int j=i+1; j<len; j++){
            if(vec[i] > vec[j])
                mySwap(vec[i], vec[j]);
        }
    }
}

// ================================================

// ����ʹ�� ����ģ�� �ķ�����дһ������ĺ���
// ʵ�ֿ��ԶԶ����������͵�����
template <typename T>
void displayTemplate(const vector<T> &vec)
{
    for(int i=0; i<vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl;
}
template <typename T>
void mySwapTemplate(T &v1, T &v2)
{
    T temp = v1;
    v1 = v2;
    v2 = temp;
}
template <typename T>
void myBubbleTemplate(vector<T> &vec)
{
    int len = vec.size();
    for(int i=0; i<len; i++){
        for(int j=i+1; j<len; j++){
            if(vec[i] > vec[j])
                mySwapTemplate(vec[i], vec[j]);
        }
    }
}

int main(){
    int arr1[7] = {4, 3, 12, 45, 0, 89, 2};
    float arr2[7] = {4.5, 3.8, 12.1, 45.1, 0, 89.9, 2.3};

    vector<int> myVec1(arr1, arr1+7);
    vector<float> myVec2(arr2, arr2+7);

    cout << "vector before sorted: ";
    displayTemplate(myVec1);
    myBubbleTemplate(myVec1);
    cout << "vector after sorted: ";
    displayTemplate(myVec1);

    cout << endl << "-------------------" << endl;

    cout << "vector before sorted: ";
    displayTemplate(myVec2);
    myBubbleTemplate(myVec2);
    cout << "vector after sorted: ";
    displayTemplate(myVec2);

    return 0;
}
