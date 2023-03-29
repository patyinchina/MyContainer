// MyContainer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include "vector.h"

using std::cout;
using std::endl;

struct test1 {
    test1(const int& x) {
        a = x;
    }
private:
    int a;
};

struct test2 {
    test2() {
        a = 0; b = 0;
    }
    test2(const int& x,const int& y) {
        a = x; b = y;
    }
private:
    int a, b;
};

int main()
{
    int n = 10;
    int array[] = { 5,4,3,2,1 };
    //------------------------------------vector定义测试------------------------------------
    mycontainer::vector<int> a1;
    mycontainer::vector<int> a2(n);
    mycontainer::vector<int> a3(n, 2);
    mycontainer::vector<int> a4(array, array + 5);
    mycontainer::vector<int> a5(a2);
    mycontainer::vector<int> a6(std::move(a3));
    mycontainer::vector<int> a7,a8;
    mycontainer::vector<int> alist{ 1,2,3,4,5 },alist2;
    a7 = a4;
    a8 = std::move(a6);
    alist2 = { 9,8,7,6,5,4 };

    //------------------------------------vector访问测试------------------------------------
    int t = a4[2];
    int t1 = a8.at(3);
    int t2 = a8.front();
    int t3 = a8.back();
    int* p = a4.data();
    int* p1 = a4.begin();
    const int* p2 = a2.cbegin();
    a7.reserve(1000);
    a7.shrink_to_fit();
    
    //------------------------------------vector修改测试------------------------------------
    //-----erase 2种
    int* p3=a7.erase(a7.begin());
    int* p4=a4.erase(a4.begin()+1,a4.end()-1);
    //-----clear
    a4.clear();
    //-----insert 3种
    mycontainer::vector<int> ainsert(5,0);
    int* p5=a7.insert(a7.begin()+2, 0);
    a7.insert(a7.begin() + 1, 4, 9);
    a7.insert(a7.begin() + 1, ainsert.begin(), ainsert.end());
    //-----resize 2种
    a4.resize(25);
    a4.resize(10, 8);
    //-----reverse
    mycontainer::vector<int> areverse(array, array + 5);
    areverse.reverse();
    //-----swap
    mycontainer::vector<int> aswap;
    aswap.swap(areverse);
    //-----push_back, pop_back
    int ele = 99;
    a4.shrink_to_fit();
    a4.push_back(ele);
    a4.push_back(100);
    a4.pop_back();
    //-----emplace_back
    a4.emplace_back(98);
    //-----emplace
    int* p6 = a4.emplace(a4.begin() + 2, 97);
    //-----assign 3种
    a4.assign(5, 1);
    a4.assign({ 3,4,5,6,7,8,9 });
    a4.assign(array, array + 3);

    //-----push_back, emplace_back二者区别
    mycontainer::vector<test1> atest1;
    atest1.emplace_back(1);
    atest1.push_back(1);
    mycontainer::vector<test2> atest2;
    atest2.emplace_back(1,2);  // correct!
    // atest2.push_back(1, 2); // wrong!
    atest2.emplace(atest2.begin(), 3, 4);

    //------------------------------------输出监测------------------------------------
    // 
    // cout << a4.capacity() << ' ' << a4.size() << endl;
    // for (auto i : a4)  cout << i << endl;

    return 0;
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
