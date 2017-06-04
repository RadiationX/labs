//
// Created by radiationx on 31.05.17.
//

#ifndef COURSE_WORK_ELEMENTSLIST_H
#define COURSE_WORK_ELEMENTSLIST_H

#include "iostream"
#include "../LinkedList.h"

using namespace std;

template<class T>
class ElementsList {
private:
    //T **array = new T *[0];
    //int count = 0;
    //int countMax = 0;
    LinkedList<T*> linkedList;
public:
    ElementsList() {

    }

    void push_back(T *item) {
        add(item);
    }

    void add(T *item) {
        linkedList.addTail(item);
        /*count++;
        if (count > countMax) {
            T **newArray = new T*[count];
            std::copy(array, array + std::min(count - 1, count), newArray);
            delete[] array;
            array = newArray;
        }
        array[count - 1] = item;
        countMax++;*/
    }

    int size() {
        return linkedList.length();
    }

    T *back() {
        return linkedList.get(linkedList.length() - 1);
    }

    T *get(int index) {
        return linkedList.get(index);
    }

    T *at(int index) {
        return get(index);
    }

    /*Element[]

    toArray() {
        return Arrays.copyOf(array, count);
    }*/


    int begin() {
        return 0;
    }

    void remove(int index) {
        linkedList.remove(index);
        //array[index] = NULL;
        //count--;
    }
};

#endif //COURSE_WORK_ELEMENTSLIST_H