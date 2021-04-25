#include "FibbTree.hpp"
void fibbHeap::insert(int val) {
        node *newNode = new node;
        newNode->key = val;
        newNode->parent = NULL;
        newNode->child = NULL;
        newNode->left = newNode;
        newNode->right = newNode;

        if (minHeapNode != NULL) {

            (minHeapNode->left)->right = newNode;
            newNode->right = minHeapNode;
            newNode->left = minHeapNode->left;
            minHeapNode->left = newNode;
            if (newNode->key < minHeapNode->key)
                minHeapNode = newNode;
        } else {
            minHeapNode = newNode;
        }
        nodeNumb++;
    }

void fibbHeap::linkParentWithChild(node *ptr2, node *ptr1)  {
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;

    if (ptr1->right == ptr1)
        minHeapNode = ptr1;

    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;

    if (ptr1->child == NULL)
        ptr1->child = ptr2;

    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;
    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;

    if (ptr2->key < (ptr1->child)->key)
        ptr1->child = ptr2;

    ptr1->degree++;
}

void fibbHeap::extractMin() {
    if (minHeapNode == NULL)
        cout << "The heap is empty" << endl;
    else {
        node* temp = minHeapNode;
        node* ptr;
        ptr = temp;
        node* x = NULL;

        if (temp->child != NULL) {
            x = temp->child;
            do {
                ptr = x->right;
                (minHeapNode->left)->right = x;
                x->right = minHeapNode;
                x->left = minHeapNode->left;
                minHeapNode->left = x;

                if (x->key < minHeapNode->key)
                    minHeapNode = x;

                x->parent = NULL;
                x = ptr;
            } while (ptr != temp->child);
        }

        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        minHeapNode = temp->right;

        if (temp == temp->right && temp->child == NULL)
            minHeapNode = NULL;
        else {
            minHeapNode = temp->right;
            consolidate();
        }
        nodeNumb--;
    }

}

void fibbHeap::consolidate() {
    int tmp1;
    double tmp2 = (log(nodeNumb)) / (log(2));
    int tmp3 = tmp2;
    struct node* arr[tmp3];

    for (int i = 0; i <= tmp3; i++)
        arr[i] = NULL;

    node* ptr1 = minHeapNode;
    node* ptr2;
    node* ptr3;
    node* ptr4 = ptr1;

    do {
        ptr4 = ptr4->right;
        tmp1 = ptr1->degree;

        while (arr[tmp1] != NULL) {
            ptr2 = arr[tmp1];
            if (ptr1->key > ptr2->key) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }

            if (ptr2 == minHeapNode)
                minHeapNode = ptr1;

            linkParentWithChild(ptr2, ptr1);

            if (ptr1->right == ptr1)
                minHeapNode = ptr1;

            arr[tmp1] = NULL;
            tmp1++;
        }
        arr[tmp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != minHeapNode);

    minHeapNode = NULL;

    for (int j = 0; j <= tmp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (minHeapNode != NULL) {
                (minHeapNode->left)->right = arr[j];
                arr[j]->right = minHeapNode;
                arr[j]->left = minHeapNode->left;
                minHeapNode->left = arr[j];
                if (arr[j]->key < minHeapNode->key)
                    minHeapNode = arr[j];
            }
            else {
                minHeapNode = arr[j];
            }
            if (minHeapNode == NULL)
                minHeapNode = arr[j];

            else if (arr[j]->key < minHeapNode->key)
                minHeapNode = arr[j];
        }
    }
}

