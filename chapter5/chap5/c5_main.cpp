/*
 * @Descripttion: 
 * @version: x.x
 * @Author: LMH
 * @Date: 1999-12-07 13:19:06
 * @LastEditors: LMH
 * @LastEditTime: 2021-08-13 15:55:16
 */
/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <string>
using namespace std;

class LibMat
{
public:
	LibMat() { cout << "LibMat::LibMat() default constructor!\n"; }
	virtual ~LibMat() { cout << "LibMat::~LibMat() destructor!\n"; }
	virtual void print() const { cout << "LibMat::print() -- I am a LibMat object!\n"; }
};

class Book : public LibMat
{
public:
	Book(const string &title, const string &author) : _title(title), _author(author)
	{
		cout << "Book::Book(" << _title;
		cout << ", " << _author << ")  constructor\n";
	}
	~Book() { cout << "Book::~Book() destructor!\n"; }
	virtual void print() const //虚函数重写父类方法;
	{
		cout << "Book::print() -- I am a Book object!\n";
		cout << "My title is: " << _title << '\n';
		cout << "My author is: " << _author << endl;
	}
	const string &title() const { return _title; }
	const string &author() const { return _author; }

protected:
	string _title;
	string _author;
};

class AudioBook : public Book
{
public:
	AudioBook(const string &title, const string &author, const string &narrator)
		: Book(title, author), _narrator(narrator) //先使用父类的构造函数初始化父类成员后再初始化自身成员;
	{
		cout << "AudioBook::AudioBook(" << _title;
		cout << ", " << _author;
		cout << ", " << _narrator;
		cout << ")  constructor\n";
	}
	~AudioBook() { cout << "AudioBook::~AudioBook() destructor!\n"; }
	virtual void print() const //虚函数重写父类方法;
	{
		cout << "AudioBook::print() -- I am a AudioBook object!\n";
		cout << "My title is: " << _title << '\n';
		cout << "My author is: " << _author << '\n';
		cout << "My narrator is: " << _narrator << endl;
	}
	const string &narrator() const { return _narrator; }

protected:
	string _narrator;
};

void print(const LibMat &mat)
{
	cout << "in global print(): about to print mat.print()\n";
	mat.print();
}

int main()
{
	//使用花括号可以看到析构函数被调用后的情况;
	{
		cout << "\nCreating a LibMat object to print()\n";
		LibMat m;
		print(m);
	}
	{
		cout << "\nCreating a Book object to print()\n";
		Book b("The Castle", "Franz Kafka");
		print(b);
	}
	{
		cout << "\nCreating a AudioBook object to print()\n";
		AudioBook ab("Man Without Qualities", "Robert Musil", "Kenneth Meyer");
		print(ab);
	}
	return 0;
}
