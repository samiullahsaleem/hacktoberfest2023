#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};


Node* newNode(int data, Node* next) {
    Node* node = new Node;
    node->data = data;
    node->next = next;
    return node;
}

void insert(Node** head, int data) {
    Node* node = newNode(data, *head);
    *head = node;
}

void selectionSort(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* min = current;
        Node* temp = current->next;
        while (temp != NULL) {
            if (temp->data < min->data) {
                min = temp;
            }
            temp = temp->next;
        }
        int tempData = current->data;
        current->data = min->data;
        min->data = tempData;
        current = current->next;
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    Node* head = NULL;
    insert(&head, 5);
    insert(&head, 2);
    insert(&head, 8);
    insert(&head, 1);
    insert(&head, 3);
    cout << "Original list: ";
    printList(head);
    selectionSort(head);
    cout << "Sorted list: ";
    printList(head);
    return 0;
}
