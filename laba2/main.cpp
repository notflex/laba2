#include <iostream>

//Динамический массив

template <class T>
class DynamicArray{
private:
    T* memory_data;
    int memory_size;
    int memory_capacity;
public:
    DynamicArray(){
        memory_data = NULL;
        memory_size = 0;
        memory_capacity = 0;
    }


    void Delete(){
        delete[] this->memory_data;
    }
    DynamicArray(int size){
        memory_size = size;
        memory_capacity = size;
        memory_data = new T[size];
    }

    DynamicArray(T* items,int count){
        if(items == nullptr){
            memory_data = nullptr;
            memory_size = 0;
            memory_capacity = 0;
        }
        else{
            memory_size = count;
            memory_capacity = count;
            memory_data = new T[count];
            for (int i = 0; i < count; ++i)
            {
                memory_data[i] = items[i];
            }
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray){
        if(&dynamicArray == nullptr){
            memory_data = nullptr;
            memory_size = 0;
            memory_capacity = 0;
        }
        else{
            memory_size = dynamicArray.memory_size;
            memory_capacity = memory_size;
            memory_data = new T[memory_size];
            for (int i = 0; i < dynamicArray.memory_size; ++i)
            {
                memory_data[i] = dynamicArray.memory_data[i];
            }
        }
    }


    void Resize(int newSize){
        if(newSize > memory_capacity){
            int new_capacity = std::max(2 * memory_size, newSize);
            T* new_data = new T[new_capacity];
            for (int i = 0; i < memory_size; ++i)
            {
                new_data[i] = memory_data[i];
            }
            delete[] memory_data;
            memory_data = new_data;
            memory_capacity = new_capacity;
        }
        memory_size = newSize;
    }

    T Get(int index){
        if(index < 0 || index >= memory_capacity)
            throw "\nGet Message : Index Out Of Range\n";
        //std::cout << "\nGet index = " << index << "\n";
        return memory_data[index];
    }

    void Set(int index,T value){
        if(index < 0 || index > memory_capacity)
            throw "\nSet Message : Index Out Of Range\n";
        //std::cout << "\nSet data = " << value << " index = "<< index <<"\n";
        memory_data[index] = value;

    }

    int GetSize() const{
        return memory_size;
    }

    void Append(T val){
        std::cout << "\nAppend data = " << val;
        Resize(memory_size + 1);
        memory_data[memory_size - 1] = val;
    }

    void Prepend(T val){
        std::cout << "\nPrepend data = " << val << "\n";
        Resize(memory_size + 1);
        for (int i = memory_size - 2; i >= 0; --i)
        {
            memory_data[i + 1] = memory_data[i];
        }
        memory_data[0] = val;
    }

    T & operator [] (int i){
        return memory_data[i];
    }

    void Print(){
        if(memory_size > 0 && memory_data != nullptr){
            std::cout << std::endl;
            for (int i = 0; i < memory_size; ++i) {
                std::cout << memory_data[i] << "\t";
            }
            std::cout << std::endl;
        }
        else{
            std::cout << "\nObject is empty!\n";
        }
    }
};

template <typename T>
std::ostream & operator << (std::ostream & out, DynamicArray<T> a){
    for(int i = 0; i < a.GetSize();++i){
        out << a[i] << " ";
    }
    return out;
}



// Linked list

template<typename T>
class Node{
public:
    Node* pNext;
    Node* pPrev;
    T data;
    Node(T data = T(),Node* pPrev = nullptr,Node* pNext = nullptr){
        this->data = data;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }
};


template<typename T>
class LinkedList{
public:
    LinkedList();
    LinkedList(T* items,int count);
    LinkedList(const LinkedList<T>& LinkedList );
    ~LinkedList();

    int GetLength(){return Size;}
    T GetFirst();
    T GetLast();
    T Get(int index);

    LinkedList<T>* GetSubLinkedList(int startIndex,int endIndex);
    LinkedList<T>* Concat(LinkedList<T>* LinkedList);

    void Append(T data);
    void Prepend(T data);

    void pop_front();
    void pop_back();

    void print_from_end();
    void print_from_begin();

    void InsertAt(T data,int index);
    void removeAt(int index);

    void clear();
    T& operator[] (const int index);

private:
    int Size;
    Node<T>* head;
    Node<T>* tail;
};

template<typename T>
LinkedList<T> :: ~LinkedList(){
    clear();
}

template<typename T>
LinkedList<T> :: LinkedList(){
    Size = 0;
    head = nullptr;
}

template<typename T>
LinkedList<T> :: LinkedList(T* items,int count){
    if(items == nullptr){
        Size = 0;
        head = nullptr;
    }
    else{
        Size = 0;
        this->head = nullptr;
        this->tail = nullptr;
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }
}

template<typename T>
LinkedList<T> :: LinkedList(const LinkedList<T>& list){
    Size = 0;
    this->head = nullptr;
    Node<T>* current = list.head;
    for (int i = 0; i < list.Size; ++i) {
        this->Append(current->data);
        current = current->pNext;
    }
    //std::cout << "CopyConstructor done . . .\n";
}

template<typename T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list){
    this->tail->pNext = list->head;
    list->head->pPrev = this->tail;
    this->tail = list->tail;
    Size+=list->Size;

    return this;
}

template<typename T>
T LinkedList<T> ::Get(int index){
    if(index < 0 || index >= Size)
        throw "\nGet Message : Index Out Of Range\n";

    Node<T>* current;

    if(index < Size/2){
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->pNext;
        }
    }else{
        current = tail;
        for (int i = 0; i < Size-index-1; ++i) {
            current = current->pPrev;
        }
    }
    return current->data;

}

template<typename T>
T LinkedList<T> ::GetFirst() {
    if(Size == 0)
        throw "\nGetFirst Message : Index Out Of Range\n";
    std::cout<<"\nGetFirst:\n";
    return Get(0);
}

template<typename T>
T LinkedList<T> ::GetLast(){
    if(Size == 0)
        throw "\nGetLast Message : Index Out Of Range\n";
    std::cout<<"\nGetLast:\n";
    return Get(Size - 1);
}

template<typename T>
LinkedList<T>* LinkedList<T>::GetSubLinkedList(int startIndex,int endIndex){
    if(startIndex < 0 || endIndex < 0 || startIndex >= Size || endIndex >=Size)
        throw "\nGetSubLinkedList Message : Index Out Of Range\n";
    std::cout<<"\nGetSubLinkedList\n";
    Node<T>* current = this->head;
    for (int i = 0; i <=startIndex; ++i) {
        current = current->pNext;
    }
    T* items;
    items = (T*)malloc(sizeof(T*)*(endIndex-startIndex));
    for (int i = 0; i < endIndex-startIndex; ++i) {
        items[i] = current->data;
        current = current->pNext;
    }

    LinkedList<T>* result = new LinkedList<T>(items,endIndex-startIndex);
    return result;

}

template<typename T>
void LinkedList<T> ::print_from_end(){
    std::cout << std::endl;
    Node<T>* tmp = this->tail;
    if(Size == 1)
        std::cout << tail->data << " ";
    else{
        while(tmp != nullptr){
            std::cout << tmp->data <<" ";
            tmp = tmp->pPrev;
        }
    }
}

template<typename T>
void LinkedList<T> ::print_from_begin(){
    if(head != nullptr){
        std::cout << std::endl;
        Node<T>* tmp = this->head;
        if(Size == 1)
            std::cout << head->data << " ";
        else{
            while(tmp != nullptr){
                std::cout << tmp->data <<" ";//std::endl;
                tmp = tmp->pNext;
            }
        }
    }
}


template<typename T>
void LinkedList<T> :: Append(T data){
    if(head == nullptr){
        head = new Node<T>(data);
        this->tail = head;

    }else{
        Node<T>* current = this->head;
        Node<T>* tmp;
        while(current->pNext != nullptr){
            tmp = current;
            current = current->pNext;
            current->pPrev = tmp;
        }

        this->tail = new Node<T>(data,current,current->pNext);
        current->pNext = tail;
    }
    Size++;
}

template<typename T>
void LinkedList<T> ::Prepend(T data) {
    if(head == nullptr){
        head = new Node<T>(data);
        this->tail = head;
    }
    else{
        Node<T>* one_more = new Node<T>(data,head->pPrev,head);
        head->pPrev = one_more;
        this->head = one_more;
        Node<T>* current = head;
        while(current->pNext != nullptr){
            current = current->pNext;
        }
        this->tail = current;
    }
    Size++;
}

template<typename T>
void LinkedList<T> ::pop_front() {
    if(Size == 1){
        delete [] tail;
        Size--;
    }
    else{
        Node<T>* tmp = head;
        head = head->pNext;
        head->pPrev = nullptr;
        delete [] tmp;
        Size--;
    }

}

template<typename T>
void LinkedList<T> ::pop_back(){
    Node<T>* tmp = tail;
    tail = tail->pPrev;
    tail->pNext = nullptr;
    delete [] tmp;
    Size--;
}

template<typename T>
void LinkedList<T> ::InsertAt(T data, int index) {
    if(index < 0 || index >= Size)
        throw "\nInsertAt Message : Index Out Of Range\n";
    Node<T>* previous;
    Node<T>* new_elem;
    Node<T>* tmp;
    std::cout << "\nInsertAt data = " << data << " index = " << index << "\n";
    if(index <= Size/2){
        if(index == 0)
            Prepend(data);
        previous = head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
    }
    else{

        previous = tail;
        for (int i = 0; i < Size - index; ++i) {
            previous = previous->pPrev;
        }
    }
    tmp = previous->pNext;
    new_elem = new Node<T>(data,previous,previous->pNext);
    previous->pNext = new_elem;
    tmp->pPrev = new_elem;

    Size++;
}

template<typename T>
void LinkedList<T>::removeAt(int index) {
    if(index < 0 || index >= Size)
        throw "removeAt Message : Index Out Of Range\n";
    std::cout << "\nremoveAt index = " << index << "\n";
    if(index == 0)
        pop_front();
    else{
        if(index == Size - 1)
            pop_back();
        else{
            Node<T>* previous;
            Node<T>* toDelete;
            if(index <= Size/2){
                previous = head;
                for (int i = 0; i < index - 1; ++i) {
                    previous = previous->pNext;
                }
            }
            else{
                previous = tail;
                for (int i = 0; i < Size - index; ++i) {
                    previous = previous->pPrev;
                }
            }

            toDelete = previous->pNext;
            previous->pNext = toDelete->pNext;
            toDelete->pNext->pPrev = previous;

            delete[] toDelete;
        }
        Size--;
    }
}

template<typename T>
void LinkedList<T> ::clear(){
    while(Size){
        pop_front();
    }
}

template<typename T>
T& LinkedList<T> :: operator[](const int index){
    int counter;
    Node<T>* current;
    if(index <= Size/2){
        counter = 0;
        current = this->head;
        while(current != nullptr){
            if(counter == index){
                return current->data;
            }
            current = current->pNext;
            counter++;
        }
    }
    else{
        counter = Size - 1;
        current = this->tail;
        while(current != nullptr){
            if(counter == index){
                return current->data;
            }
            current = current->pPrev;
            counter--;
        }
    }
}




// sequence



template<typename T>
class Sequence{
public:
    virtual Sequence<T>* GetSubsequence(int startIndex,int endIndex) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item,int index) = 0;

    virtual void Print() = 0;
};

template<typename T>
class ArraySequence : public Sequence<T>{
public:
    ArraySequence(){
        DynamicArray<T>* tmp = new DynamicArray<T>();
        data = *tmp;
    }

    ArraySequence(T* item,int count){

        DynamicArray<T>* tmp = new DynamicArray<T>(item,count);
        data = *tmp;

    }

    ArraySequence(ArraySequence<T>& array){

        DynamicArray<T>* tmp = new DynamicArray<T>(array.data);
        data = *tmp;
    }

    ArraySequence(LinkedList<T>& list){
        T* items;
        items = (T*)malloc(sizeof(T)*(list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }

        DynamicArray<T>* tmp = new DynamicArray<T>(items,list.GetLength());
        data = *tmp;
    }
    int GetLength(){
        return data.GetSize();
    }
    T Get(int index){
        return data.Get(index);
    }
    T GetFirst(){
        return data.Get(0);
    }
    T GetLast(){
        return data.Get(data.GetSize()-1);
    }

    void Append(T item){
        data.Append(item);
    }
    void Prepend(T item){
        data.Prepend(item);
    }
    void InsertAt(T item,int index){
        if(index >= data.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        data.Resize(data.GetSize()+1);
        for (int i = data.GetSize()-2; i >= index ; --i) {
            data.Set(i+1,data.Get(i));
        }
        data.Set(index,item);
    }
    void Print(){
        data.Print();
    }

    ArraySequence<T>* GetSubsequence(int startIndex,int endIndex){
        T* items = (T*)malloc(sizeof(T)*(endIndex-startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i-startIndex] = data.Get(i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(items,endIndex-startIndex);
        return result;
    }

    ArraySequence<T>* Concat(Sequence<T>* list){
        if(list->GetLength() != 0){
            T* items = (T*)malloc(sizeof(T)*(data.GetSize()+list->GetLength()));
            for (int i = 0; i < data.GetSize(); ++i) {
                items[i] = data.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i+data.GetSize()] = list->Get(i);
            }
            ArraySequence<T>* result = new ArraySequence<T>(items,data.GetSize()+list->GetLength());

            return result;
        }else{
            ArraySequence<T>* result = new ArraySequence<T>(*this);
            return result;
        }

    }
private:
    DynamicArray<T> data;
};

template<typename T>
class LinkedListSequence : public Sequence<T>{
public:
    LinkedListSequence(){
        LinkedList<T>* tmp = new LinkedList<T>();
        data = *tmp;
    }
    LinkedListSequence(T* items,int count){
        LinkedList<T>* tmp = new LinkedList<T>(items,count);
        data = *tmp;

    }

    LinkedListSequence<T>* Concat(Sequence<T>* list){
        for (int i = 0; i < list->GetLength(); ++i) {
            data.Append(list->Get(i));
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(data.GetLength()+list->GetLength()));
        for (int i = 0; i < data.GetLength(); ++i) {
            items[i] = data.Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,data.GetLength());
        return result;
    }

    LinkedListSequence(const LinkedList<T>& list){
        LinkedList<T>* tmp = new LinkedList<T>(list);
        std::cout<< "Constructor by object . . .\n";
        data = *tmp;
    }
    LinkedListSequence<T>* GetSubsequence(int startIndex,int endIndex){
        LinkedList<T>* tmp = data.GetSubLinkedList(startIndex,endIndex);
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex-startIndex));
        for (int i = 0; i < endIndex-startIndex; ++i) {
            items[i] = tmp->Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,endIndex-startIndex);

        return result;
    }
    int GetLength(){
        return data.GetLength();
    }
    T GetFirst(){
        data.GetFirst();
    }
    T GetLast(){
        data.GetLast();
    }
    T Get(int index){
        data.Get(index);
    }

    void Append(T item){
        data.Append(item);
    }
    void Prepend(T item){
        data.Prepend(item);
    }
    void InsertAt(T item,int index){
        data.InsertAt(item,index);
    }
    void removeAt(int index){
        data.removeAt(index);
    }
    void Print(){
        data.print_from_begin();
    }
private:
    LinkedList<T> data;
};

// squarematrix



template<typename T>
class SquareMatrix{
private:
    DynamicArray<DynamicArray<T>> data;
    int m;
public:
    int isFailed = 0;
    SquareMatrix();

    ~SquareMatrix(){
        for (int i = 0; i < m; ++i) {
            data[i].Delete();
        }
        std::cout << "\nDestructor call . . ." << this << std::endl;
    }

    SquareMatrix(int m,T** items)
    {
        this->m = m;
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data[i].Resize(m);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                data[i].Set(j,items[i][j]);
            }
        }
        std::cout << "Constructor by array done for " << this << std::endl;
    }


    SquareMatrix(int m){
        this->m = m;
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data[i].Resize(m);
        }
        T value;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if((std::cin >> value)){
                    data[i].Set(j,value);
                }else{
                    std::cout << "Incorrect input";
                    isFailed = 1;
                    return;
                }
            }
        }
        std::cout << "Constructor done for " <<this<<std::endl;
    }

    int getM(){return m;}
    T Get(int i,int j){return data[i].Get(j);}


    void Transposition(){
        DynamicArray<DynamicArray<T>> tmp;
        tmp.Resize(m);
        for (int i = 0; i < m; ++i) {
            tmp[i].Resize(m);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                tmp[i].Set(j,data[j].Get(i));
            }
        }

        this->data = tmp;
        this->m = m;
    }


    void swapStrings(int first,int second){
        if(first >= m || second >= m){
            isFailed = 1;
            std::cout << "Incorrect indexes for swap strings";
            return;
        }
        else{
            DynamicArray<T> tmp = data[first];
            data[first] = data[second];
            data[second] = tmp;
        }
    }


    void swapColumns(int first,int second){
        if(first >= m || second >= m){
            isFailed = 1;
            std::cout << "Incorrect indexes for swap columns";
            return;
        }else{
            this->Transposition();
            this->swapStrings(first,second);
            this->Transposition();
        }
    }

    void stringsScalarMultiplication(T k,int index){
        if(index >= m){
            isFailed = 1;
            std::cout << "Incorrect index for string scalar multiplication";
            return;
        }else{
            for (int i = 0; i < m; ++i) {
                data[index].Set(i,k*data[index].Get(i));
            }
        }
    }

    void columnsScalarMultiplication(T k,int index){
        if(index >= m){
            isFailed = 1;
            std::cout << "Incorrect index for columns scalar multiplication";
            return;
        }else{
            this->Transposition();
            this->stringsScalarMultiplication(k,index);
            this->Transposition();
        }
    }

    void additionoftwoStrings(int first,int second){
        if(first >= m || second >=m){
            isFailed = 1;
            std::cout << "Incorrect indexes for addition of two strings";
            return;
        }else{
            for (int i = 0; i < m; ++i) {
                data[first].Set(i,data[first].Get(i) + data[second].Get(i));
            }
        }
    }

    void additionoftwoColumns(int first,int second){
        if(first >= m || second >= m){
            isFailed = 1;
            std::cout << "Incorrect indexes for addition of two columns";
            return;
        }else{
            this->Transposition();
            this->additionoftwoStrings(first,second);
            this->Transposition();
        }
    }

    void matrixMultiplicationByNumber(T k){
        for (int i = 0; i < m; ++i) {
            stringsScalarMultiplication(k,i);
        }
    }

    SquareMatrix<T>* Sum(SquareMatrix<T>& first,SquareMatrix<T>& second){
        if(first.getM() != second.getM()){
            isFailed = 1;
            std::cout << "Can't sum";
            return nullptr;
        }else{

            T** tmp = (T**)malloc(sizeof(T*)*m);
            for (int i = 0; i < m; ++i) {
                tmp[i] = (T*)malloc(sizeof(T)*m);
            }

            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    tmp[i][j] = first.Get(i,j) + second.Get(i,j);
                }
            }
            SquareMatrix<T>* result = new SquareMatrix<T>(m,tmp);
            for (int i = 0; i < m; ++i) {
                delete[] tmp[i];
            }
            delete[] tmp;
            return result;
        }
    }

    SquareMatrix<T>* Multiply(SquareMatrix<T>& first,SquareMatrix<T>& second){
        if(first.getM() != second.getM()){
            isFailed = 1;
            std::cout << "Can't multiply";
            return nullptr;
        }else{
            int M = first.getM();
            int N = second.getM();
            int Q = first.getM();
            T** tmp = (T**)malloc(sizeof(T*)*M);
            for (int i = 0; i < M; ++i) {
                tmp[i] = (T*)malloc(sizeof(T)*N);
            }
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    tmp[i][j] = 0;
                    for (int k = 0; k < Q; ++k) {
                        tmp[i][j]+=first.Get(i,k)*second.Get(k,j);
                    }
                }
            }
            SquareMatrix<T>* result = new SquareMatrix<T>(M,tmp);
            for (int i = 0; i < M; ++i) {
                delete[] tmp[i];
            }
            delete[] tmp;
            return result;
        }
    }

    T MatrixNorm(){
        T max = 0;
        for (int i = 0; i < m; ++i) {
            max+=data[0].Get(i);
        }
        T tmp;
        for (int i = 0; i < m; ++i) {
            tmp = 0;
            for (int j = 0; j < m; ++j) {
                tmp+=data[i].Get(j);
            }
            if(tmp >= max)
                max = tmp;
        }
        return max;
    }

    void Print(){
        if(this != nullptr && isFailed == 0){
            std::cout<<std::endl;
            for (int i = 0; i < m; ++i) {
                data[i].Print();
                std::cout << std::endl;
            }
            std::cout<<std::endl;
        }else
            std::cout << "\nCan't print, invalid input" << std::endl;
    }
};


///////////////////////////////////////////////////////////////////////////



template<typename T>
class Matrix{
private:
    DynamicArray<DynamicArray<T>> data;
    int m;//количество строк
    int n;//количество столбцов

public:
    int isFailed = 0;
    Matrix();

    ~Matrix(){
        for (int i = 0; i < m; ++i) {
            data[i].Delete();
        }
    }

    Matrix(int m,int n,T** items)
    {
        this->m = m;
        this->n = n;
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data[i].Resize(n);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i].Set(j,items[i][j]);
            }
        }
    }

    Matrix(int m,int n){
        this->m = m;
        this->n = n;
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data[i].Resize(n);
        }
        T value;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if((std::cin >> value)){
                    data[i].Set(j,value);
                }else{
                    std::cout << "Incorrect input";
                    isFailed = 1;//контрольное значение ошибки изменяется в случае некорректного ввода
                    return;
                }
            }
        }
        std::cout << "Constructor done for " <<this<<std::endl;
    }

    int getM(){return m;}
    int getN(){return n;}
    T Get(int i,int j){return data[i].Get(j);}

    void Transposition(){
        DynamicArray<DynamicArray<T>> tmp;
        tmp.Resize(n);
        for (int i = 0; i < n; ++i) {
            tmp[i].Resize(m);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                tmp[i].Set(j,data[j].Get(i));
            }
        }

        this->data = tmp;
        int a = m;
        int b = n;
        this->m = b;
        this->n = a;
    }

    void swapStrings(int first,int second){
        if(first >= m || second >= m){
            isFailed = 1;
            std::cout << "Incorrect indexes for swap strings";
            return;
        }
        else{
            DynamicArray<T> tmp = data[first];
            data[first] = data[second];
            data[second] = tmp;

        }
    }

    void swapColumns(int first,int second){
        if(first >= n || second >= n){
            isFailed = 1;
            std::cout << "Incorrect indexes for swap columns";
            return;
        }else{
            this->Transposition();
            this->swapStrings(first,second);
            this->Transposition();
        }
    }

    void stringsScalarMultiplication(T k,int index){
        if(index >= m){
            isFailed = 1;
            std::cout << "Incorrect index for string scalar multiplication";
            return;
        }else{
            for (int i = 0; i < n; ++i) {
                data[index].Set(i,k*data[index].Get(i));
                //data[index][i] = k * data[index][i];
            }
        }
    }

    void columnsScalarMultiplication(T k,int index){
        if(index >= n){
            isFailed = 1;
            std::cout << "Incorrect index for columns scalar multiplication";
            return;
        }else{
            this->Transposition();
            this->stringsScalarMultiplication(k,index);
            this->Transposition();
        }
    }

    void additionoftwoStrings(int first,int second){
        if(first >= m || second >=m){
            isFailed = 1;
            std::cout << "Incorrect indexes for addition of two strings";
            return;
        }else{
            for (int i = 0; i < n; ++i) {
                data[first].Set(i,data[first].Get(i) + data[second].Get(i));
            }
        }
    }

    void additionoftwoColumns(int first,int second){
        if(first >= n || second >= n){
            isFailed = 1;
            std::cout << "Incorrect indexes for addition of two columns";
            return;
        }else{
            this->Transposition();
            this->additionoftwoStrings(first,second);
            this->Transposition();
        }
    }

    void matrixMultiplicationByNumber(T k){
        for (int i = 0; i < m; ++i) {
            stringsScalarMultiplication(k,i);
        }
    }

    Matrix<T>* Sum(Matrix<T>& first,Matrix<T>& second){
        if(first.getM() != second.getM() || first.getN() != second.getN()){
            isFailed = 1;
            std::cout << "Can't sum";
            return nullptr;
        }else{

            T** tmp = (T**)malloc(sizeof(T*)*m);
            for (int i = 0; i < m; ++i) {
                tmp[i] = (T*)malloc(sizeof(T)*n);
            }

            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    tmp[i][j] = first.Get(i,j) + second.Get(i,j);
                }
            }
            Matrix<T>* result = new Matrix<T>(m,n,tmp);
            for (int i = 0; i < m; ++i) {
                delete[] tmp[i];
            }
            delete[] tmp;
            return result;
        }
    }

    Matrix<T>* Multiply(Matrix<T>& first,Matrix<T>& second){
        if(first.getN() != second.getM()){
            isFailed = 1;
            std::cout << "Can't multiply";
            return nullptr;
        }else{
            int M = first.getM();
            int N = second.getN();
            int Q = first.getN();
            T** tmp = (T**)malloc(sizeof(T*)*M);
            for (int i = 0; i < M; ++i) {
                tmp[i] = (T*)malloc(sizeof(T)*N);
            }
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    tmp[i][j] = 0;
                    for (int k = 0; k < Q; ++k) {
                        tmp[i][j]+=first.Get(i,k)*second.Get(k,j);
                    }
                }
            }
            Matrix<T>* result = new Matrix<T>(M,N,tmp);
            for (int i = 0; i < M; ++i) {
                delete[] tmp[i];
            }
            delete[] tmp;
            return result;
        }
    }

    T MatrixNorm(){
        if(isFailed == 0){
            T max = 0;
            for (int i = 0; i < n; ++i) {
                max+=data[0].Get(i);
            }
            T tmp;
            for (int i = 0; i < m; ++i) {
                tmp = 0;
                for (int j = 0; j < n; ++j) {
                    tmp+=data[i].Get(j);
                }
                if(tmp >= max)
                    max = tmp;
            }
            return max;
        }

    }

    void Print(){
        if(this != nullptr && isFailed == 0){
            std::cout<<std::endl;
            for (int i = 0; i < m; ++i) {
                data[i].Print();
                std::cout << std::endl;
            }
            std::cout<<std::endl;
        }else
            std::cout << "\nCan't print, invalid input" << std::endl;
    }
};

void menu(){
    int choice = 0;
    while (choice != 5) {
        std::cout << "1.Sum\n" << "2.Mult on Scal\n" << "3.Norm\n" << "4.Elementary transform\n" << "5.Exit\n"
                  << "Choose on of options: ";
        std::cin >> choice;
        std::cout << std::endl;
        if (choice < 1 || choice > 5) {
            std::cout << "incorrect option. Choose another one.\n";
            continue;
        }
        int type;
        int n;

        switch (choice) {
            case 1: {
                int m;
                std::cout << "Enter size of first matrix :\n";
                std::cin >> m;
                SquareMatrix<int>* test1 = new SquareMatrix<int>(m);
                test1->Print();
                std::cout << "Enter size of second matrix :\n";
                std::cin >> m;
                SquareMatrix<int>* test2 = new SquareMatrix<int>(m);
                test2->Print();
                SquareMatrix<int>* sum = test1->Sum(*test1,*test2);
                sum->Print();

            }
            break;
            case 2:{
                int m;
                std::cout << "Enter size matrix :\n";
                std::cin >> m;
                SquareMatrix<int>* test = new SquareMatrix<int>(m);
                int scalar;
                std :: cout << "Enter scalar: \n";
                std :: cin >> scalar;
                std :: cout << "Result: \n";
                test->matrixMultiplicationByNumber(scalar);
                test->Print();
            }
            break;
            case 3:{
                int m;
                std::cout << "Enter size matrix :\n";
                std::cin >> m;
                SquareMatrix<int>* test = new SquareMatrix<int>(m);
                test->MatrixNorm();
                test->Print();
            }
            break;
            case 4:{
                std::cout << "1.Transposition\n2.addition of two coloumns\n3.addition of two strins\n4.swapstrings\n5.swapcoloumns\nInput type of transform: ";
                std::cin >> type;
                if (type != 1 && type != 2 && type != 3 && type != 4 && type != 5) {
                    std::cout << "Wrong choice of type! Try again.\n";
                    continue;
                }
                switch (type) {
                    case 1:{
                        int m;
                        std::cout << "Enter size matrix :\n";
                        std::cin >> m;
                        SquareMatrix<int>* test = new SquareMatrix<int>(m);
                        test->Transposition();
                        test->Print();
                    }
                    break;
                    case 2:{
                        int m, k, p;
                        std :: cout << "Enter size matrix :\n";
                        std :: cin >> m;
                        SquareMatrix<int>* test = new SquareMatrix<int>(m);
                        std :: cout << "Enter number of first coloumn: \n";
                        std :: cin >> k;
                        std :: cout << "Enter number of second coloumn: \n";
                        std :: cin >> p;
                        test->additionoftwoColumns(k, p);
                        test->Print();
                    }
                    break;
                    case 3:{
                        int m, k, p;
                        std :: cout << "Enter size matrix :\n";
                        std :: cin >> m;
                        SquareMatrix<int>* test = new SquareMatrix<int>(m);
                        std :: cout << "Enter number of first string: \n";
                        std :: cin >> k;
                        std :: cout << "Enter number of second second: \n";
                        std :: cin >> p;
                        test->additionoftwoStrings(k, p);
                        test->Print();
                    }
                    break;
                    case 4:{
                        int m, k, p;
                        std :: cout << "Enter size matrix :\n";
                        std :: cin >> m;
                        SquareMatrix<int>* test = new SquareMatrix<int>(m);
                        std :: cout << "Enter number of first string: \n";
                        std :: cin >> k;
                        std :: cout << "Enter number of second string: \n";
                        std :: cin >> p;
                        test->swapStrings(k, p);
                        test->Print();
                    }
                    break;
                    case 5:{
                        int m, k, p;
                        std :: cout << "Enter size matrix :\n";
                        std :: cin >> m;
                        SquareMatrix<int>* test = new SquareMatrix<int>(m);
                        std :: cout << "Enter number of first column: \n";
                        std :: cin >> k;
                        std :: cout << "Enter number of second column: \n";
                        std :: cin >> p;
                        test->swapColumns(k, p);
                        test->Print();
                    }
                    break;
                }
            }
            break;
            case 5: {
                std::cout << "Exit the program...\n";
                return;
            }
                break;
            default: {
                std::cout << "Wrong choice! Try again.\n";
            }
                break;
        }
        }
}



int main(){
    menu();
}