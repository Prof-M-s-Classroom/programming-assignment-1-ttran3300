#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node {
public:
    T& data;
    Node* next;
    Node* prev;

    Node(T& d) : data(d), next(nullptr), prev(nullptr) {}
    void print() { cout << data << " "; }
};

class CelestialNode {
private:
    string name;
    double distance_from_earth;
    string mission_log;

public:
    CelestialNode(const string& n, double d, const string& log);
    const string& getName() const { return name;}
    double getDistance() const { return distance_from_earth;}
    const string& getMissionLog() const { return mission_log;}
    void print() const { cout << name << " (" << distance_from_earth << " AU) - " << mission_log << endl; }
};

template <typename T>
class SpaceRoute {
private:
    Node<T>* head;
    Node<T>* tail;
    int length;

public:
    // Constructor //TIME COMPLEXITY: O(1)
    SpaceRoute() : head(nullptr), tail(nullptr), length(0){}

    // Destructor //TIME COMPLEXITY: O(n)
    ~SpaceRoute() {
        Node<T> *temp = head;
        while (head) {
            head = head->next;      //moves head to nextnode
            delete temp;            //deletes old head node
            temp = head;            //temp to new head
        }
    }

    //get and set
    Node<T>* getHead() {
        if (head == nullptr) { //checks if list is empty
            cout<<"Head: nullptr, list is empty" <<endl;
        } else { //if not empty then print head
            cout<<"Head: "<< head->data <<endl;
        }
        return head;
    }
    //TIME COMPLEXITY: O(1)

    Node<T>* getTail() {
        if (tail == nullptr) { //checks if list is empty
            cout<<"Tail: nullptr, list is empty" <<endl;
        } else { //if not empty then print head
            cout<<"Tail: "<< tail->data <<endl;
        }
        return tail;
    }
    //TIME COMPLEXITY: O(1)

    int getLength() {
        cout<<"Length: "<<length<<endl; //prints length of the list... depending if we are adding or removing
        return length;
    }
    //TIME COMPLEXITY: O(1)

    void addWaypointAtBeginning(T& data){
        Node<T>* newNode = new Node<T>(data); //creates a new node w/ data

        if (head == nullptr) {      //checks if list is empty
            head = newNode;         //sets head & tail to new node (since it is the only node)
            tail = newNode;
        } else {                    //if list is not empty
            newNode->next = head;   //new node pts to current head
            head->prev = newNode;   //old head previous is new node
            head = newNode;         //new node updates as head
        }
        length++;                   //increments +1 for length since we are adding a new node
    }
    //TIME COMPLEXITY: O(1)

    void addWaypointAtEnd(T& data) {
        Node<T>* newNode = new Node<T>(data); //creates a new node w/ data

        if (head == nullptr) {      //checks if list is empty
            head = newNode;         //sets head & tail to new node
            tail = newNode;
        } else {
            newNode->prev = tail;   //new node previous pts to current tail
            tail->next = newNode;   //old tail pts to new node
            tail = newNode;         //new node updates as tail
        }
        length++;                   //increments +1 for length since we are adding a new node
    }
    //TIME COMPLEXITY: O(1)

    void addWaypointAtIndex(int index, T& data) {
        Node<T>* newNode = new Node<T>(data);   //creates a new node w/ data
        Node<T>* current = head;
        int count = 0;

        if (index < 0 || index >= length) { //checks if index is out of bounds
            cout<< "Error: Index is out of bounds. Index cannot be a negative or greater than length."<<endl;
            return;
        }

        if (index == 0) { //checks if index is 0... then adds node to beginning of the list since 0 is the first node
            addWaypointAtBeginning(data); //calls the function to add the first node
            return;
        }

        if (index == length) { //checks if index is equal to the length of the list... then adds node to end of the list
            addWaypointAtEnd(data); //calls the function to add the last node
            return;
        }

       //moves through the list to find where to insert
       while (current != nullptr && count < index - 1) { //checks till the end of the list and stops one node before correct index to insert
           current = current->next;                      //moves to next node
           count++;                                      //increments count
       }
       //inserts node
       newNode->next = current->next;                    //updates the next ptr of new node to point to the node after the current node
       newNode->prev = current;                          //updates the prev ptr of new node to point to current node

       if (current->next != nullptr) {                   //if there is a node after the current node... prev pointer is updated to the new node
           current->next->prev = newNode;
       }
       current->next = newNode;                          //updates current next pointer to pt at new node
       length++;                                         //increments +1 for length since we are adding a new node
   }
    //TIME COMPLEXITY: O(n)

    void removeWaypointAtBeginning() {
        if (head == nullptr) {      // checks if list is empty
            cout<<"The list is empty"<<endl;
            return;
        }

        Node<T>* temp = head;       //stores current head in temp
        if (length == 1) {          //if there is only 1 node
            head = nullptr;         //head & tail are set to nullptr.. meaning the list is empty
            tail = nullptr;
        } else {                    //if more than 1 node
            head = head->next;      //set head to next node
            head->prev = nullptr;   //set prev ptr of new head to nullptr
        }
        delete temp;                //deletes old head node
        length--;                   //decrements -1 of length since we removed a node
    }
    //TIME COMPLEXITY: O(1)

    void removeWaypointAtEnd() {
        if (head == nullptr) { // checks if list is empty
            cout<<"The list is empty"<<endl;
            return;
        }

        Node<T>* temp = head;    //stores current head in temp
        if (length == 1) {       //if there is only 1 node
            head = nullptr;      //head & tail are set to nullptr.. meaning the list is empty
            tail = nullptr;
        } else {                 //if more than 1 node
            Node<T> *pre = head;    //create a ptr
            while (temp->next) {    //transverse through the list...until the last node
                pre = temp;         //pre ptr becomes current node
                temp = temp->next;  //move temp to the next node
            }
            tail = pre;             //sets tail to second to last node (not last node)
            tail->next = nullptr;   //sets the next ptr to new tail to null ptr
        }
        delete temp;                //deletes old tail node
        length--;                   //decrements -1 of length since we removed a node
    }
    //TIME COMPLEXITY: O(n)

    void removeWaypointAtIndex(int index){
    Node<T>* current = head;    //sets current to begin at the "head" of the list
    int count = 0;              //count to keep track when transversing through list

    if (index < 0 || index >= length) { //checks if index is out of bounds
        cout<< "Error: Index is out of bounds. Index cannot be a negative or greater than length."<<endl;
        return;
    }

    if (index == 0) { //checks if index is 0... then removes node to beginning of the list since 0 is the first node
        removeWaypointAtBeginning();//calls the function to remove the first node
        return;
    }

    if (index == length - 1) { //checks if index is equal to the length of the list... then removes node to end of the list
        removeWaypointAtEnd(); //calls the function to remove the last node
        return;
    }

    //moves through the list to find where to insert
    while (current != nullptr && count < index) { //checks till the end of the list and stops one node before correct index to insert
        current = current->next;                  //moves to next node
        count++;                                  //increments count
    }

    current->prev->next = current->next;          //updates the prev node next ptr to skip current node
    current->next->prev = current->prev;          //updates the next node prev ptr to skip current node

    delete current;                               //deletes node
    length--;                                     //decrements -1 for length since we are adding a new node
}
    //TIME COMPLEXITY: O(n)

    void traverseForward() {
        Node<T>* current = head;             //sets current to begin at the "head" of the list

        while (current != nullptr) {         //traverse through the list while current is not null (goes through the list)
            cout<< current->data << " ";     //prints current node and adds space
            current = current->next;         //moves to the next node and sets as current
        }
        cout<<endl;                          //prints new lin
    }
    //TIME COMPLEXITY: O(n)

    void traverseBackward() {
        Node<T>* current = tail;            //sets current to begin at the "tail" of the list... starting from the last node

        while (current != nullptr) {        //traverse through the list while current is not null (goes through the list)
            cout<< current->data << " ";    //prints current node and adds space
            current = current->prev;        //moves to the prev node and sets as current
        }
        cout<<endl;                         //prints new line
    }
    //TIME COMPLEXITY: O(n)

    Node<T>* getWaypoint(int index){
    if (index < 0 || index >= length) {     //checks if index is out of bounds
        cout<< "Error: Index is out of bounds. Index cannot be a negative or greater than length."<<endl;
        return nullptr;
    }
        Node<T> *temp = head;               //sets temp to head
        for (int i = 0; i < index; ++i) {   //iterates through the list until reaching specified index
            temp = temp->next;              //moves temp to next node for each iteration
        }
        return temp;                        //returns the node at the specified index
    }
    //TIME COMPLEXITY: O(n)

    void setWaypoint(int index, T& data) {
        Node<T>* temp = getWaypoint(index);     //get node of specified index
        if (temp) {                             //checks if the node exists
            temp->value = data;                 //sets value of node to  data
        } else {                                //if node does not exist... print error msg
            cout<<"Error: Index is out of bounds."<<endl;
        }
    }
    //TIME COMPLEXITY: O(n)

    void print(){

            Node<T>* current = head;        //sets current to the head of list (first node)
            while (current) {               //transverse the list while current is not null
                current->print();           //call print method for current node to print
                current = current->next;    //moves to the next node
            }
            cout << endl;                   //prints new line
        }
    //TIME COMPLEXITY: O(n)

};
