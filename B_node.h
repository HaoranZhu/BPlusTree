//
//  B_node.h
//  B_Tree
//
//  Created by 朱昊冉 on 15/6/10.
//  Copyright (c) 2015年 SEI,ECNU. All rights reserved.
//

#ifndef __B_Tree__B_node__
#define __B_Tree__B_node__
//C1:   第一次遇到具有两个参数的模板哦。注意观察使用方法
#include <stdio.h>
template<class Record,int order>
struct B_node{
    int count;
    B_node<Record,order> *branch[order];
    Record data[order-1];
//constructors:
    B_node();
};
#endif /* defined(__B_Tree__B_node__) */
