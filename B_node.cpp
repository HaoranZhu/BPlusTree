//
//  B_node.cpp
//  B_Tree
//
//  Created by 朱昊冉 on 15/6/10.
//  Copyright (c) 2015年 SEI,ECNU. All rights reserved.
//
//Q1:   构造函数中对于使用模板的成员的定义为什么不需要进行构造呢？

#include "B_node.h"

template<class Record,int order>
B_node<Record,order>::B_node(){
    count=0;
}