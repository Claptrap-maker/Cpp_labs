#include <iostream>
#include <ctime>
#include <utility>

enum direction{
    clockwise,
    counterclockwise
};

class InvalidStepException
{
public:
    InvalidStepException(std::string message): message{std::move(message)}{}
    std::string getMessage() const {return message;}
private:
    std::string message;
};

template <typename T>
struct Node{
    T info;
    Node *next, *prev;
};

template<typename T>
class DoublyLinkedCircularList{
private:
    int size;
    Node<T> *head, *rear;
public:
    DoublyLinkedCircularList();

    int GetSize();

    Node<T> *GetHead();

    Node<T> *GetRear();

    Node<T>* GetNode(int index);

    void PushBack(T info);

    void PushFront(T info);

    void Insert(int index);

    void Remove(int index);

    void RemoveNode(Node<T>* node);

    void RemoveAll();

    void PrintList();

    void PrintNode(int index);

    DoublyLinkedCircularList<T>& operator = (const DoublyLinkedCircularList<T> &l);

    DoublyLinkedCircularList<T> operator + (const DoublyLinkedCircularList<T>&);

    bool operator == (const DoublyLinkedCircularList<T>&);

    bool operator != (const DoublyLinkedCircularList<T>&);

    DoublyLinkedCircularList<T> operator - ();

    DoublyLinkedCircularList<T>& operator = (DoublyLinkedCircularList<T>&&l) = default;

    DoublyLinkedCircularList(const DoublyLinkedCircularList<T>&l);

    DoublyLinkedCircularList(DoublyLinkedCircularList<T>&& l) = default;

    ~DoublyLinkedCircularList();
};

template<typename T>
DoublyLinkedCircularList<T>::DoublyLinkedCircularList() {
    head = nullptr;
    rear = nullptr;
    size = 0;
}

template<typename T>
Node<T> *DoublyLinkedCircularList<T>::GetHead() {
    return head;
}

template<typename T>
Node<T> *DoublyLinkedCircularList<T>::GetRear() {
    return rear;
}

template<typename T>
int DoublyLinkedCircularList<T>::GetSize() {
    return size;
}

template<typename T>
DoublyLinkedCircularList<T>::DoublyLinkedCircularList(const DoublyLinkedCircularList<T> &l) {
    head = nullptr;
    rear = nullptr;
    size = 0;
    Node<T> *temp = l.head;
    do{
        PushBack(temp->info);
        temp = temp->next;
    }
    while(temp != l.head);
}

template<typename T>
void DoublyLinkedCircularList<T>::PushFront(T info) {
    auto *tempNode = new Node<T>;
    if (size == 0){
        tempNode->next = tempNode;
        tempNode->prev = tempNode;
        head = rear = tempNode;
    }
    tempNode->prev = rear;
    tempNode->info = info;
    tempNode->next = head;
    rear->next = tempNode;
    if (head != nullptr){
        head->prev = tempNode;
    }
    if (size != 0 ) {
        head = tempNode;
    }
    size++;
}

template<typename T>
void DoublyLinkedCircularList<T>::PushBack(T info) {
    auto *tempNode = new Node<T>;
    if (size == 0){
        tempNode->next = tempNode;
        tempNode->prev = tempNode;
        head = rear = tempNode;
    }
    tempNode->next = head;
    tempNode->info = info;
    tempNode->prev = rear;
    head->prev = tempNode;
    if (rear != nullptr){
        rear->next = tempNode;
    }
    if (size != 0) {
        rear = tempNode;
    }
    size++;
}

template<typename T>
void DoublyLinkedCircularList<T>::Insert(int index) {
    if (index < 0 || index > size - 1){
        std::cout << "Incorrect position" << std::endl;
        return;
    }
    if (index == size - 1){
        T data;
        std::cout << "Input new info: ";
        std::cin>>data;
        PushBack(data);
        return;
    } else if (index == 0){
        T data;
        std::cout << "Input new info: ";
        std::cin>>data;
        PushFront(data);
        return;
    }
    int i = 0;
    Node<T> *Ins = head;
    while(i < index){
        Ins = Ins->next;
        i++;
    }
    Node<T> *prevIns = Ins->prev;
    auto *temp = new Node<T>;
    std::cout<<"Input new info: ";
    std::cin>>temp->info;
    if (prevIns != nullptr && size != 1){
        prevIns->next = temp;
    }
    temp->next = Ins;
    temp->prev = prevIns;
    Ins->prev = temp;
    size++;
}

template<typename T>
void DoublyLinkedCircularList<T>::RemoveNode(Node<T> *node) {
    Node<T> *next, *prev;
    prev = node->prev;
    next = node->next;
    if (prev != nullptr && size != 1) {
        prev->next = node->next;
    }
    if (next != nullptr && size != 1) {
        next->prev = node->prev;
    }
    if (head == node) {
        head = next;
    }
    if (rear == node) {
        rear = prev;
    }
    delete node;
    size--;
}

template<typename T>
void DoublyLinkedCircularList<T>::Remove(int index) {
    if(index < 0 || index > size - 1)
    {
        std::cout << "Incorrect index \n";
        return;
    }
    int i = 0;
    Node<T> *delNode = head;
    while(i < index){
        delNode = delNode->next;
        i++;
    }
    Node<T> *prevDel = delNode->prev;
    Node<T> *nextDel = delNode->next;
    if (prevDel != nullptr && size != 1){
        prevDel->next = nextDel;
    }
    if (nextDel != nullptr && size != 1){
        nextDel->prev = prevDel;
    }
    if (index == 0){
        head = nextDel;
    }
    if (index == size - 1){
        rear = prevDel;
    }
    delete delNode;
    size--;
}

template<typename T>
void DoublyLinkedCircularList<T>::PrintNode(int index) {
    if(index < 0 || index > size - 1){
        std::cout << "Incorrect index \n";
        return;
    }
    Node<T> *tempNode;
    if (index <= size / 2){
        tempNode = head;
        int i = 0;

        while (i < index){
            tempNode = tempNode->next;
            i++;
        }
    } else {
        tempNode = rear;
        int i = 1;
        while (i <= size - 1 - index){
            tempNode = tempNode->prev;
            i++;
        }
    }
    std::cout << index << "Node's info: " << tempNode->info << std::endl;
}

template<typename T>
void DoublyLinkedCircularList<T>::PrintList() {
    if (size != 0){
        Node<T> *temp = head;
        std::cout<<"( ";
        while(temp->next != head){
            std::cout << temp->info << ", ";
            temp = temp->next;
        }
        std:: cout << temp->info << " )\n";
    }
}

template<typename T>
void DoublyLinkedCircularList<T>::RemoveAll() {
    while(size != 0){
        Remove(0);
    }
}

template<typename T>
Node<T> *DoublyLinkedCircularList<T>::GetNode(int index) {
    Node<T> *tempNode = head;
    if (index < 0 || index > size - 1){
        std::cout << "Incorrect index" << std::endl;
        return nullptr;
    }
    int i = 0;
    while(i < index && tempNode != nullptr){
        tempNode = tempNode->next;
        i++;
    }
    if (tempNode == nullptr){
        return nullptr;
    } else {
        return tempNode;
    }
}

template<typename T>
DoublyLinkedCircularList<T> &DoublyLinkedCircularList<T>::operator = (const DoublyLinkedCircularList<T> & l) {
    if (this == &l){
        return *this;
    }
    this->~DoublyLinkedCircularList<T>();
    Node<T> *tempNode = l.head;
    do{
        PushBack(tempNode->info);
        tempNode = tempNode->next;
    }
    while(tempNode != l.head);
    return *this;
}

template<typename T>
DoublyLinkedCircularList<T> DoublyLinkedCircularList<T>::operator+(const DoublyLinkedCircularList<T> &l) {
    DoublyLinkedCircularList<T> result(*this);
    Node<T> *tempNode = l.head;
    do {
        result.PushBack(tempNode->info);
        tempNode = tempNode->next;
    }
    while(tempNode != l.head);
    return result;
}

template<typename T>
bool DoublyLinkedCircularList<T>::operator==(const DoublyLinkedCircularList<T> & l) {
    if (size != l.size){
        return false;
    }
    Node<T> *p1, *p2;
    p1 = head;
    p2 = l.head;
    do{
        if (p1->info != p2->info){
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    while(p1 != head);
    return true;
}

template<typename T>
bool DoublyLinkedCircularList<T>::operator!=(const DoublyLinkedCircularList<T> & l) {
    return *this != l;
}

template<typename T>
DoublyLinkedCircularList<T> DoublyLinkedCircularList<T>::operator-() {
    DoublyLinkedCircularList<T> result;
    Node<T> *temp = head;
    do{
        result.PushFront(temp->info);
        temp = temp->next;
    }
    while(temp != head);
    return result;
}

template<typename T>
DoublyLinkedCircularList<T>::~DoublyLinkedCircularList<T>() {
    RemoveAll();
}

//solving Josephus problem
template<typename T>
std::pair<int, T> FlaviAlgorithm(DoublyLinkedCircularList<T> cll, direction dir, unsigned step) {
    if (step == 0){
        throw InvalidStepException("Step is equal 0");
    }
    if (step == 1) {
        return dir == clockwise ?
               std::make_pair(cll.GetSize() - 1, cll.GetNode(cll.GetSize() - 1)->info) :
               std::make_pair(0, cll.GetNode(0)->info);
    }
    auto posList = new DoublyLinkedCircularList<int>;
    for (int i = 0; i < cll.GetSize(); i++){
        posList->PushBack(i);
    }
    Node<T> *front, *back, *posPointer, *posPointerBack;
    front = dir == clockwise ? cll.GetHead() : cll.GetRear();
    back = dir == clockwise ? cll.GetHead() : cll.GetRear();
    posPointer = dir == clockwise ? posList->GetHead() : posList->GetRear();
    posPointerBack = dir == clockwise ? posList->GetHead() : posList->GetRear();
    while (cll.GetSize() > 1) {
        for (int i = 1; i < step; i++) {
            back = front;
            front = dir == clockwise ? front->next : front->prev;
            posPointerBack = posPointer;
            posPointer = dir == clockwise ? posPointer->next : posPointer->prev;
        }
        cll.RemoveNode(front);
        posList->RemoveNode(posPointer);
        front = dir == clockwise ? back->next : back->prev;
        posPointer = dir == clockwise ? posPointerBack->next : posPointerBack->prev;
    }
    int pos = posPointer->info;
    posList->RemoveAll();
    return std::make_pair(pos, front->info);
}

void CheckWork(){
    DoublyLinkedCircularList<int> list;
    const int size = 10;
    int numbers[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < size; i++)
        if(i % 2 == 0)
            list.PushFront(numbers[i]);
        else
            list.PushBack(numbers[i]);
    std::cout << "List:\n";
    std::cout << "Size of numbers: " << list.GetSize() << std::endl;
    list.PrintList();
    std::cout << std::endl;
    int index;
    std::cout << "Input index: ";
    std::cin >> index;
    list.Insert(index);
    std::cout << "List:\n";
    std::cout << "Size of numbers: " << list.GetSize() << std::endl;
    list.PrintList();
    list.PrintNode(2);
    list.PrintNode(8);
    DoublyLinkedCircularList<int> otherList;
    otherList = list;
    std::cout << "Another List:\n";
    std::cout << "Size of list: " << list.GetSize() << std::endl;
    otherList.PrintList();
    std::cout << "Concat lists:\n";
    DoublyLinkedCircularList<int> sumList = -list + otherList;
    std::cout << "Size of concat lists: " << sumList.GetSize() << std::endl;
    sumList.PrintList();
    std::cout << "Delete info"<<std::endl;
    std::cout << "Input index: ";
    std::cin >> index;
    sumList.Remove(index);
    std::cout << "List after deleting info with index = " << index << std::endl;
    std::cout << "New size is: " << sumList.GetSize() << std::endl;
    sumList.PrintList();
}

int main(){
    srand(time(NULL));
    unsigned size, step;
    std::cout<<"Enter size of list: ";
    std::cin>>size;
    std::cout<<"Enter step value: ";
    std::cin>>step;
    auto dlcl = new DoublyLinkedCircularList<int>;
    for (int i = 0; i < size; i++){
        dlcl->PushBack(rand() % 10);
    }
    std::cout<<"List: "<<std::endl;
    dlcl->PrintList();
    try {
        auto pairClockWise = FlaviAlgorithm(*dlcl, clockwise, step);
        std::cout << "Flavi index clockwise: (" << pairClockWise.first << ", " << pairClockWise.second << ")"
                  << std::endl;
        auto pairCounterClockWise = FlaviAlgorithm(*dlcl, counterclockwise, step);
        std::cout << "Flavi index counter clockwise: (" << pairCounterClockWise.first << ", "
                  << pairCounterClockWise.second << ")" << std::endl;
    } catch (const InvalidStepException &ise) {
        std::cout << ise.getMessage() << std::endl;
    }
    //CheckWork();
    return 0;
}