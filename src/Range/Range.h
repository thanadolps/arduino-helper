#ifndef THANADOL_HELPER_RANGE_H
#define THANADOL_HELPER_RANGE_H

class Range {
    struct Iterator {
        int value, step;
        bool operator!=(Iterator& other) {return other.value > this->value;}
        void operator++() {this->value += this->step;}
        int operator*() {return value;}
    };
    int start, stop, step;
public:
    Range(int start, int stop, int step=1) {{this->start = start; this->stop = stop; this->step = step;}}
    explicit Range(int stop) {{this->start = 0; this->stop = stop; this->step = 1;}}
    Iterator begin() { return {start, step}; }
    Iterator end() { return {stop, step}; }
};

#endif