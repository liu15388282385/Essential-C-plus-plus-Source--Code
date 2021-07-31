/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <algorithm>
using namespace std;
const int int_size = 12;
const int string_size = 4;
const int int_not_present = 1024;

static int ia[int_size] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
static string sa[string_size] = {"pooh", "piglet", "eeyore", "tigger"};

static vector<int> ivec(ia, ia + int_size);
static vector<string> svec(sa, sa + string_size);

//第1个find函数, 查找vector<int>中的元素;
const int *find_ver1(const vector<int> &vec, int value)
{
    for (int ix = 0; ix < vec.size(); ++ix)
    {
        if (vec[ix] == value)
        {
            return &vec[ix];
        }
    }
    return nullptr;
}

//第2个find函数, 查找vector中自定义类型的元素;
template <typename elemType>
const elemType *find_ver2(const vector<elemType> &vec, const elemType &value)
{
    for (int ix = 0; ix < vec.size(); ++ix)
    {
        if (vec[ix] == value)
        {
            return &vec[ix];
        }
    }
    return nullptr;
}

//mybegin函数防止获取错误的起始位置;
template <typename elemType>
inline const elemType *mybegin(const vector<elemType> &vec) //源程序begin与标准库中的函数重名需改为mybegin;
{
    return vec.empty() ? nullptr : &vec[0];
}

//myend函数防止获取错误的终止位置;
template <typename elemType>
inline const elemType *myend(const vector<elemType> &vec) //源程序end与标准库中的函数重名需改为myend;
{
    return vec.empty() ? nullptr : &vec[vec.size()];
}

//第3个find函数, 传入数组长度查找数组中自定义类型的元素(使用下标);
template <typename elemType>
const elemType *find_ver3(const elemType *array, int size, const elemType &value)
{
    if (array == nullptr || size < 1)
    {
        return nullptr;
    }
    for (int ix = 0; ix < size; ++ix)
    {
        if (array[ix] == value) //下标法;
        {
            return &array[ix];
        }
    }
    return nullptr;
}

//第4个find函数, 传入数组长度查找数组中自定义类型的元素(使用指针);
template <typename elemType>
const elemType *find_ver4(const elemType *array, int size, const elemType &value)
{
    if (array == nullptr || size < 1)
    {
        return nullptr;
    }
    for (int ix = 0; ix < size; ++ix, ++array)
    {
        if (*array == value) //指针法;
        {
            return array;
        }
    }
    return nullptr;
}

//第5个find函数, 使用数组首地址和末地址查找数组中自定义类型的元素;
template <typename elemType>
const elemType *find_ver5(const elemType *first, const elemType *last, const elemType &value)
{
    if (first == nullptr || last == nullptr)
    {
        return nullptr;
    }
    while (first != last)
    {
        if (*first == value)
        {
            return first;
        }
        ++first;
    }
    return nullptr;
}

//第6个find函数, 查找可迭代类型的容器中的元素;
template <typename IteratorType, typename elemType>
IteratorType find_ver6(IteratorType first, IteratorType last, const elemType &value)
{
    while (first != last)
    {
        if (value == *first)
        {
            return first;
        }
        ++first;
    }
    return last;
}

//测试上述的所有find函数;
void prog_find_vers()
{
    const int *iptr = find_ver1(ivec, ivec[2]); //使用vector<int>测试find1函数;
    if (iptr != &ivec[2])
    {
        cerr << "?? find_ver1 failed!\n";
    }
    else
    {
        cerr << "!! find_ver1 ok!\n";
    }

    const string *sptr = find_ver2(svec, svec[2]); //使用vector<string>测试find2函数;
    if (sptr != &svec[2])
    {
        cerr << "?? find_ver2 failed with string!\n";
    }
    else
    {
        cerr << "!! find_ver2 ok with string!\n";
    }

    iptr = find_ver2(ivec, ivec[2]); //使用vector<int>测试find2函数;
    if (iptr != &ivec[2])
    {
        cerr << "?? find_ver2 failed with int!\n";
    }
    else
    {
        cerr << "!! find_ver2 ok with int!\n";
    }

    iptr = find_ver3(ia, int_size, ia[2]); //使用int数组测试find3函数;
    if (iptr != &ia[2])
    {
        cerr << "?? find_ver3 failed with int array!\n";
    }
    else
    {
        cerr << "!! find_ver3 ok with int array!\n";
    }

    sptr = find_ver3(sa, string_size, sa[2]); //使用string数组测试find3函数;
    if (sptr != &sa[2])
    {
        cerr << "?? find_ver3 failed with string array!\n";
    }
    else
    {
        cerr << "!! find_ver3 ok with string array!\n";
    }

    iptr = find_ver4(mybegin(ivec), ivec.size(), ivec[2]); //使用vector<int>和mybegin函数测试find4函数;
    if (iptr != &ivec[2])
    {
        cerr << "?? find_ver4 failed with int vector!\n";
    }
    else
    {
        cerr << "!! find_ver4 ok with int vector!\n";
    }

    sptr = find_ver4(mybegin(svec), svec.size(), svec[2]); //使用vector<string>和mybegin函数测试find4函数;
    if (sptr != &svec[2])
    {
        cerr << "?? find_ver4 failed with string vector!\n";
    }
    else
    {
        cerr << "!! find_ver4 ok with string vector!\n";
    }

    sptr = find_ver5(sa, sa + string_size, sa[2]); //使用string数组测试find5函数;
    if (sptr != &sa[2])
    {
        cerr << "?? find_ver5 failed with string array!\n";
    }
    else
    {
        cerr << "!! find_ver5 ok with string array!\n";
    }

    iptr = find_ver5(mybegin(ivec), myend(ivec), ivec[2]); //使用vector<int>和边界判断函数测试find5函数;
    if (iptr != &ivec[2])
    {
        cerr << "?? find_ver5 failed with int vector!\n";
    }
    else
    {
        cerr << "!! find_ver5 ok with int vector!\n";
    }

    iptr = find_ver5(mybegin(ivec), myend(ivec), int_not_present); //使用vector<int>和边界元素测试find5函数;
    if (iptr != 0)
    {
        cerr << "?? find_ver5 failed with int not present in vector!\n";
    }
    else
    {
        cerr << "!! find_ver5 ok with int not present in vector!\n";
    }

    sptr = find_ver6(sa, sa + string_size, sa[2]); //使用string数组测试find6函数;
    if (sptr != &sa[2])
    {
        cerr << "?? find_ver6 failed with string array and iterators!\n";
    }
    else
    {
        cerr << "!! find_ver3 ok with string array and iterators!\n";
    }

    vector<int>::iterator it = find_ver6(ivec.begin(), ivec.end(), ivec[2]); //使用vector<int>测试find6函数;
    if (*it != ivec[2])
    {
        cerr << "?? find_ver6 failed with int vector and iterators!\n";
    }
    else
    {
        cerr << "!! find_ver4 ok with int vector and iterators!\n";
    }
    return;
}

vector<int> less_than_10(const vector<int> &vec)
{
    vector<int> nvec;
    for (int ix = 0; ix < vec.size(); ++ix)
    {
        if (vec[ix] < 10)
        {
            nvec.push_back(vec[ix]);
        }
    }
    return nvec;
}

bool less_than(int v1, int v2)
{
    return v1 < v2;
}

bool greater_than(int v1, int v2)
{
    return v1 > v2;
}

//函数指针pred提高元素compare适用性;
vector<int> filter_ver1(const vector<int> &vec, int filter_value, bool (*pred)(int, int))
{
    vector<int> nvec;

    for (int ix = 0; ix < vec.size(); ++ix)
    {
        if (pred(vec[ix], filter_value))
        {
            nvec.push_back(vec[ix]);
        }
    }
    return nvec;
}

//使用标准库中的less<int>和bind2nd进行元素比较;
vector<int> filter_ver2(const vector<int> &vec, int val, less<int> lt)
{
    vector<int> nvec;
    vector<int>::const_iterator iter = vec.begin();

    while ((iter = find_if(iter, vec.end(), bind2nd(lt, val))) != vec.end())
    {
        nvec.push_back(*iter);
        iter++;
    }
    return nvec;
}

//使用输入iterator和输出iterator完善filter函数;
template <typename InputIterator, typename OutputIterator,
          typename ElemType, typename Comp>
OutputIterator
filter_ver3(InputIterator first, InputIterator last,
            OutputIterator at, const ElemType &val, Comp pred)
{
    while ((first = find_if(first, last, bind2nd(pred, val))) != last)
    {
        *at++ = *first++;
    }
    return at;
}

vector<int> sub_vec(const vector<int> &vec, int val)
{
    vector<int> local_vec(vec);
    sort(local_vec.begin(), local_vec.end()); //元素升序排序;

    //找到第一个大于val的元素;
    vector<int>::iterator iter = find_if(local_vec.begin(), local_vec.end(), bind2nd(greater<int>(), val));
    local_vec.erase(iter, local_vec.end()); //删除之后的所有比val大的元素;
    return local_vec;
}

//测试上述的所有filter函数;
void prog_filter_vers()
{
    const int solution_size = 6;

    vector<int> local_vec = less_than_10(ivec); //返回一个所有元素小于10的vector<int>;
    if (local_vec.size() != solution_size)
    {
        cerr << "?? less_than_10 failed! expected expected ";
        cerr << solution_size << ", received: ";
        cerr << local_vec.size() << endl;
    }
    else
    {
        cerr << "!! less_than_10 ok!\n";
    }

    const int partition_value = 10;
    local_vec = filter_ver1(ivec, partition_value, greater_than); //使用greater_than函数处理并返回一个所有元素大于10的vector<int>;
    if (local_vec.size() != solution_size)
    {
        cerr << "?? filter_ver1 failed! expected expected ";
        cerr << solution_size << ", received: ";
        cerr << local_vec.size() << endl;
    }
    else
    {
        cerr << "!! filter_ver1 ok!\n";
    }

    local_vec = filter_ver2(ivec, partition_value, less<int>()); //使用less模板处理并返回一个所有元素大于10的vector<int>;
    if (local_vec.size() != solution_size)
    {
        cerr << "?? filter_ver2 failed! expected ";
        cerr << solution_size << ", received: ";
        cerr << local_vec.size() << endl;
    }
    else
    {
        cerr << "!! filter_ver2 ok!\n";
    }

    int ia2[solution_size];
    filter_ver3(ia, ia + int_size, ia2, partition_value, less<int>()); //使用纯模板函数filter_ver3处理元素并放置在数组ia2中;

    int err_cnt = 0;
    for (int ix = 0; ix < solution_size; ++ix)
    {
        if (ia[ix] != ia2[ix])
        {
            ++err_cnt;
        }
    }
    if (err_cnt)
    {
        cerr << "?? filter_ver3 failed for array! ";
        cerr << err_cnt << " unexpected values\n";
    }
    else
    {
        cerr << "!! filter_ver3 for array ok!\n";
    }

    vector<int> ivec2(solution_size);
    filter_ver3(ivec.begin(), ivec.end(), ivec2.begin(), partition_value, greater<int>());
    //使用纯模板函数filter_ver3处理元素并放置在定长vector中;
    err_cnt = 0;
    int ix = solution_size;
    for (int iy = 0; ix < ivec.size(); ++ix, ++iy)
    {
        if (ivec[ix] != ivec2[iy])
        {
            ++err_cnt;
        }
    }
    if (err_cnt)
    {
        cerr << "?? filter_ver3 failed for vector! ";
        cerr << err_cnt << " unexpected values\n";
    }
    else
    {
        cerr << "!! filter_ver3 for vector ok!\n";
    }

    vector<int> ivec3;
    filter_ver3(ivec.begin(), ivec.end(), back_inserter(ivec3), partition_value, greater<int>());
    //使用纯模板函数filter_ver3处理元素并使用back_inserter逐渐添加至ivec3的末尾;
    if (ivec3.size() != solution_size)
    {
        cerr << "?? filter_ver3 with back inserter failed! expected ";
        cerr << solution_size << ", received: ";
        cerr << ivec3.size() << endl;
    }
    else
    {
        cerr << "!! filter_ver3 with back inserter ok!\n";
    }
    ivec3 = sub_vec(ivec, partition_value); //删除ivec中所有大于partition_value的元素并赋值给ivec3;
    if (ivec3.size() != solution_size)
    {
        cerr << "?? sub_vec failed! expected ";
        cerr << solution_size << ", received: ";
        cerr << ivec3.size() << endl;
    }
    else
    {
        cerr << "!! sub_vec ok!\n";
    }
    return;
}

//从stdin流输入数据并输出至stdout流中;
void prog_io_std()
{
    cout << "Please enter some text, then indicate end of file!\n";

    istream_iterator<string> is(cin);
    istream_iterator<string> eof;
    vector<string> text;

    copy(is, eof, back_inserter(text));
    sort(text.begin(), text.end());
    ostream_iterator<string> os(cout, " ");
    copy(text.begin(), text.end(), os);
    return;
}

//文件输入输出;
void prog_io_fil()
{
    ifstream in_file("input_file.txt");
    //使用前应创建一个文本文件input_file.txt处理输入;
    ofstream out_file("output_file.txt");
    //使用前应创建一个文本文件output_file.txt处理输出;

    if (!in_file || !out_file)
    {
        cerr << "?? unable to open the necessary files.\n";
        return;
    }
    else
    {
        cerr << "!! ok: input and output files opened!\n";
    }
    istream_iterator<string> is(in_file);
    istream_iterator<string> eof;
    vector<string> text;

    copy(is, eof, back_inserter(text));
    if (text.empty())
    {
        cerr << "?? iostream iterators failed: string vector empty!\n";
    }
    else
    {
        cerr << "!! iostream iterators seem to work: ";
        cerr << text.size() << " strings read in!\n";
    }
    sort(text.begin(), text.end());
    ostream_iterator<string> os(out_file, " ");
    unique_copy(text.begin(), text.end(), os);
    return;
}

void prog_io_iters()
{
    //prog_io_std();
    //↑测试标准流中的输入输出, 若是想测试可以处理掉注释;
    prog_io_fil();
}

int main()
{
    cerr << "About to execute prog_find_vers()\n";
    prog_find_vers();

    cerr << "\n\nAbout to execute prog_filter_vers()\n";
    prog_filter_vers();

    cerr << "\n\nAbout to execute prog_io_iters()\n";
    prog_io_iters();

    cerr << "\n\nOk -- done!\n";
    return 0;
}
