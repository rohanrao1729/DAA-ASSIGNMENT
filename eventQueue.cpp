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
// User Defined data type representation of an eventQueue with points, left and right event queues and vector of line segments
typedef struct{
    Point eventPoint;
    eventQueue* left;
    eventQueue* right;
    vector<Line> lineSegments;
    int height;
}eventQueue;
// function that calculates the height of the eventQueue.
int height(eventQueue* node){
    if(node == NULL)
        return 0;
    return node->height;
}

// function that creates a new event queue and returns it.
eventQueue *createeventQueueNode(Point eventPoint, vector<Line> lineSegments) {
    eventQueue *newnode = new eventQueue();
    newnode->eventPoint = eventPoint;
    newnode->lineSegments = lineSegments;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
// the function rightRotate is called while insertion or deletion to maintain the balance of binary search tree.
eventQueue *rightRotate(eventQueue *y){
    eventQueue *x = y->left;
    eventQueue *z = x->right;
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

// the function leftRotate is called while insertion or deletion to maintain the balance of binary search tree.
eventQueue *leftRotate(eventQueue *y){
    eventQueue *x = y->right;
    eventQueue *z = x->left;
    x->left = y;
    y->right = z;
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

// function to find the height difference between left and right subtree for a given node.
int heightDiff(eventQueue* node){
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}


// function to insert the eventPoints in the statusQueue which is a balanced binary search tree.
eventQueue* insertin(eventQueue* root, Point eventPoint, vector<Line> lineSegments){
    // if root is null, create a new event queue node
    if (root == NULL){
        return createeventQueueNode(eventPoint, lineSegments);
    }
    // insert at the right
    if(eventPoint.y>root->eventPoint.y || (eventPoint.y == root->eventPoint.y && eventPoint.x<root->eventPoint.x)){
        root->right = insertin(root->right, eventPoint, lineSegments);
    }
    // insert at the end
    else if(eventPoint.y==root->eventPoint.y && eventPoint.x==root->eventPoint.x){
        root->lineSegments.insert(root->lineSegments.end(), lineSegments.begin(), lineSegments.end());
    }
    // insert at the left
    else{
        root->left = insertin(root->left, eventPoint, lineSegments);
    }
    root->height =(height(root->left) > height(root->right))? height(root->left) + 1 : height(root->right) + 1 ;

    int difference = heightDiff(root);
    if (difference > 1 && eventPoint.y < root->eventPoint.y || (eventPoint.y == root->eventPoint.y && eventPoint.x > root->eventPoint.x)){
        return rightRotate(root);
    }
    if (difference < -1 && eventPoint.y > root->eventPoint.y || (eventPoint.y == root->eventPoint.y && eventPoint.x<root->eventPoint.x)){
        return leftRotate(root);
    }
    if (difference > 1 && eventPoint.y > root->eventPoint.y || (eventPoint.y == root->eventPoint.y && eventPoint.x<root->eventPoint.x)){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (difference < -1 && eventPoint.y < root->eventPoint.y || (eventPoint.y == root->eventPoint.y && eventPoint.x > root->eventPoint.x)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
// preorder traversal of a binary search tree.
void preOrder(eventQueue *root){
    if(root != NULL){
        preOrder(root->left);
        cout << root->eventPoint.x << " " <<root->eventPoint.y<<"  ";
        preOrder(root->right);
    }
}
// function to find the minimum value event in the event queue.
eventQueue * minValueEvent(eventQueue* event){
    eventQueue* currentEvent = event;
    while (currentEvent->left != NULL)
        currentEvent = currentEvent->left;
    return currentEvent;
}
// check balance.
int getBalance(eventQueue *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
// function to delete event from the eventQueue.
eventQueue* deleteEvent(eventQueue* root){
    if (root == NULL)
        return root;
    if(root->right!=NULL)
        root->right = deleteEvent(root->right);
    else{
        if( (root->left == NULL)||(root->right == NULL)){
            eventQueue *tempEvent = root->left ? root->left : root->right;
            if (tempEvent == NULL){
                tempEvent = root;
                root = NULL;
            }
            else{
                *root = *tempEvent;
            }
            free(tempEvent);
        }else{
            eventQueue* tempEvent = minValueEvent(root->right);
            root->eventPoint = tempEvent->eventPoint;
            root->lineSegments = tempEvent->lineSegments;
            root->right = deleteEvent(root->right);
        }
    }
    if (root == NULL){
        return root;
    }
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// function to get the next event in the eventQueue.
eventQueue getNextEvent(eventQueue *root){
    eventQueue *temp = root;
    while(temp->right!=NULL){
        temp = temp->right;
    }
    eventQueue e = *temp;
    return e;
}

int main()
{
    return 0;
}
