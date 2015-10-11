#include <iostream>

using namespace std;

int startBuff = 1000;
const int growFactor = 2;

struct Segment {
    Segment() : start(0), end(0) {}
    Segment(const Segment &obj) : start(obj.start), end(obj.end) {}

    int start;
    int end;
};

int partition(Segment*& segments, int left, int right) {
    int pivot = right - 1;
    int i = left, j = left;

    while(j < pivot) {
        if(segments[j].end > segments[pivot].end) ++j;

        else {
            Segment temp = segments[j];
            segments[j] = segments[i];
            segments[i] = temp;
            ++i; ++j;
        }
    }

    Segment temp = segments[pivot];
    segments[pivot] = segments[i];
    segments[i] = temp;

    return i;
}

void xoara(Segment*& segments, int left, int right) {
    if(left < right) {
        int q = partition(segments, left, right);
        xoara(segments, left, q);
        xoara(segments, q + 1, right);
    }
}

void grow(Segment*& segments) {
    startBuff *= growFactor;

    Segment* allSegments = new Segment[startBuff];

    for(int i = 0; i < startBuff/growFactor; ++i) {
        allSegments[i] = segments[i];
    }

    delete[] segments;
    segments = allSegments;
}

int main()
{
    Segment* allSegments = new Segment[startBuff];
    int size = 0;

    while(!cin.eof())
    {
        if(size >= startBuff) grow(allSegments);
        cin >> allSegments[size].start;
        cin >> allSegments[size].end;
        ++size;
    }
    --size;
    xoara(allSegments, 0, size);

    int result = 1;
    int  j = 0;
    for(int i = 1; i < size; ++i)
    {
        if(allSegments[i].start >= allSegments[j].end)
        {
            ++result;
            j = i;
        }
    }

    //  example  1 2 2 5 7 10 2 3 6 7 4 7 3 6 3 5 1 2 4 5
    cout << result;
    delete[] allSegments;
    return 0;
}

