#pragma once

#include <iostream>
using namespace std;

class Node
{
public:
    char data;
    Node* next;
};


class List
{
private:

    Node* head;
    int size;

public:

    char SearchElement(int pos);
    void Diference(List& L1, List& L2);
    void Unity( List& list1,  List& list2);
    void FindIntersection(List& L1, List& L2);
    bool DeleteElement(char el);

    void Print()
    {
        Node* cur = this->head;

        while (cur != nullptr)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
    }

    void addElement(const char& value)
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        if (isEmpty())
        {
            this->head = newNode;
        }
        else
        {
            Node* current = this->head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        this->size++;
    }

    void SetFirstElement(char value)
    {
        Node* newnode = new Node;
        newnode->data = value;
        newnode->next = nullptr;
        this->head = newnode;
        this->size++;
    }

   /* char SearchElement(int pos)
    {
        pos--;

        if (pos > size)
        {
            throw out_of_range("pos is bigger than size");
        }
        Node* cur = this->head;

        for (int i = 0; i < pos; i++)
        {
            cur = cur->next;
        }

        return cur->data;
    }*/

    Node* GetHead()
    {
        return this->head;
    }


    List()
    {
        this->head = nullptr;
        this->size = 0;
    }

    List(char value)
    {
        this->head = new Node;
        this->head->data = value;
        this->head->next = nullptr;
    }

    List(const List& list)
    {
        this->size = list.size;

        Node* cur = list.head;

        while (cur != nullptr)
        {
            this->pushFront(cur->data);
            cur = cur->next;
        }
    }

    List(List&& other)
    {
        Node* cur = other.head;

        while (cur != nullptr)
        {
            this->pushFront(cur->data);
            cur = cur->next;
        }

        other.clear();
    }

    List& operator=(const List& L)
    {
        Node* currThis = this->head;
        Node* currL = L.head;

        while (currL != nullptr && currThis != nullptr)
        {
            currThis->data = currL->data;

            currL = currL->next;
            currThis = currThis->next;
        }

        while (currL != nullptr)
        {
            pushFront(currL->data);
            currL = currL->next;
        }

        return *this;
    }

    List& operator=(List&& list)
    {
        Node* cur = list.head;

        while (cur != nullptr)
        {
            this->pushFront(cur->data);
            cur = cur->next;
        }

        list.clear();
    }

    inline ostream& operator<<(ostream& os)
    {
        int size = this->getSize();

        for (int i = 0; i < size; i++)
        {
            os << this->SearchElement(i) << " ";
        }

        return os;
    }

    inline ifstream& operator>>(ifstream& is)
    {
        this->clear();
        int size;
        char a;
        cout << "Enter size " << endl;
        cin >> size;

        for (int i = 0; i < size; i++)
        {
            cin >> a;
            this->pushFront(a);
        }

        return is;
    }

    void Sethead(Node* head)
    {
        this->head = head;
    }

    void SetSize(int size)
    {
        this->size = size;
    }

    int GetSize()
    {
        return this->size;
    }

    void pushFront(const char& value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        size++;
    }

    void popFront() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }

    bool isEmpty() const {
        return (head == nullptr);
    }

    int getSize() const {
        return size;
    }

    char& front() {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    const char& front() const {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    ~List()
    {
        clear();
    }
};

