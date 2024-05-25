//
// Created by 86198 on 2024/5/25.
//

#ifndef FIFTH_EXPERIMENT_BINARY_TREE_HUFFMAN_TREE_H
#define FIFTH_EXPERIMENT_BINARY_TREE_HUFFMAN_TREE_H

#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>

using std::vector;
using std::string;
using std::pair;
using std::priority_queue;
using std::queue;



class huffmanTree;


class huffmanNode
{
    friend class huffmanTree;
private:
    char data;//节点值
    int weight;//权值
    huffmanNode* lc;//左孩子
    huffmanNode* rc;//右孩子
    string path;//路径

public:
    huffmanNode() :
    data(), weight(0), lc(nullptr), rc(nullptr), path() {}

    explicit huffmanNode(const char& d) :
    data(d), weight(0), lc(nullptr), rc(nullptr), path()  {}

    explicit huffmanNode(int w) :
    data(), weight(w), lc(nullptr), rc(nullptr), path() {}

    explicit huffmanNode(const char& d, int w) :
    data(d), weight(w), lc(nullptr), rc(nullptr), path()  {}

    explicit huffmanNode(int w, huffmanNode* node = nullptr, huffmanNode* node1 = nullptr):
    data(), weight(w), lc(node), rc(node1), path() {}

    ~huffmanNode()
    {
        this->weight = 0;
        delete lc;
        delete rc;
    }

};





class huffmanTree
{
    friend class huffmanNode;
private:

    using Node = huffmanNode;

    Node* _root;
    vector<pair<char, string>*> map;

    struct Compare
    {
        bool operator()(huffmanNode* node1, huffmanNode* node2)
        {
            return node1->weight > node2->weight;
        }
    };

public:

    huffmanTree(vector<int>& weight, vector<char>& value)
    {
        createHuffmanTreeNode(weight, value);
        createHuffmanTreePath();
    }

    Node* root() noexcept {return this->_root;}

    void createHuffmanTreeNode(vector<int>& weight, vector<char>& value)
    {
        priority_queue<Node*, vector<Node*>, Compare> queue;//优先级队列构造树

        for(size_t i = 0;i < weight.size();i++)
        {
            Node* tmp = new Node{value[i], weight[i]};
            queue.push(tmp);
        }
        while(queue.size() >= 2)
        {
            Node* min1 = queue.top();
            queue.pop();
            Node* min2 = queue.top();
            queue.pop();
            Node* node = new Node{min1->weight + min2->weight, min1, min2};
            queue.push(node);
        }
        this->_root = queue.top();
    }


    //初始化路径
    void createHuffmanTreePath()
    {
        if(this->_root == nullptr) return;
        queue<Node*> queue;
        queue.push(this->_root);
        while(!queue.empty())
        {
            Node* tmp = queue.front();
            queue.pop();
            if(tmp->lc)
            {
                queue.push(tmp->lc);
                tmp->lc->path.append(tmp->path+ '0');
            }
            if(tmp->rc)
            {
                queue.push(tmp->rc);
                tmp->rc->path.append(tmp->path + '1');
            }
            if(!tmp->lc && !tmp->rc)
            {
                map.push_back(new pair<char, string>(tmp->data, tmp->path));
            }
        }
    }


    string encode(string s)
    {
        string result;
        for(size_t i = 0;i < s.size();i++)
        {
            char ch = s[i];
            for(size_t j = 0;j < map.size();j++)
            {
                pair<char, string>* mapData = map[j];
                if(mapData->first == ch)
                {
                    result.append(mapData->second);
                    break;
                }
            }
        }
        return result;
    }

    string decode(string s)
    {
        string result;
        while(!s.empty())
        {
            for(size_t i = 0;i < map.size();i++)
            {
                pair<char, string>* mapData = map[i];
                if(s.find(mapData->second) == 0)
                {
                    result.push_back(mapData->first);
                    s = s.substr(mapData->second.size());
                    break;
                }
            }
        }
        return result;
    }


};






#endif //FIFTH_EXPERIMENT_BINARY_TREE_HUFFMAN_TREE_H
