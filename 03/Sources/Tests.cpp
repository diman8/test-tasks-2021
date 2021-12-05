#include <gtest/gtest.h>
#include <string>
#include "Source.h"
#include <vector>
#include <list>

TEST(ListCompare, Null) {
    std::unique_ptr<List> lst1;
    std::unique_ptr<List> lst2;

    {
        lst1 = std::make_unique<List>(nullptr, nullptr);
    }

    {
        lst2 = std::make_unique<List>(nullptr, nullptr);
    }

    lst1->IsListOk();
    lst2->IsListOk();

    EXPECT_TRUE(*lst1.get() == *lst2.get());
}

TEST(ListCompare, OneFalse) {
    std::unique_ptr<List> lst1;
    std::unique_ptr<List> lst2;

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test1" };
        lst1 = std::make_unique<List>(n1, n1);
    }

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test3" };
        lst2 = std::make_unique<List>(n1, n1);
    }

    lst1->IsListOk();
    lst2->IsListOk();

    EXPECT_FALSE(!(*lst1.get() == *lst2.get()));
}

TEST(ListCompare, One) {
    std::unique_ptr<List> lst1;
    std::unique_ptr<List> lst2;

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test1" };
        lst1 = std::make_unique<List>(n1, n1);
    }

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test1" };
        lst2 = std::make_unique<List>(n1, n1);
    }

    lst1->IsListOk();
    lst2->IsListOk();

    EXPECT_TRUE(*lst1.get() == *lst2.get());
}

TEST(ListCompare, Cycle) {
    std::unique_ptr<List> lst1;
    std::unique_ptr<List> lst2;

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test1" };
        ListNode* n2 = new ListNode{ nullptr,nullptr,nullptr,"test2" };
        ListNode* n3 = new ListNode{ nullptr,nullptr,nullptr,"test3" };
        ListNode* n4 = new ListNode{ nullptr,nullptr,nullptr,"test4" };

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;

        n2->prev = n1;
        n3->prev = n2;
        n4->prev = n3;

        n4->rand = n1;
        n2->rand = n4;
        lst1 = std::make_unique<List>(n1, n4);
    }

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test1" };
        ListNode* n2 = new ListNode{ nullptr,nullptr,nullptr,"test2" };
        ListNode* n3 = new ListNode{ nullptr,nullptr,nullptr,"test3" };
        ListNode* n4 = new ListNode{ nullptr,nullptr,nullptr,"test4" };

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;

        n2->prev = n1;
        n3->prev = n2;
        n4->prev = n3;

        n4->rand = n1;
        n2->rand = n4;
        lst2 = std::make_unique<List>(n1, n4);
    }

    lst1->IsListOk();
    lst2->IsListOk();

    EXPECT_TRUE(*lst1.get() == *lst2.get());
}


TEST(ListCompare, CycleAndNull) {
    std::unique_ptr<List> lst1;
    std::unique_ptr<List> lst2;

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test1" };
        ListNode* n2 = new ListNode{ nullptr,nullptr,nullptr,"test2" };
        ListNode* n3 = new ListNode{ nullptr,nullptr,nullptr,"test3" };
        ListNode* n4 = new ListNode{ nullptr,nullptr,nullptr,"test4" };

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;

        n2->prev = n1;
        n3->prev = n2;
        n4->prev = n3;

        n4->rand = n1;
        n2->rand = n4;
        lst1 = std::make_unique<List>(n1, n4);
    }
    {
        lst2 = std::make_unique<List>(nullptr, nullptr);
    }

    EXPECT_FALSE(*lst1.get() == *lst2.get());
}


TEST(SerializeDemo, Cycle) {
    std::unique_ptr<List> lst1;
    std::unique_ptr<List> lst2;

    {
        ListNode* n1 = new ListNode{ nullptr,nullptr,nullptr,"test1" };
        ListNode* n2 = new ListNode{ nullptr,nullptr,nullptr,"test2" };
        ListNode* n3 = new ListNode{ nullptr,nullptr,nullptr,"test3" };
        ListNode* n4 = new ListNode{ nullptr,nullptr,nullptr,"test4" };

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;

        n2->prev = n1;
        n3->prev = n2;
        n4->prev = n3;

        n4->rand = n1;
        n2->rand = n4;
        lst1 = std::make_unique<List>(n1, n4);
    }
    {
        lst2 = std::make_unique<List>(nullptr, nullptr);
    }

    FILE* fptr = fopen("temp.txt", "w+");

    lst1->Serialize(fptr);
    rewind(fptr);
    lst2->Deserialize(fptr);

    fclose(fptr);
    //compare

    EXPECT_TRUE(*lst1.get() == *lst2.get());
}
