//
//  B_tree.cpp
//  B_Tree
//
//  Created by 朱昊冉 on 15/6/10.
//  Copyright (c) 2015年 SEI,ECNU. All rights reserved.
//C1:   position清零还是非常重要的，详情请见search_node这个函数
//C2: 写递归函数一定要有一个终止条件，一定不要忘了！！详情请见recursive_search_tree;
//C3：   我觉得吧，之所以要使用一个search_tree然后再嵌套一个什么recursive_search_tree的目的就在于如果不在里面使用一个递归的函数的话，因为root是private，实在不好调用出来。

//Q1:insert()里面有问题
//Q2：push_in操作中的插入的是entry以及它的right_branch那么，left_branch该是怎么处理的呢？
//Q3: 看不出来split这个函数最后remove median的操作是在哪里执行的。
#include "B_tree.h"

//this function is written by myself.
template<class Record,int order>
Error_code B_tree<Record,order>::search_node(B_node<Record,order> *current,const Record &target,int &position){
    /*pre:current points to a node of a B_tree
     post:If the Key of target is found in *current, then a code of success is returned,
     the parameter position is set to the index of target, and the corresponding Record is
     copied to target. Otherwise, a code of not_present is returned and position is set to 
     the branch index on which to continue the search.
     Uses:*/
    position=0;//position清零还是挺重要的
    int i;
    for(i=0;i<current->count-1;i++){
        if(current->data[i]==target)
            return success;
        if(current->data[i]>target)
            break;
    }
    position=i;
    return not_present;
}

template<class Record,int order>
Error_code B_tree<Record,order>::recursive_search_tree(B_node<Record,order>*current,const Record &target){
    int position=0;
    if(current!=NULL){//千万不要忘记有current!=NULL这一个语句！！
        if(search_node(current,target,position)==success){
            return success;
        }
        search_node(current->branch[position],target,position);
        }
    return not_present;
}


template<class Record,int order>
Error_code B_tree<Record,order>::search_tree(const Record &target){
    return recursive_search_tree(root, target);
}


template<class Record,int order>
Error_code B_tree<Record,order>::push_down(B_node<Record,order> *current,const Record &new_entry,Record &median,B_node<Record,order> *&right_branch){
    Error_code result;
    int position;
    if(current==NULL)//base case
    {
        median=new_entry;
        right_branch=NULL;
        result=overflow;
    }
    else{//search the current node
        if(search_node(current,new_entry,position)==success)
            return duplicate_error;
        else{
            Record extra_entry;
            B_node<Record,order> *extra_branch;
            result=push_down(current->branch[position],new_entry,extra_entry,extra_branch);
            if(result==overflow){//Record extra_entry now must be added to the current;
                if(current->count<order-1){
                    result=success;
                    push_in(current,extra_entry,extra_branch,position);
                }
                else{
                    split_node(current,extra_entry,extra_branch,position,right_branch,median);//Record median and its right_branch will go up to a higher node;
                }
            }
        }
    }
    return result;

}

template<class Record,int order>
void B_tree<Record,order>::push_in(B_node<Record,order> *current,const Record &entry,B_node<Record,order> *right_branch,int position){
    for(int i=current->count;i>position;i--){
        current->data[i]=current->data[i-1];
        current->branch[i+1]=current->branch[i];
    }
    current->data[position]=entry;
    current->count++;
    current->branch[position+1]=right_branch;
}

template<class Record,int order>
void B_tree<Record,order>::split_node(B_node<Record,order>*current,const Record&extra_entry,B_node<Record,order>extra_branch,int position,B_node<Record,order> *&right_half,Record &median){
    right_half=new B_node<Record, order>;
    int mid=order/2;
    if(position<=mid){
        for(int i=mid;i<order-1;i++){
            right_half->data[i-mid]=current->data[i];
            right_half->branch[i-mid+1]=current->branch[i+1];
        }
        current->count=mid;
        right_half->count=order-1-mid;
        push_in(current,extra_entry,extra_branch,position);
    }
    else{
        mid++;
        for(int i=mid;i<order-1;i++){
            right_half->data[i-mid]=current->data[i];
            right_half->branch[i-mid+1]=current->branch[i+1];
        }
        current->count=mid;
        right_half->count=order-1-mid;
        push_in(right_half, extra_entry, extra_branch, position-mid);
    }
    median=current->data[current->count-1];
    right_half->branch[0]=current->branch[current->count];
    current->count--;
}

template<class Record,int order>
Error_code B_tree<Record,order>::insert(const Record &new_entry){
    Record median;
    B_node<Record,order> *right_branch,*new_root;// 接下来可能用得到的参数
    Error_code result=push_down(root,new_entry,median,right_branch);
    /*********
     这里有问题，上面result的返回值是什么？？*********/
    if(result==overflow){ //it means the height has increased.
        new_root=new B_node<Record, order>;
        new_root->count=1;
        new_root->data=median;
        new_root->branch[0]=root;
        new_root->branch[1]=right_branch;
        root=new_root;
        result=success;
    }
    return result;
}


