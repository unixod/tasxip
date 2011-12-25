/*----------------------------------------------------------------------------+
|      ___   __                                                               |
|      //_/\//                                                                |
|    _// _//\\                                                                |
|                                                                             |
|   -=[ProfX]=-                                                               |
|   Created by Zakirov Eldar aka ProfX, 2011                                  |
|                                                                             |
|   Header:                                                                   |
|       TasIXP                                                                |
|   Description:                                                              |
|        .                                                 |
|   Interface:                                                                |
|       void init(T min, T max);                                              |
|                                                            |
|       void exclude(T min, T max);                                           |
|           ,       .      |
|   Dependiences:                                                             |
|   To Do:                                                                    |
+----------------------------------------------------------------------------*/

#ifndef RANGESET_H
#define RANGESET_H

#include <list>
#include <functional>
#include <algorithm>
#include <vector>

template <class T>
class RangeSet : public std::list< std::pair<T, T> >{
    typedef std::pair<T, T> TRange;

    struct pred : std::unary_function<const TRange&, bool>{
        const T &_ip;
        pred(const T &ip) : _ip(ip){}

        bool operator()(const TRange &range){
            return (range.first <= _ip) && (range.second >= _ip);
        }
    };

public:
    //RangeSet(T min, T max);
    void init(T min, T max);
    void exclude(T min, T max);

private:
    void _exclude(const TRange&);
};


/*template <class T>
RangeSet<T>::RangeSet(T min, T max){
    this->push_back(std::make_pair(min, max));
}*/

template <class T>
void RangeSet<T>::init(T min, T max){
    this->clear();
    this->push_back(std::make_pair(min, max));
}

template <class T>
void RangeSet<T>::exclude(T min, T max){
    const TRange range(min, max);
    _exclude(range);
}

template <class T>
void RangeSet<T>::_exclude(const TRange &exc_r){
    //      ip
    typename RangeSet<T>::iterator iter_min = std::find_if(this->begin(), this->end(), pred(exc_r.first));
    typename RangeSet<T>::iterator iter_max = std::find_if(this->begin(), this->end(), pred(exc_r.second));

    if((iter_min == iter_max) && (iter_min != this->end())){                        //irange = 256 - 734 / exc_r = 256 - 734 -> exc_r is in irange
        typename RangeSet<T>::iterator &irange = iter_min;

        if(*irange == exc_r) this->erase(irange);                                   //irange = 256 - 734 / exc_r = 256 - 734 -> irange - deleted
        else if(irange->first == exc_r.first) irange->first = exc_r.second + 1;     //irange = 256 - 734 / exc_r = 256 - 500 -> irange = 256 - 499
        else if(irange->second == exc_r.second) irange->second = exc_r.first - 1;   //irange = 256 - 734 / exc_r = 500 - 734 -> irange = 501 - 734
        else {                                                                      //irange = 256 - 734 / exc_r = 300 - 500 -> irange splited to irange1 = 256 - 299, irange2 = 501 - 734
            this->insert(irange, *irange);
            irange->first = exc_r.second + 1;
            irange--;
            irange->second = exc_r.first - 1;
        }
    } else {
        if(iter_min != this->end()){
            typename RangeSet<T>::iterator &irange = iter_min;

            if(irange->first == exc_r.first) this->erase(irange);   //irange = 256 - 400 / exc_r = 256 - 700 -> irange - deleted
            else irange->second = exc_r.first - 1;                //irange = 256 - 400 / exc_r = 300 - 700 -> irange = 256 - 299
        }

        if(iter_max != this->end()){
            typename RangeSet<T>::iterator &irange = iter_max;

            if(irange->second == exc_r.second) this->erase(irange); //irange = 500 - 700 / exc_r = 256 - 700 -> irange - deleted
            else irange->first = exc_r.second + 1;                //irange = 500 - 700 / exc_r = 256 - 600 -> irange - 500 - 599
        }
    }
}

#endif // RANGESET_H
