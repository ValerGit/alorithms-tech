#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stack>
#define STOP_REC 40


struct Dimension {
    BlackInt* start;
    BlackInt* end;
    Dimension(BlackInt* l, BlackInt* r) : start(l), end(r) {}
};

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
    end->swap(*i);
    return i;

}

void quickSort(BlackInt* begin, BlackInt* end) {

    std::stack<Dimension>* stack = new std::stack<Dimension>;
    stack->push(Dimension(begin,end));

    while(1) {
        if(stack->size() == 0) break;
        Dimension temp = stack->top();
        if( temp.start < temp.end && ((temp.end - temp.start)/ sizeof(Dimension) > STOP_REC)) {

            BlackInt* pivot = partition(temp.start, temp.end);
            stack->pop();
            stack->push( Dimension( temp.start, pivot - 1) );
            stack->push( Dimension( pivot + 1, temp.end) );

        } else stack->pop();
    }
    delete stack;
}


BlackInt* binSearch ( BlackInt* begin, BlackInt* end,  BlackInt* val ) {
    BlackInt* l = begin;
    BlackInt* r = end;
    while(l < r) {
        BlackInt* m = l + (r - l)/2 ;
        if( val->operator>(*m) ) l = m + 1;
        else r = m;
    }
    return r;
}


void insertion_sort ( BlackInt* begin, BlackInt* end )
{
    BlackInt* iter = begin + 1;

    while( iter < end ) {

        BlackInt* newPos = binSearch(begin, iter, iter);
        if( newPos < iter ) {
            BlackInt* ye = new BlackInt(*iter);
            BlackInt* n = iter+1;
            memmove( newPos + 1, newPos, (iter-newPos)* sizeof(BlackInt));
            newPos->operator=(*ye);
            iter = n;
            delete[] ye;
        }
        else ++iter;

    }
}

void sort(BlackInt *begin, BlackInt *end) {
    if(begin >= end) return;
    quickSort(begin, end-1);
    insertion_sort(begin, end);
}
