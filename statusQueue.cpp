#include <bits/stdc++.h>
using namespace std;


// User Defined data type representation of a point with it's x and y co-ordinates.
typedef struct{
    int x;
    int y;
    int type;
}Point;
// User Defined data type representation of a line with two end points namely - upper and lower points.
typedef struct {
    int index;
    Point upperPoint;
    Point lowerPoint;
}Line;
// User Defined data type representation of an statusQueue with points, left and right event queues and vector of line segments

typedef struct {
    Line segment;
    statusQueue* left;
    statusQueue* right;
    int height;
}statusQueue;


statusQueue *createStatusQueueNode(Line segment) {
    statusQueue *newnode = new statusQueue();
    newnode->segment = segment;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
// function that calculates the height of the eventQueue.

int height(statusQueue* node){
    if(node == NULL)
        return 0;
    return node->height;
}
// right rotate to balance the bst
statusQueue *rightRotate(statusQueue *y){
    statusQueue *x = y->left;
    statusQueue *z = x->right;
    x->right = y;
    y->left = z;
    if(height(y->left)>(height(y->right)+1))
        y->height=height(y->left);
    else
        y->height=height(y->right)+1;
    if(height(x->left)>(height(x->right)+1))
        x->height=height(x->left);
    else
        x->height=height(x->right)+1;
    return x;
}
// left rotate to balance the bst
statusQueue *leftRotate(statusQueue *y){
    statusQueue *x = y->right;
    statusQueue *z = x->left;
    x->left = y;
    y->right = z;
    if(height(y->left)>(height(y->right)+1)){
        y->height=height(y->left);
    }
    else{
        y->height=height(y->right)+1;
    }
    if(height(x->left)>(height(x->right)+1)){
        x->height=height(x->left);
    }
    else{
        x->height=height(x->right)+1;
    }
        
    return x;
}
// function to calculate the height difference of left and right subtree.
int heightDiff(statusQueue* node){
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}
// how to compare l1 and l2
int compare(Line l1, Line l2){
    if(l1.upperPoint.y>l2.upperPoint.y ||
      (l1.upperPoint.y == l2.upperPoint.y && l1.upperPoint.x<l2.upperPoint.x) ||
      (l1.upperPoint.y == l2.upperPoint.y && l1.upperPoint.x==l2.upperPoint.x && l1.lowerPoint.y>l2.lowerPoint.y) ||
      (l1.upperPoint.y == l2.upperPoint.y && l1.upperPoint.x==l2.upperPoint.x && l1.lowerPoint.y == l2.lowerPoint.y) && l1.lowerPoint.x<l2.lowerPoint.x ){
        return 1;
      }
    return 0;
}
// function to insert in the status queue.
statusQueue* insertin(statusQueue* root, Line l1){
    // if root is null, create the new status queue node.
    if (root == NULL){
        return createStatusQueueNode(l1);
    }
        
    
    if(compare(l1,root->segment)){
        root->right=insertin(root->right,l1);
    }
    else{
        root->left=insertin(root->left,l1);
    }   
    root->height =(height(root->left) > height(root->right))? height(root->left) + 1 : height(root->right) + 1 ;

    int diff = heightDiff(root);
    if (diff > 1 && compare(root->segment,l1)){
        return rightRotate(root);
    }
        
    if (diff < -1 && compare(l1,root->segment)){
        return leftRotate(root);
    }
        
    if (diff > 1 && compare(l1,root->segment)){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (diff < -1 && compare(root->segment,l1)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// function to check the minimum value segement in the status queue.
statusQueue * minValueSegment(statusQueue* segment){
    statusQueue* current = segment;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// check balance in status queue.
int getBalance(statusQueue *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

statusQueue* deleteSegment(statusQueue* root){
    if (root == NULL)
        return root;
    if(root->right!=NULL)
        root->right = deleteSegment(root->right);
    else{
        if( (root->left == NULL)||(root->right == NULL)){
            statusQueue *temp = root->left ? root->left : root->right;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp;
            }
            free(temp);
        }else{
            statusQueue* temp = minValueSegment(root->right);
            root->segment = temp->segment;
            root->right = deleteSegment(root->right);
        }
    }
    if (root == NULL){
        return root;
    }
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0){
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0){
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


int main()
{
    return 0;
}
