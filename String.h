#ifndef STRING_H
#define STRING_H

class String
{
	char* data;
	int size;
	int getUserStringLength(const char*);//for string string user enter
	int compare(const String&) const;
public:
	String();
	String(const char);
	String(const char*);
	String(const String&);
	~String();
	String& operator =(const String&);
	void input();
	void shrink();
	char& operator [] (const int);
	const char& operator [] (const int) const;
	bool operator ! () const;
	int getLength() const;
	int getSize() const;
	void display() const;
	int find(const String&, const int = 0) const;
	void insert(const int, const String&);
	void remove(const int, const int = 1);
	int replace(const String&, const String&);
	void trimLeft();
	void trimRight();
	void trim();
	void makeUpper();
	void makeLower();
	bool operator == (const String& s2) const;
	bool operator > (const String& s2) const;
	bool operator >= (const String& s2) const;
	bool operator < (const String& s2) const;
	bool operator <= (const String& s2) const;
	bool operator != (const String& s2) const;
	void reverse();
	void resize(int newCap);
	String left(const int);
	String right(const int);
	long long int convertToInteger() const;
	String operator + (const String& s2) const;
	String operator += (const String& s2);
	String& operator =(const long long int num);
	String& operator =(const double num);
};

#endif
