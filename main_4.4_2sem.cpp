#include <iostream>
#include "Header_4.4.h"

using namespace std;

int main()
{
    List L1;
    List L2;
    List L;
    int s1, s2;
    char a;

    cout << "Enter size of L1" << endl;
    cin >> s1;
    cout << "Enter L1" << endl;

    for (int i = 0; i < s1; i++)
    {
        cin >> a;
        L1.addElement(a);
    }

    /*cout << "Enter size of L2" << endl;
    cin >> s2;
    cout << "Enter L2" << endl;

    for (int i = 0; i < s2; i++)
    {
        cin >> a;
        L2.addElement(a);
    }

    L.Diference(L1, L2);
    Node* cur = L.GetHead();
    */

    L1.DeleteElement('a');

    Node* cur = L1.GetHead();

    while (cur != nullptr)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
}
