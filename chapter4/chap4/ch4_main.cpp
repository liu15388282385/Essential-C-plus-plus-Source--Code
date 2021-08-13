/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Triangular_iterator
{
public:
    Triangular_iterator(int index) : _index(index - 1) {} //???????iterator;
    bool operator==(const Triangular_iterator &) const;   //??iterator????;
    bool operator!=(const Triangular_iterator &) const;   //??iterator?????;
    int operator*() const;                                //????????;
    Triangular_iterator &operator++();                    //???????;
    Triangular_iterator operator++(int);                  //???????;

private:
    void check_integrity() const; //??_index??????;
    int _index;
};

class Triangular
{
public:
    Triangular(int len = 1, int bp = 1);
    Triangular(const Triangular &);
    Triangular &operator=(const Triangular &rhs);
    //3?????;

    int length() const { return _length; }
    int beg_pos() const { return _beg_pos; }
    int elem(int pos) const;
    //??vector??, ????, pos??????;

    void length(int nlen) { _length = nlen; }
    void beg_pos(int npos) { _beg_pos = npos; }
    //??Triangular??????????;

    bool next(int &val) const;
    void next_reset() const { _next = 1; }
    //????????_next??;

    static bool is_elem(int);
    static void gen_elements(int length);
    static void gen_elems_to_value(int value);
    static void display(int length, int beg_pos, ostream &os = cout);
    //????????, ????????vector<int> _elems;

    typedef Triangular_iterator iterator;
    Triangular_iterator begin() const
    {
        return Triangular_iterator(_beg_pos);
    }
    Triangular_iterator end() const
    {
        return Triangular_iterator(_beg_pos + _length);
    }

private:
    friend class Triangular_iterator; //??Triangular??iterator??, ???private????;
    int _length;
    int _beg_pos;
    mutable int _next;
    enum
    {
        _max_elems = 1024
    };
    static vector<int> _elems;
};

ostream &operator<<(ostream &os, const Triangular &rhs)
{
    os << "( " << rhs.beg_pos() << " , " << rhs.length() << " ) ";
    rhs.display(rhs.length(), rhs.beg_pos(), os);
    return os;
}

istream &operator>>(istream &is, Triangular &rhs)
{
    char ch1, ch2;
    int bp, len;

    is >> ch1 >> bp >> ch2 >> len;
    rhs.beg_pos(bp);
    rhs.length(len);
    rhs.next_reset();
    return is;
}

Triangular::Triangular(int len, int beg_pos) : _length(len > 0 ? len : 1), _beg_pos(beg_pos > 0 ? beg_pos : 1)
{
    _next = _beg_pos;
    int elem_cnt = _beg_pos + _length;
    if (_elems.size() < elem_cnt)
    {
        gen_elements(elem_cnt);
    }
}

Triangular::Triangular(const Triangular &rhs) : _length(rhs._length), _beg_pos(rhs._beg_pos), _next(rhs._next)
{
}

//????????
int sum(const Triangular &trian)
{
    if (0 == trian.length())
    {
        return 0;
    }
    int val, sum = 0;
    trian.next_reset(); //?????????;
    while (trian.next(val))
    {
        sum += val;
    }
    return sum;
}

int Triangular::elem(int pos) const
{
    return _elems[pos - 1];
}

bool Triangular::next(int &value) const
{
    if (0 == _next)
    {
        return false;
    }
    if (_next < _beg_pos + _length)
    {
        value = _elems[_next++];
        return true;
    }
    _next = 0;
    return false;
}

Triangular &Triangular::operator=(const Triangular &rhs)
{
    if (this != &rhs)
    {
        _length = rhs._length;
        _beg_pos = rhs._beg_pos;
        _next = 1;
    }
    return *this;
};

vector<int> Triangular::_elems; //??????vector;

bool Triangular::is_elem(int value)
{
    if (0 == _elems.size() || _elems[_elems.size() - 1] < value)
    {
        gen_elems_to_value(value);
    }
    return find(_elems.begin(), _elems.end(), value) != _elems.end();
}

void Triangular::gen_elements(int length)
{
    if (length < 0 || length > _max_elems)
    {
        cerr << "Triangular Sequence: oops: invalid size: ";
        cerr << length << " -- max size is ";
        cerr << _max_elems << endl;
        return;
    }
    if (_elems.size() < length)
    {
        int ix = _elems.size() ? _elems.size() + 1 : 1;
        while (ix <= length)
        {
            _elems.push_back(ix * (ix + 1) / 2); //??????vector??????length;
            ++ix;
        }
    }
    return;
}

void Triangular::gen_elems_to_value(int value)
{
    int ix = _elems.size();
    if (0 == ix)
    {
        _elems.push_back(1);
        ix = 1;
    }
    while (_elems[ix - 1] < value && ix < _max_elems)
    {
        _elems.push_back(ix * (ix + 1) / 2); //?????vector???????value;
        ++ix;
    }
    if (ix == _max_elems)
    {
        cerr << "Triangular Sequence: oops: value too large ";
        cerr << value << " --  exceeds max size of ";
        cerr << _max_elems << endl;
    }
    return;
}

void Triangular::display(int length, int beg_pos, ostream &os)
{
    if (length <= 0 || beg_pos <= 0)
    {
        cerr << "invalid parameters -- unable to fulfill request: ";
        cerr << length << ", " << beg_pos << endl;
        return;
    }
    int elems = beg_pos + length - 1;
    if (_elems.size() < elems)
    {
        gen_elements(elems);
    }
    for (int ix = beg_pos - 1; ix < elems; ++ix)
    {
        os << _elems[ix] << ' ';
    }
    return;
}

inline bool Triangular_iterator::operator==(const Triangular_iterator &rhs) const
{
    return _index == rhs._index; //??2?Triangular?????;
}

inline bool Triangular_iterator::operator!=(const Triangular_iterator &rhs) const
{
    return !(*this == rhs); //??????==???????;
}

class iterator_overflow //???????;
{
};

inline void Triangular_iterator::check_integrity() const
{
    if (_index > Triangular::_max_elems)
    {
        throw iterator_overflow(); //???????iterator_overflow;
    }
    if (_index > Triangular::_elems.size())
    {
        Triangular::gen_elements(_index); //?????vector?????????_index;
    }
    return;
}

inline int Triangular_iterator::operator*() const
{
    check_integrity();
    return Triangular::_elems[_index]; //??_index??????;
}

inline Triangular_iterator &Triangular_iterator::operator++()
{
    ++_index; //????;
    check_integrity();
    return *this; //????;
}

inline Triangular_iterator Triangular_iterator::operator++(int)
{
    Triangular_iterator tmp = *this; //?????;
    ++_index;                        //????;
    check_integrity();
    return tmp; //?????;
}

//???????????????;
class LessThan
{
public:
    LessThan(int val) : _val(val) {}
    int comp_val() const { return _val; }
    void comp_val(int nval) { _val = nval; }
    bool operator()(int value) const { return value < _val; }

private:
    int _val;
};

int count_less_than(const vector<int> &vec, int comp)
{
    int count = 0;
    LessThan lt(comp);

    for (int ix = 0; ix < vec.size(); ++ix)
    {
        if (lt(vec[ix])) //????;
        {
            ++count;
        }
    }
    return count;
}

void print_less_than(const vector<int> &vec, int comp, ostream &os = cout)
{
    LessThan lt(comp);
    vector<int>::const_iterator iter = vec.begin();
    vector<int>::const_iterator it_end = vec.end();

    os << "elements less than " << lt.comp_val() << endl;
    while ((iter = find_if(iter, it_end, lt)) != it_end) //?????????????find_if;
    {
        os << *iter << ' ';
        ++iter;
    }
    os << endl;
    return;
}

void prog1()
{
    char ch;
    int ival;
    bool more = true;

    while (more)
    {
        cout << "Enter value: ";
        cin >> ival;

        bool is_elem = Triangular::is_elem(ival);
        cout << ival;
        cout << (is_elem ? " is " : " is not ");
        cout << "an element in the Triangular series.\n";
        cout << "Another value? (y/n) ";
        cin >> ch;
        if (ch == 'n' || ch == 'N')
        {
            more = false;
        }
    }
    return;
}

void prog2()
{
    Triangular tri(20, 12);
    Triangular::iterator it = tri.begin();
    Triangular::iterator end_it = tri.end();

    cout << "Triangular Series of " << tri.length() << " elements\n";
    cout << tri << endl;
    while (it != end_it)
    {
        cout << *it << ' ';
        ++it;
    }
    cout << endl;
}

void prog3()
{
    int ia[16] = {17, 12, 44, 9, 18, 45, 6, 14,
                  23, 67, 9, 0, 27, 55, 8, 16};

    vector<int> vec(ia, ia + 16);
    int comp_val = 20;

    cout << "Number of elements less than ";
    cout << comp_val << " are ";
    cout << count_less_than(vec, comp_val) << endl;
    print_less_than(vec, comp_val);
    return;
}

void prog4()
{
    Triangular tri(6, 3);
    cout << tri << endl;

    Triangular tri2;
    cout << "Please enter as the example (3, 5): ";
    cin >> tri2;
    cout << tri2 << endl;
    return;
}

void prog5()
{
    Triangular tri(4, 3);
    Triangular::iterator it = tri.begin();
    Triangular::iterator end_it = tri.end();

    cout << "Triangular Series of " << tri.length() << " elements\n";
    cout << tri << endl;

    while (it != end_it)
    {
        cout << *it << ' ';
        ++it;
    }
    cout << endl;
    return;
}

int main()
{
    prog1();
    prog2();
    prog3();
    prog4();
    prog5();

    return 0;
}
