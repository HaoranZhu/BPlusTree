//
//  B_tree.h
//  B_Tree
//
//  Created by 朱昊冉 on 15/6/10.
//  Copyright (c) 2015年 SEI,ECNU. All rights reserved.
//Q1:这个ppt上好像是写错了，因为没有用到实例化，所以说不需要使用.cpp文件，只需要使用.h文件就可以了。
//Q2:对于push_down()、push_in()的名称的理解？为什么要这么起名？

#ifndef __B_Tree__B_tree__
#define __B_Tree__B_tree__

#include <stdio.h>
#include "B_node.h"
enum  Error_code{not_present, duplicate_error, overflow, success};
template<class Record,int order>
class B_tree
{
public:
    Error_code search_tree(const Record &target);//这里和ppt的代码稍微有些改动，同时应该参数是继续使用Record，而不用重新架构一个参数Entry.
    Error_code insert(const Record &new_entry);
    /*Post: If the key of new_entry is already in the B_tree, a code of duplicate_error is returned. Otherwise, a code of success is returned and the Record new_enry is inserted into the B_tree in such a way that the properties of a B_tree are preserved;
     */
private:
    B_node<Record,order> *root;
    //auxiliary functions that the search_tree(const Record & target)；needs
    Error_code recursive_search_tree(B_node<Record,order>*current,const Record &target);
    Error_code search_node(B_node<Record,order> *current,const Record &target,int &position);
    
    
    
    
    //auxiliary functions that the insert(const Record &new_entry); needs
    Error_code push_down(B_node<Record,order> *current,const Record &new_entry,Record &median,B_node<Record,order> *&right_branch);
    /*
     Pre: current is either NULL or points to a node of a B_tree
     Post: If an entry with a Key matching that of new_entry is in the subtree to which current points, a code of duplicate error is returned. Otherwise, new_entry is inserted into the subtree:If this causes the height of the subtree to grow, a code of overflow is returned, and the Record median is extracted to be reinserted higher in the B_tree, together with the subtree right_branch on its right. If the height does not grow, a code of success is returned.
     Uses:Functions push_down (called recursively),search_node,split_node, and push_in
     */
    void push_in(B_node<Record,order> *current,const Record &entry,B_node<Record,order> *right_branch,int position);
    /*Pre:current points to a node of a B_tree.The node *current is not full and entry belongs in *current at index position.
     Post:entry has been inserted along with its right-hand branch right_branch ito *current at index position
     */
    void split_node(B_node<Record,order>*current,const Record&extra_entry,B_node<Record,order>extra_branch,int position,B_node<Record,order> *&right_half,Record &median);
    /*
     Pre:current points to a node of a B_tree. The node *current is full,but if there were room, the record extra_entry with its right-hand pointer extra_branch wound belong in *current at position, 0<=position<order.
     Post:The node *current with extra_entry and pointer extra_branch at position position are divided into nodes *current and *right_half separated by a Record median.
     Uses: Methods of struct B_node.function push_in
     */
};
#endif /* defined(__B_Tree__B_tree__) */
