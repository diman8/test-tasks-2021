#pragma once
#include <string>
#include <vector>
#include <memory>

typedef unsigned int uint;

// структуру ListNode модифицировать нельзя
struct ListNode {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо NULL
    std::string data;
};

typedef std::pair<ListNode*, int> NodeWRndIndex;

class List final
{
public:
    List(ListNode* head, ListNode* tail);
    ~List();

    void Serialize(FILE* file); // сохранение в файл (файл открыт с помощью fopen(path, &quot;wb&quot;))
    void Deserialize(FILE* file); // загрузка из файла (файл открыт с помощью fopen(path, &quot;rb&quot;))

    void ReleaseNodes();

    bool IsListOk() const; // WIP

    friend bool operator==(const List& lhs, const List& rhs);
private:
    std::vector<NodeWRndIndex> EncodeToVec() const;
    void DecodeFromVec(const std::vector<NodeWRndIndex>& vec);

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int count = 0;
};


bool operator==(const ListNode& lhs, const ListNode& rhs);

//class SmartListStorage
//{
//public:
//    void AddNodeToEnd(std::unique_ptr<ListNode> node);
//    std::vector<std::unique_ptr<ListNode>>& GetStorage();
//
//private:
//    std::vector<std::unique_ptr<ListNode>> storage;
//    ListNode* last_elem = nullptr;
//    int count = 0;
//};