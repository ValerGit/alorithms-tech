#include <string.h>
#include <stdio.h>
#include <stack>
#include <cstdlib>
#include <iostream>

BlackInt* findPivot(BlackInt *begin, BlackInt *end) {
    BlackInt* pivot;
    BlackInt* mid  = begin + (end-begin)/2;
        if (begin->operator<(*mid)) {
            if (mid->operator<(*end)) pivot = mid;
            else {
                if (begin->operator<(*end)) pivot = end;
                else pivot = begin;
            }
        } else {
            if (end->operator<(*mid)) pivot = mid;
            else {
                if (begin->operator<(*end)) pivot = begin;
                else pivot = end;
            }
        }
    return pivot;
}


BlackInt* partition(BlackInt* begin, BlackInt* end) {

    if(begin == end) return begin;
    BlackInt* pivot = findPivot(begin, end);
    pivot->swap(*end);

    BlackInt* i = begin;
    BlackInt* j = begin;
    while(j < end) {
        if(j->operator>(*end)) ++j;
        else {
            i->swap(*j);
            ++i;
            ++j;
        }
    }
    //end->swap(*i);
    //std::swap(end, i);
    return i;

}


void quickSort(BlackInt *begin, BlackInt *end) {
    if (begin >= end) return;
    BlackInt *pivot = partition(begin, end);
    quickSort(begin, pivot - 1);
    quickSort(pivot + 1, end);
}


void sort(BlackInt *begin, BlackInt *end) {
    for (BlackInt *i = begin+1; i < end; ++i) {
        if(i->operator<(*(i - 1)))
        {
            quickSort(begin, end - 1);
            return;
        }
    }
}
