//
// Created by radiationx on 07.02.17.
//

#ifndef TECH_PROG_LAB_1_2_MERGESORT_H
#define TECH_PROG_LAB_1_2_MERGESORT_H

#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
class BaseItem {
private:
    T data;
    bool nullItem = true;
public:
    BaseItem() {}

    bool isNull() {
        return nullItem;
    }

    void setData(T data) {
        this->data = data;
        nullItem = false;
    }

    T getData() {
        return this->data;
    }
};

template<class E>
class BaseSortListener {
public:
    BaseSortListener() {}

    ~BaseSortListener() {}

    virtual bool onMergeCompare(E &el1, E &el2) = 0;

    virtual void onChangeArray(const std::string &title, E *mainArray, int size) = 0;

    virtual void onChangeTapeArray(const std::string &title, E **tapeArray, int cols, int rows) = 0;

    virtual void onSortTape(E *tape, int size) = 0;
};

template<class E>
class MergeSort {
private:
    BaseSortListener<E> *listener;
    bool initialized = false;

public:
    MergeSort(BaseSortListener<E> *listener) {
        this->listener = listener;
        initialized = true;
    }

    E *sort(E *mainArray, int mainSize) {
        if (!initialized) {
            cout << "Error: Need initialize listener" << endl;
            return mainArray;
        }
        listener->onChangeArray(string("Input data:"), mainArray, mainSize);

        //---- Calc tape size ----//
        double sqrtMainSize = sqrt(mainSize);
        int tapeSize = (int) (sqrtMainSize - floor(sqrtMainSize) == 0 ? sqrtMainSize : sqrtMainSize + 1);

        E **tapeArray = new E *[tapeSize];
        for (int i = 0; i < tapeSize; i++)
            tapeArray[i] = new E[tapeSize];

        //---- Transform to tapes ----//
        for (int i = 0, m = 0; i < tapeSize; i++) {
            for (int j = 0; j < tapeSize; j++, m++) {
                if (m >= mainSize) break;
                tapeArray[j][i] = mainArray[m];
            }
        }
        listener->onChangeTapeArray(string("Transformed to tapes:"), tapeArray, tapeSize, tapeSize);

        //---- Sorting ----//
        for (int i = 0; i < tapeSize; ++i)
            listener->onSortTape(tapeArray[i], tapeSize);
        listener->onChangeTapeArray(string("Sorted tapes:"), tapeArray, tapeSize, tapeSize);

        //---- Merge tapes----//
        delete[](mainArray);
        mainArray = new E[mainSize];

        int *offsets = new int[tapeSize];
        for (int i = 0; i < tapeSize; offsets[i] = 0, i++);

        int minOffset = 0;
        for (int i = 0; i < mainSize; i++) {
            int offset = minOffset;
            for (int j = 0; j < tapeSize; j++) {
                if (offsets[j] >= tapeSize)
                    continue;
                if (offsets[offset] >= tapeSize)
                    offset = j;
                if (listener->onMergeCompare(tapeArray[offset][offsets[offset]], tapeArray[j][offsets[j]]))
                    offset = j;
            }

            if (tapeArray[offset][offsets[offset]].isNull())
                i--;
            else
                mainArray[i] = tapeArray[offset][offsets[offset]];

            offsets[offset]++;
            if (offsets[minOffset] >= tapeSize) minOffset++;
        }
        listener->onChangeArray(string("Merged tapes:"), mainArray, mainSize);

        for (int i = 0; i < tapeSize; i++) {
            delete[](tapeArray[i]);
        }
        delete[](tapeArray);

        return mainArray;
    }
};


#endif //TECH_PROG_LAB_1_2_MERGESORT_H