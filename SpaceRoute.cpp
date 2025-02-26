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

public:
    // Constructor
    SpaceRoute() : head(nullptr), tail(nullptr) {}

    // Destructor
    ~SpaceRoute() {
        Node<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void addWaypointAtBeginning(T& data){
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {      //checks if list is empty
            head = newNode;         //sets head & tail to new (since it is the only node)
            tail = newNode;
        } else {                    //if list is not empty
            newNode->next = head;   //new node pts to current head
            head->prev = newNode;   //old head previous is new node
            head = newNode;         //new node updates as head
        }
    }

    void addWaypointAtEnd(T& data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {      //checks if list is empty
            head = newNode;         //sets head & tail to new node
            tail = newNode;
        } else {
            newNode->prev = tail;   //new node previous pts to current tail
            tail->next = newNode;   //old tail pts to new node
            tail = newNode;         //new node updates as tail
        }
    }

    void addWaypointAtIndex(int index, T& data) {
        //FIX THIS: when index is more than amount of elements and getters/setters
        Node<T>* newNode = new Node<T>(data);
        Node<T>* current = head;
        int count = 0;

        if (index < 0) {
            cout<< "Index is out of bounds. Index cannot be a negative."<<endl;
            return;
        }

        if (index == 0) {
            addWaypointAtBeginning(data);
            return;
        }

        if (current->next == nullptr) {
            addWaypointAtEnd(data);
            return;
        }

        //continue here
    }

    void removeWaypointAtBeginning() {
        if (head == nullptr) {      // checks if list is empty
            cout<<"The list is empty"<<endl;
            return;
        }

        Node<T>* temp = head;       //stores current head in temp
        head = head->next;          //moves head to next node

        if (head != nullptr) {      //checks if head is not null (there are nodes..not empty)
            head->prev = nullptr;   //updates new head to prev pointer (since it is a double link list)
        }
        delete temp;                //deletes old head node
    }

    void removeWaypointAtEnd(){
        if (head == nullptr) { // checks if list is empty
            cout<<"The list is empty"<<endl;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != tail)  //runs until temp is the second to last node (one node before tail)
            temp = temp->next;      //moves forward one node at a time
        delete temp;                //deletes the last node
        tail = temp;                //updates tail to second to last node since old tail is deleted
        tail->next = nullptr;       //new last node... tail points to nullptr
        }

    void removeWaypointAtIndex(int index);

    void traverseForward() {
        Node<T>* current = head;

        while (current != nullptr) {
            cout<< current->data << " ";
            current = current->next;
        }
        cout<<endl;
    }

    void traverseBackward() {
        Node<T>* current = tail;

        while (current != nullptr) {
            cout<< current->data << " ";
            current = current->prev;
        }
        cout<<endl;
    }

    Node<T>* getWaypoint(int index);
    void setWaypoint(int index, T& data);

    void print(){

            Node<T>* current = head;
            while (current) {
                current->print();
                current = current->next;
            }
            cout << endl;
        }

};

