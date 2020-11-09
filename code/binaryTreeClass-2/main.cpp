/*************************************************************************
	> File Name: main.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月28日 星期一 09时32分19秒
 ************************************************************************/

#include<iostream>
#include<string>
#include"binaryTree.hpp"

using namespace std;


int main() {

	binaryTree<string> bt;

    bt.insert("Piglet");
    bt.insert("Eeyore");
    bt.insert("Roo");
    bt.insert("Tigger");
    bt.insert("Chris");
    bt.insert("Pooh");
    bt.insert("Kanga");

    cout << "Preorder traversal:\n";
    bt.preorder();

    bt.remove("Piglet");
    cout << "\n\npreorder traversal after Piglet removal:\n";
    bt.preorder();

    bt.remove("Eeyore");
    cout << "\n\nPreorder traversal after Eeyore removal:\n";
    bt.preorder();
    cout << endl;

	return 0;
}
