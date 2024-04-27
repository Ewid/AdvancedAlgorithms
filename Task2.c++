#include <iostream>
using namespace std;

// First of all a doubly linked list is type of data structure that has nodes, pointer to the next node in the sequence and pointer to the previous node allowing forward and backward traversal.
// Nodes are the elements of the list, containing data (numbers here) and pointers to the next and previous nodes.
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

// Get Last node is a while loop that keeps going to the next until there is no next basically meaning you go to the last node in the list, to use it as a pivot in our case.
Node* getLastNode(Node* head) {
    while (head && head->next) {
        head = head->next;
    }
    return head;
}

// Partitioning: Rearranges the elements so that elements less than the pivot are on the left, and elements greater than the pivot are on the right we use two pointers that traverse the list.
// The pivot is the last element of the list , it can be done in other ways but we chose to do it this way in this algorithm.
Node* partition(Node* low, Node* high) {
    int pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == nullptr) ? low : i->next;
            swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swap(i->data, high->data);
    return i;
}

// Quick sort is a well known and usually used on array structure instead of this type, it is an very efficient divide and conquer sorting algorithm with a time complexity of O(n log n).
// Quick sort is more efficient for larger datasets.
// Why did we use this? Quick sort is much faster than the insertion sort with a complexity of O(n^2) making it less efficient , Merge sort is the same time complexity but provides more stability.
// Using it on a doubly linked list has some benefits like moving backwards during partitioning easier than arrays exploiting node manipulation. Here we will be moving pointers instead of indices.
// Which is efficient as we wont need to shift elements as done usually in arrays.
// After partitioning we apply quicksort to the list and recursively onto the sub lists before and after the pivot.
// O(logn) on average for the stack space due to recursion. In the worst case, it can be O(n) if the pivot is the smallest or largest element at each step.
// Time complexity Best Case, average case  would be the pivot splitting the list into two equal parts at each step O(n log n), Worst case is when the pivot the smallest/largest element at each step.
// Merge sort would have been better because it relinks the nodes instead of moving any data making its complexity always O(n log n) because quick sort can be affected by the pivot chosen.
void quickSort(Node* low, Node* high) {
    if (high != nullptr && low != high && low != high->next) {
        Node* p = partition(low, high);
        quickSort(low, p->prev);
        quickSort(p->next, high);
    }
}

// Prints the list by using a while loop to access the nodes data then going to the next node until there is no nodes left.
void printList(Node* node) {
    while (node) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    // Here we created the first node and then every other node with head looking to next and previous.
    Node* head = new Node(30);
    head->next = new Node(3);
    head->next->prev = head;
    head->next->next = new Node(4);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(20);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->prev = head->next->next->next;

    Node* last = getLastNode(head);
    cout << "Unsorted Linked List : ";
    printList(head);

    quickSort(head, last);

    cout << "Sorted Link List: ";
    printList(head);

    return 0;
}
