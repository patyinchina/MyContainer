// MyContainer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include "vector.h"

using std::cout;
using std::endl;
using namespace mycontainer;

int main()
{
    int n = 10;
    int array[] = {5,4,3,2,1};
    vector<int> a1;
    vector<int> a2(n);
    vector<int> a3(n, 2);
    vector<int> a4(array, array + 5);
    vector<int> a5(a2);
    vector<int> a7(std::move(a3));
    int* p = a4.data();
    vector<int> a6,a8;
    a6 = a4;
    a8 = std::move(a7);

    cout << a8.at(3);
    


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
