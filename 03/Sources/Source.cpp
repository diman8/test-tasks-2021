#include <iostream>
#include "Source.h"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "Base64EncDec.h"

List::List(ListNode* _head, ListNode* _tail) : head(_head), tail(_tail)
{
}

List::~List()
{
    auto vec = EncodeToVec();
    for (auto vec_elem : vec)
    {
        delete vec_elem.first;
    }
}

void List::Serialize(FILE* file)
{
    auto vec = EncodeToVec();
    for (auto elem : vec)
    {
        const std::string base64str = base64_encode(elem.first->data);
        fprintf(file, "%s %u\n", base64str.data(), elem.second);
    }
}

void List::Deserialize(FILE* file)
{
    std::vector<NodeWRndIndex> vec;
    {
        static char buff[256];

        while (fscanf(file, "%s", buff) != EOF)
        {
            uint rnd_ptr = -1;
            auto retVal = fscanf(file, "%d", &rnd_ptr);
            if (retVal == -1)
            {
                std::cout << "ALARM: wrong file encoding" << "\n";
                return;
            }
            auto tmp = new ListNode{ nullptr,nullptr,nullptr,buff };
            vec.push_back(std::make_pair(tmp, rnd_ptr));
        }
    }

    for (int i = 0; i < vec.size(); i++)
    {
        if (i != 0)
        {
            vec[i].first->prev = vec[i - 1].first;
        }
        if (i != vec.size() - 1)
        {
            vec[i].first->next = vec[i + 1].first;
        }

        if (vec[i].second != -1)
        {
            vec[i].first->rand = vec[vec[i].second].first;
        }
    }
    this->head = vec.front().first;
    this->tail = vec.back().first;
}

void List::ReleaseNodes()
{
    head = nullptr;
    tail = nullptr;
}

// WIP
bool List::IsListOk() const
{
    std::vector<NodeWRndIndex> v1 = EncodeToVec();

    //sanity check for proper prev usage in Nodes
    for (int i = v1.size() - 1; i > 0; i--)
    {
        if (v1[i].first->prev != v1[i-1].first)
        {
            std::cout << "ALARM: can't find linked node" << "\n";
            return false;
        }
    }
    return true;
}

std::vector<NodeWRndIndex> List::EncodeToVec() const
{
    std::unordered_map<ListNode*, uint> nodes;
    std::vector<NodeWRndIndex> v1;
    ListNode* current = nullptr;
    uint index = 0;
    for (current = this->head, index = 0; current; current = current->next, index++)
    {
        nodes[current] = index;
        v1.push_back(std::make_pair(current, -1));
        if (current == this->tail)
        {
            break;
        }
    }

    for (auto cur_pair : v1)
    {
        if (cur_pair.first->rand)
        {
            auto it = nodes.find(cur_pair.first->rand);
            if (it != nodes.end())
            {
                cur_pair.second = it->second;
            }
            else
            {
                std::cout << "ALARM: can't find linked node" << "\n";
            }
        }
    }

    return v1;
}

void List::DecodeFromVec(const std::vector<NodeWRndIndex>& vec)
{
    if (head || tail)
    {
        std::cout << "ALARM: there is already data in this List" << "\n";
        return;
    }

    head = vec.front().first;
    tail = vec.back().first;
}

bool operator==(const List& lhs, const List& rhs)
{
    std::vector<NodeWRndIndex> v1 = lhs.EncodeToVec();
    std::vector<NodeWRndIndex> v2 = rhs.EncodeToVec();

    if (v1.size() != v2.size())
        return false;

    for (int i = 0; i < v1.size(); i++)
    {
        if (!(*v1[i].first == *v2[i].first) || v1[i].second != v2[i].second)
            return false;
    }

    return true;
}

bool operator==(const ListNode& lhs, const ListNode& rhs)
{
    return lhs.data == lhs.data;
}


//void SmartListStorage::AddNodeToEnd(std::unique_ptr<ListNode> node)
//{
//    if (last_elem)
//    {
//        last_elem->next = node.get();
//        node->prev = last_elem;
//    }
//    last_elem = node.get();
//    storage.push_back(std::move(node));
//}
//
//std::vector<std::unique_ptr<ListNode>>& SmartListStorage::GetStorage()
//{
//    return storage;
//}
