//
//  BinarySearchTree.c
//  KYSBinaryTreeTest
//
//  Created by yongshuai.kang on 2020/6/30.
//  Copyright © 2020 kkk.cn. All rights reserved.
//

#include "BinarySearchTree.h"
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
}Node, *Tree; // 别名 struct Node

Node* newNode(int value) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->value = value;
    p->left = NULL;
    return p;
}

void deallocNode(Node **p){
    if (NULL == *p) {
        return;
    }
    free(*p);
    *p = NULL;
}

// 前序遍历
void preTraversalBSTree(Tree T){
    if (NULL == T) {
        return;
    }
    printf(" %d ",T->value);
    if (NULL != T->left) preTraversalBSTree(T->left);
    if (NULL != T->right) preTraversalBSTree(T->right);
}

// 中序遍历
void inTraversalBSTree(Tree T){
    if (NULL == T) {
        return;
    }
    if (NULL != T->left) inTraversalBSTree(T->left);
    printf("%d ",T->value);
    if (NULL != T->right) inTraversalBSTree(T->right);
}

// 后续遍历
void postTraversalBSTree(Tree T){
    if (NULL == T) {
        return;
    }
    if (NULL != T->left) postTraversalBSTree(T->left);
    if (NULL != T->right) postTraversalBSTree(T->right);
    printf("%d ",T->value);
}

// 查找元素
Node *searchBSTTree(Tree T, int val) {
    Node *current = T;
    while (NULL != current) {
        if (val == current->value) {
            return current;
        }
        if (val < current->value) {
            current = current->left;
        } else if (val > current->value) {
            current = current->right;
        }
    }
    return NULL;
}

// 插入元素
void insertBSTTree(Tree T, int val) {
    Node *current = T;
    Node *parent = NULL;
    while (NULL != current) {
        parent = current;
        if (val < current->value) {
            current = current->left;
        } else if (val > current->value) {
            current = current->right;
        } else {
            printf("duplicate value %d/n",val);
            return;
        }
    }
    Node* x = newNode(val);
    if (NULL == parent) {// 传入树 T 为 NULL
        T = x;
    } else if (val < parent->value) {
        parent->left = x;
    } else {
        parent->right = x;
    }
}

// 删除元素
/*
三种情况
1. 左右子树都为空（叶子节点）
2. 左右子树其中一个为空
3. 左右子树都不为空，降级为 2 或 1
*/
void deleteBSTree(Tree *T, int val){
    if (NULL == *T) {
        return;
    }
    
    // 查找待删除节点
    Node *deleteNode = *T;
    Node *parent = NULL;        // 记录待删除节点的父节点
    while (NULL != deleteNode) {
        if (val == deleteNode->value) {
            break;
        }
        parent = deleteNode;
        if (val < deleteNode->value) {
            deleteNode = deleteNode->left;
        } else if (val > deleteNode->value) {
            deleteNode = deleteNode->right;
        }
    }
    
    // 未找到删除节点
    if (NULL == deleteNode) {
        return;
    }
    
    // 1.无左右子树  2.无左子树或右子树
    if (NULL == deleteNode->left || NULL == deleteNode->right) {
        // 待删除节点为根节点
        if (NULL == parent) {
            // 如果都为空，其实 *T = NULL
            *T = (NULL == deleteNode->left) ? deleteNode->right : deleteNode->left;
            deallocNode(&deleteNode);
            return;
        }
        // 父节点新的子节点, 如果左右子节点都为 NULL，child 为 NULL
        Node *child = (NULL == deleteNode->left) ? deleteNode->right :deleteNode->left ;
        (parent->left == deleteNode) ? (parent->left = child) : (parent->right = child);
        deallocNode(&deleteNode);
    }
    // 3.左右子树都有
    else {
        // 寻找右子树最小值，找到的待删除节点要么是 1. 叶子节点，2. 要么只有一个右子树，无左子树
        Node *pMinParent = deleteNode;
        Node *pMin = deleteNode->right;
        while (pMin->left) {
            pMinParent = pMin;
            pMin = pMin->left;
        }
        deleteNode->value = pMin->value;
        // 删除该节点，1. 叶子节点，2. 要么只有一个右子树，无左子树
        if (NULL == pMin->left || NULL == pMin->right) {
            Node *child = (NULL == pMin->left) ? pMin->right :pMin->left ;
            (pMinParent->left == pMin) ? (pMinParent->left = child) : (pMinParent->right = child);
            deallocNode(&pMin);
        }
    }
}

