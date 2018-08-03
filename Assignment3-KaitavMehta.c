//Days Algorithm writteb by Kaitav Mehta for Assignment 3
// Topics in BioInformatrics 23/07/2018



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define COUNT 10
#define SIZE 20

//Hash table structure
struct DataItem
{
    struct node *hashData;
    int key;
};
struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;


//Binary Tree Structure
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

//Creates a new Node
struct node* newNode(int data);

//used to print the binary tree
void print2DUtil(struct node *root, int space);
void print2D(struct node *root);

//Change lable of Tree T1 according to preorder and create a labelling array to change labels in Tree T2
void preorderTreeTraversal(struct node *root);
//Change lables of Tree T2
void preorderTreeTraversalOfT2AndRelabelling(struct node *root);

//Create HashTable according to algo w.r.t Tree T1
void preorderTraversalForHashTableInsertion(struct node* node,int parentNode);

//Print a tree in pree order
void printPreorder(struct node* node);

//Sets maximum and minimun in a given Tree
void setMaxMinInSubTree(struct node* node);

//
void findGoodEdgesInTree(struct node* node);

//Prints HashArray
void displayHashArray();

//Inserts values in HashArray
void insertInHashArray(int key,int dataArray[],int sizeOfArray);

//Searches value in HashTable
struct DataItem *search(int key);


int labellingArray[100];
int maxInSubTree=0;
int minInSubTree =100;
int sizeInSubTree = 0;
int preOrderCount = 1;
int totalGoodEdges = 0;

int maxNodeCount =0;
int treeData = 0;
int leftChild = -1;
int rightChild = -1;
int defaultInput = 1;


int main()
{
    printf("Hello world welcome to Day's Algorithm- Coded by Kaitav Mehta!\n");

    printf("\n");
    printf("Press 1 for default Tree input OR Press 0 for manual Tree Input :");
    scanf("%d",&defaultInput);

    struct node *T1 = newNode(0);
    struct node *T2 = newNode(0);
    if(defaultInput == 0)
    {

        printf("Enter how many nodes tree has:");
        scanf("%u",&maxNodeCount);
        printf("\n");
        printf("\n");
        printf("Enter the tree in preorder.\n");

        printf("Follow Steps stated as below to create a Tree\n");
        printf("Enter value of node, if its the leaf node then end the tree branch by adding -1 for both left and right child. Keep track of preOrder while creating tree.\n");
        printf("Enter negative value if a node dosen't have a specific child. Please check readme for an example of insertion of Tree \n");


        printf("Enter tree T1 Root value:");
        scanf("%u",&treeData);
        T1->data = treeData;
        scanLeftAndRightChild(T1,treeData);
        printf("-------------------------------------Initial Tree T1--------------------------------\n");
        printf("------------------------------------------------------------------------------------");
        printf("\n");
        print2D(T1);

        printf("Enter tree T2 Root value:");
        scanf("%u",&treeData);
        T2->data = treeData;
        scanLeftAndRightChild(T2,treeData);
        printf("-------------------------------------Initial Tree T2------------------------------\n");
        printf("------------------------------------------------------------------------------------");
        print2D(T2);

    }
    else
    {

        //Default Tree Inputs
        maxNodeCount =5;
        T1->data = 5;
        T1->left        = newNode(NULL);
        T1->left->right       = newNode(4);
        T1->left->left  = newNode(NULL);
        T1->left->left->left  = newNode(3);
        T1->left->left->right  = newNode(NULL);
        T1->left->left->right->left  = newNode(1);
        T1->left->left->right->right  = newNode(2);
        printf("-------------------------------------Initial Tree T1--------------------------------\n");
        printf("------------------------------------------------------------------------------------");
        printf("\n");
        print2D(T1);

        T2->data = 5;
        T2->left        = newNode(NULL);
        T2->left->right       = newNode(4);
        T2->left->left  = newNode(NULL);
        T2->left->left->left  = newNode(1);
        T2->left->left->right  = newNode(NULL);
        T2->left->left->right->left  = newNode(2);
        T2->left->left->right->right  = newNode(3);
        printf("-------------------------------------Initial Tree T2------------------------------\n");
        printf("------------------------------------------------------------------------------------");
        print2D(T2);


    }
    /* Change the labelling of the Tree T1 as per preorder and create a labellingArray to change corresponding value in Tree T2 as per Tree T1*/
    preorderTreeTraversal(T1);
    printf("-------------------------------------Altered Tree T1----------------------------------------\n");
    printf("------------------------------------------------------------------------------------");
    print2D(T1);
    printf("\n");


    for(int i=1; i < maxNodeCount; i++)
    {
        printf(" Node %d is subsituted with : node vale:%d \n",i,labellingArray[i]);
    }

    preorderTreeTraversalOfT2AndRelabelling(T2);
    printf("-------------------------------------Altered Tree T2----------------------------------------\n");
    printf("------------------------------------------------------------------------------------");
    print2D(T2);


    // Step 3 ---If u is the leftmost child of its parent in T1, set H[ju] to be iu..ju;
    //otherwise, set H[iu] to be iu..ju.
    preorderTraversalForHashTableInsertion(T1,0);

    printf("Hash Table values: \n");
    displayHashArray();

    printf("\n");
    printf("Prints Max,Min and Size of Each Sub Tree and Corresponding Value of H[max] and H[Min] if exists for each Internal Node\n");
    //Calculate no of good edges in Tree T2 corresponding to Tree T1
    findGoodEdgesInTree(T2);
    printf("\n");
    printf("Total No of internal node good edges :%d \n",totalGoodEdges-1);

    // Total no of edges in Tree - Total leaf nodes - Total Good edeges-> Gives count of bad Edges
    int disSimilarityScore = (2*maxNodeCount - 3)- (maxNodeCount-1) - totalGoodEdges;
    printf("\n");
    printf(" Total no of edges in Tree - Total leaf nodes - Total Good edeges-> Gives count of bad Edges.\n");
    printf("Robinson-Folds distance for measuring the dis-similarity score is: %d ",disSimilarityScore);
    printf("\n");
    printf("\n");
    return 0;
}

//This method recursively takes input from user for Tree Creation whose Robinsons fold distance is to be calculated.
void scanLeftAndRightChild(struct node *node,int parent)
{
    printf("Enter left child of : %d \n",parent);
    scanf("%u",&leftChild);
    if(leftChild >= 0)
    {
        node->left = newNode(leftChild);
        scanLeftAndRightChild(node->left,leftChild);
    }

    printf("Enter right child of: %d\n",parent);
    scanf("%u",&rightChild);
    if(rightChild >= 0)
    {
        node->right = newNode(rightChild);
        scanLeftAndRightChild(node->right,rightChild);
    }

}


/* Change the labelling of the Tree T1 as per pre order and create a labellingArray to change corresponding value in Tree T2 as per Tree T1*/
void preorderTreeTraversal(struct node* node)
{

    if (node == NULL)
        return;

    /* first print data of node */

    if(node->data > 0 && node->data != maxNodeCount)
    {

        labellingArray[node->data] = preOrderCount;
        node->data = preOrderCount;
        preOrderCount++;

    }

    /* then recur on left sutree */
    preorderTreeTraversal(node->left);

    /* now recur on right subtree */
    preorderTreeTraversal(node->right);
}

/*Change labelling of Tree T2 as per labelling array.*/
void preorderTreeTraversalOfT2AndRelabelling(struct node* node)
{

    if (node == NULL)
        return;

    /* first print data of node */

    if(node->data > 0 && node->data != maxNodeCount)
    {
        node->data =  labellingArray[node->data];
    }

    /* then recur on left sutree */
    preorderTreeTraversalOfT2AndRelabelling(node->left);

    /* now recur on right subtree */
    preorderTreeTraversalOfT2AndRelabelling(node->right);
}

//Creates a HashTable Corresponding to Tree T1
/*If parent node is 0 then it is left child if parent node is 1 then it is right child*/
void preorderTraversalForHashTableInsertion(struct node* node,int parentNode)
{
    if (node == NULL)
        return;


    if(node->data == 0)
    {

        maxInSubTree=0;
        minInSubTree =100;
        setMaxMinInSubTree(node);

        int dataArray[20];
        int sizeOfArray = 0;
        for(int i = minInSubTree; i<=maxInSubTree; i++)
        {
            dataArray[sizeOfArray] = i;
            sizeOfArray++;
        }
        //sizeOfArray++;
        if(parentNode == 0)
        {
            insertInHashArray(maxInSubTree,dataArray,sizeOfArray);
        }
        else
        {
            insertInHashArray(minInSubTree,dataArray,sizeOfArray);
        }
    }

    /* then recur on left sutree */
    preorderTraversalForHashTableInsertion(node->left,0);

    /* now recur on right subtree */
    preorderTraversalForHashTableInsertion(node->right,1);
}



/*Travers Tree T2 and find number of Good edges

    for every internal node u in T2 do
    Compute minu, maxu, and sizeu
    if maxu − minu + 1 = sizeu then
    if either H[minu] or H[maxu] equals minu..maxu, (u, v) is a good
    edge where v is the parent of u in T2

*/
void findGoodEdgesInTree(struct node* node)
{
    if (node == NULL)
        return;

//   printf("node data :%d \n",node->data);
    if(node->data == 0)
    {
        printf("--------------------------------------\n");
        //find max and min of the sub tree
        maxInSubTree=0;
        minInSubTree =100;
        sizeInSubTree = 0;
        setMaxMinInSubTree(node);

        printf("Min : %d\n",minInSubTree);
        printf("Max : %d\n",maxInSubTree);
        printf("Size of tree :%d\n",sizeInSubTree);

        if(( maxInSubTree - minInSubTree +1) == sizeInSubTree)
        {
            int minU = minInSubTree;
            int maxU = maxInSubTree;

            // looping over hash array
            for(int i = 0; i<SIZE; i++)
            {

                if(hashArray[i] != NULL)
                {

                    if(hashArray[i]->key == maxInSubTree)
                    {

                        printf("H[max]-- valuess:\n");
                        printPreorder(hashArray[i]->hashData);
                        printf("\n");
                        //Update Maximun and Minimum according to Tree T1 from Hash Table
                        maxInSubTree=0;
                        minInSubTree =100;
                        setMaxMinInSubTree(hashArray[i]->hashData);
                        if(minInSubTree == minU && maxInSubTree == maxU)
                        {
                            totalGoodEdges++;
                        }
                    }
                    else if(hashArray[i]->key == minInSubTree)
                    {

                        printf("H[min]-- valuess:");
                        printPreorder(hashArray[i]->hashData);
                        printf("\n");
                        //Update Maximun and Minimum according to Tree T1 from Hash Table
                        maxInSubTree=0;
                        minInSubTree =100;
                        setMaxMinInSubTree(hashArray[i]->hashData);
                        if(minInSubTree == minU && maxInSubTree == maxU)
                        {
                            totalGoodEdges++;
                        }
                    }
                }

            }

        }
    }


    /* then recur on left sutree */
    findGoodEdgesInTree(node->left);

    /* now recur on right subtree */
    findGoodEdgesInTree(node->right);
}

//Finds max, min and size of a subtree
void setMaxMinInSubTree(struct node* node)
{

    if (node == NULL)
        return;

    if(node->data > 0)
    {
        if(maxInSubTree < node->data)
        {
            maxInSubTree = node->data;
        }
        if(minInSubTree > node->data)
        {
            minInSubTree = node->data;
        }
        sizeInSubTree++;

    }

    /* then recur on left sutree */
    setMaxMinInSubTree(node->left);

    /* now recur on right subtree */
    setMaxMinInSubTree(node->right);
}


/*ALL UTILITY FUNCTIONS BELOW!!*/
int hashCode(int key)
{
    return key % SIZE;
}

void insertInHashArray(int key,int dataArray[],int sizeOfArray)
{

    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));


    item->key = key;
    struct node *arrayDataRoot = newNode(0);
    struct node *currentNode = arrayDataRoot;

    for(int i=0; i<sizeOfArray; i++)
    {
        currentNode->left= newNode(dataArray[i]);
        currentNode = currentNode->left;

    }
    item->hashData = arrayDataRoot;


    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1)
    {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}


void displayHashArray()
{
    int i = 0;

    for(i = 0; i<SIZE; i++)
    {

        if(hashArray[i] != NULL)
        {
            printf(" (Key :%d-",hashArray[i]->key);
            //get array from hasharray
            struct node *displayNode = hashArray[i]->hashData;
            printPreorder(displayNode);
            printf(")");
        }
        else
        {
            printf(" ~~ ");
        }
    }

    printf("\n");
}

/* newNode() allocates a new node with the given data and NULL left and
   right pointers. */
struct node* newNode(int data)
{
    // Allocate memory for new node
    struct node* node = (struct node*)malloc(sizeof(struct node));

    // Assign data to this node
    node->data = data;

    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    return(node);
}



/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct node* node)
{
    if (node == NULL)
        return;

    /* first print data of node */
    if(node->data > 0)
    {
        printf("%d ", node->data);
    }

    /* then recur on left sutree */
    printPreorder(node->left);

    /* now recur on right subtree */
    printPreorder(node->right);
}

// Wrapper over print2DUtil()
void print2D(struct node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(struct node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // Process left child
    print2DUtil(root->left, space);
}

