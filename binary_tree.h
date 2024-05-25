//
// Created by 86198 on 2024/5/24.
//

#ifndef FIFTH_EXPERIMENT_BINARY_TREE_BINARY_TREE_H
#define FIFTH_EXPERIMENT_BINARY_TREE_BINARY_TREE_H

#include<iostream>
#include<stack>
#include<queue>
#include"release.h"


template<class eleType>
class Tree;


template<class eleType>
class TreeNode
{
    friend class Tree<eleType>;
private:
    eleType data;
    TreeNode* parent;
    TreeNode* lc;//����
    TreeNode* rc;//�Һ���
    size_t height;//�߶ȣ������ڵ��·�������ڵ���

public:
    TreeNode():data(0), parent(0), lc(nullptr), rc(nullptr), height(0){}

    explicit TreeNode(eleType elem, TreeNode<eleType>* p = nullptr,
             TreeNode<eleType>* l = nullptr, TreeNode<eleType>* r = nullptr, size_t h = 0):
    data(elem), parent(p), lc(l), rc(r), height(h){}

    //��ֵΪelem�Ľڵ���Ϊ��ǰ�ڵ�����Ӳ���
    TreeNode<eleType>* insertAsLC(const eleType& elem)//assert !this->lc
    {
        return this->lc = new TreeNode(elem, this);
    }


    //��ֵΪelem�Ľڵ���Ϊ��ǰ�ڵ���Һ��Ӳ���
    TreeNode<eleType>* insertAsRC(const eleType& elem)//assert !this->rc
    {
        return this->rc = new TreeNode(elem, this);
    }

    size_t stature(TreeNode<eleType>* node)
    {
        return (node) ? (node)->height : -1;
    }

    size_t updateHeight()
    {
        return this->height = 1 + std::max(stature(this->lc), stature(this->rc));
    }


    void updateHeightAbove()
    {
        TreeNode<eleType>* node = this;
        while(node)
        {
            node->updateHeight();
            node = node->parent;
        }
    }
};


template<class eleType>
class Tree
{
    friend class TreeNode<eleType>;
protected:
    TreeNode<eleType>* _root;//���ڵ�

    size_t _size;


public:
    Tree():_root(nullptr), _size(0){}

    ~Tree() = default;


    //��ӡ��������
    void printAss(TreeNode<eleType>* node, size_t depth) const
    {
        if(node == nullptr)  return;
        printAss(node->rc, depth+1);
        for(int i = 0;i < depth;i++)
        {
            std::cout << "   " ;
        }
        std::cout << node->data << std::endl;
        printAss(node->lc, depth + 1);
    }

    void displayTree() const
    {
        if(empty())
        {
            throw std::underflow_error("empty tree, can not display anything");
        }
        printAss(this->_root,0);
    }

    TreeNode<eleType>* insertAsRoot(const eleType& elem);//������ڵ�

    TreeNode<eleType>* insert(const eleType& elem, TreeNode<eleType>* node);//�����Һ���

    TreeNode<eleType>* insert(TreeNode<eleType>* node, const eleType& elem);//��������


    [[nodiscard("not use return")]]size_t size() const noexcept
    {
        return this->_size;
    }

    [[nodiscard("not use return")]]bool empty() const noexcept
    {
        return this->_size == 0;
    }


    TreeNode<eleType>* root() noexcept
    {
        return this->_root;
    }


    //ɾ���ڵ���������������ɾ���Ľڵ���
    eleType remove(TreeNode<eleType>* node);

public:

    //���ֱ����㷨
    void traversePre(TreeNode<eleType>* node)
    {
        std::stack<TreeNode<eleType>*> s;//����ջ
        while(true)
        {
            visitAlongLeft(node, s);
            if(s.empty()) break;
            node = s.top();
            s.pop();
        }
    }


    void traverseIn(TreeNode<eleType>* node)
    {
        std::stack<TreeNode<eleType>*> s;
        while(true)
        {
            traAlongLeft(node, s);
            if(s.empty()) break;
            node = s.top();
            s.pop();
            std::cout << node->data << " ";
            node = node->rc;
        }
    }


    void traversePost(TreeNode<eleType>* node)
    {
        std::stack<TreeNode<eleType>*> s;
        if(node) s.push(node);
        while(!s.empty())
        {
            if(s.top() != node->parent)
            {
                gotoDHLF(s);
            }
            node = s.top();
            s.pop();
            std::cout << node->data << " ";
        }
    }


private:

    static eleType removeAt(TreeNode<eleType>* node)
    {
        if(!node) return 0;//�ݹ��
        eleType n = 1 + removeAt(node->lc) + removeAt(node->rc);//�ݹ��ͷ���������
        release(node->data);//�ͷ�ժ���ڵ㣬�����ر�ɾ���Ľڵ�����
        release(node);
        return n;
    }

    static void visitAlongLeft(TreeNode<eleType>* node, std::stack<TreeNode<eleType>*>& s)
    {
        while(node)
        {
            std::cout << node->data << " " ;
            if(node->rc) s.push(node->rc);
            node = node->lc;
        }
    }

    static void traAlongLeft(TreeNode<eleType>* node, std::stack<TreeNode<eleType>*>& s)
    {
        while(node)
        {
            s.push(node);
            node = node->lc;
        }
    }


    static void gotoDHLF(std::stack<TreeNode<eleType>*>& s)
    {
        while(TreeNode<eleType>* node = s.top())
        {
            if(node->lc)
            {
                if(node->rc)//�������Ҹ��ı���˳���Լ�ջ��FILO���ԣ����ӽڵ�������ջ
                {
                    s.push(node->rc);
                }
                s.push(node->lc);//�ٽ����ӽڵ���ջ
            }
            else///û�и������Ľڵ�
            {
                s.push(node->rc);
            }
        }
        s.pop();//��ջ���Ŀսڵ㵯��
    }



};


template<class eleType>
TreeNode<eleType>* Tree<eleType>::insertAsRoot(const eleType &elem)
{
    this->_size++;
    return this->_root = new TreeNode<eleType>(elem);
}


template<class eleType>
TreeNode<eleType>* Tree<eleType>::insert(TreeNode<eleType>* node, const eleType& elem)
{
    this->_size++;
    node->insertAsLC(elem);
    node->updateHeightAbove();
    return node->lc;
}


template<class eleType>
TreeNode<eleType>* Tree<eleType>::insert(const eleType& elem, TreeNode<eleType>* node)
{
    this->_size++;
    node->insertAsRC(elem);
    node->updateHeightAbove();
    return node->rc;
}



template<class eleType>
[[nodiscard("not use return")]] eleType Tree<eleType>::remove(TreeNode<eleType>* node)
{
    !node->parent ? this->_root : ((node->parent && node == node->parent->lc) ? node->parent->lc : node->parent->rc) = nullptr;
    node->parent->updateHeightAbove();
    eleType n = removeAt(node);
    this->_size -= n;
    return n;
}






#endif //FIFTH_EXPERIMENT_BINARY_TREE_BINARY_TREE_H
