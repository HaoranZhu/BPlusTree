//
//  main.cpp
//  B_Tree
//
//  Created by 朱昊冉 on 15/6/10.
//  Copyright (c) 2015年 SEI,ECNU. All rights reserved.
//Pay attention!! B_tree的insert部分的实现还是无法自己根据算法的思想来实现，需要之后花时间来自己打一遍代码。
//Prepartion:对于有两个参数的模板还需要之后花时间去看底层的书籍。

#include <iostream>
#include "B_tree.cpp"


using namespace std;
int main(int argc, const char * argv[]) {
    B_tree<int, 5> tree1;
    tree1.insert(1);
    
    
    return 0;
}
