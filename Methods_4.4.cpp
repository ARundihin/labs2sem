#include "Header_4.4.h"

void List::Unity(List& L1, List& L2)
{
    Node* cur1 = L1.GetHead();
    Node* cur2 = L2.GetHead();
    bool o = true;

    while (cur1 != nullptr)
    {
        char k = cur1->data;

        while (cur2 != nullptr)
        {
            if (cur2->data == k)
            {
                o = false;
            }

            cur2 = cur2->next;
        }

        if (o)
        {
            this->pushFront(k);
        }

        o = true;
        cur2 = L2.GetHead();
        cur1 = cur1->next;
    }

    cur1 = L1.GetHead();
    cur2 = L2.GetHead();

    while (cur2 != nullptr)
    {
        char k = cur2->data;

        while (cur1 != nullptr)
        {
            if (cur1->data == k)
            {
                o = false;
            }

            cur1 = cur1->next;
        }

        if (o)
        {
            this->pushFront(k);
        }

        o = true;
        cur1 = L1.GetHead();
        cur2 = cur2->next;
    }
}

void List::FindIntersection(List& L1, List& L2)
{
    Node* cur1 = L1.GetHead();
    Node* cur2 = L2.GetHead();
    bool o = true;

    while (cur1 != nullptr)
    {
        char k = cur1->data;

        while (cur2 != nullptr)
        {
            if (cur2->data == k)
            {
                o = false;
            }

            cur2 = cur2->next;
        }

        if (!o)
        {
            this->pushFront(k);
        }

        o = true;
        cur2 = L2.GetHead();
        cur1 = cur1->next;
    }
}

void List::Diference(List& L1, List& L2)
{
    Node* cur1 = L1.GetHead();
    Node* cur2 = L2.GetHead();
    bool o = true;

    while (cur1 != nullptr)
    {
        char k = cur1->data;

        while (cur2 != nullptr)
        {
            if (cur2->data == k)
            {
                o = false;
            }

            cur2 = cur2->next;
        }

        if (o)
        {
            this->pushFront(k);
        }

        o = true;
        cur2 = L2.GetHead();
        cur1 = cur1->next;
    }
}

bool List::DeleteElement(char el)
{
    Node* curr = this->GetHead();
    Node* prev = curr;

    if (curr->data == el)
    {
        this->head = curr->next;
    }

    while (curr->data != el)
    {
        curr = curr->next;

        if (curr == nullptr)
        {
            return 0;
        }
        else if (curr->data != el)
        {
            prev = prev->next;
        }
    }

    prev->next = curr->next;

    delete curr;

    return 1;
}
