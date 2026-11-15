#include "String.h"
#include <iostream>
using namespace std;

int String::getUserStringLength(const char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

void String::resize(int newCap)
{
	if (newCap <= 0)
	{
		return;
	}
	char* temp = new char[newCap];

	if (data != nullptr) {
		for (int i = 0; i < (size < newCap ? size - 1 : newCap); i++)
		{
			temp[i] = data[i];
		}
		delete[]data;
	}
	temp[newCap - 1] = '\0';
	size = newCap;
	data = temp;
}

void String::shrink()
{
	if (!(*this))
	{
		return;
	}
	char* temp = new char[getLength() + 1];
	int i = 0;
	while (i < getLength())
	{
		temp[i] = data[i];
		i++;
	}
	temp[i] = '\0';
	size = getLength() + 1;
	delete[]data;
	data = temp;
}

String::String()
{
	data = nullptr;
	size = 0;
}

String::String(const char c) :String()
{
	if (c == '\0') {
		return;
	}
	data = new char[2];
	data[0] = c;
	data[1] = '\0';
	size = 2;
	return;
}

String::String(const char* str) : String()
{
	size = getUserStringLength(str) + 1;
	data = new char[size];

	for (int i = 0; i < size; i++)//inclded th '\0'
	{
		data[i] = str[i];
	}
	return;
}

String::String(const String& str) :String()
{
	if (str.data == nullptr) {
		return;
	}
	data = new char[str.size];
	size = str.size;
	for (int i = 0; i < size; i++)//inclded th '\0'
	{
		data[i] = str.data[i];
	}
}

String::~String()
{
	if (data != nullptr)
	{
		delete[]data;
		data = nullptr;
		size = 0;
	}
}

String& String::operator=(const String& str)
{
	if (this == &str)
	{
		return *this;
	}
	if (str.data == nullptr) {
		return *this;
	}
	if (data != nullptr) {
		this->~String();
	}
	data = new char[str.size];
	size = str.size;
	for (int i = 0; i < size; i++)
	{
		data[i] = str.data[i];
	}
	return *this;
}

void String::input()
{
	if (data != nullptr)
	{
		delete[]data;
	}
	char ch;
	int i = 0;
	if (!(*this)) {
		resize(2);
	}
	while (cin.get(ch) && ch != '\n') {
		data[i] = ch;
		if ((i + 1) == size) {
			resize(size * 2);
		}
		i++;
	}
	data[i] = '\0';
}

char& String::operator [](const int index)//'\0' index included
{
	if (index < 0 || index >= size) {
		cout << "Wrong" << endl;
		exit(0);
	}
	return data[index];
}

const char& String::operator[](const int index) const
{
	if (index < 0 || index >= size) {
		cout << "Wrong" << endl;
		exit(0);
	}
	return data[index];
}

void String::display() const
{
	if (data == nullptr)
	{
		cout << "nothing";
		return;
	}
	cout << data << endl;
}

bool String::operator ! () const
{
	if (data == nullptr || data[0] == '\0')
	{
		return true;
	}
	return false;
}

int String::getLength() const
{
	if (data == nullptr || data[0] == '\0') {
		return 0;
	}
	int len = 0;
	for (int i = 0; i < size - 1; i++)//even if ther this null temrinator in between it will ignore
	{
		len++;
	}
	return len;
}

int String::getSize() const
{
	if (data == nullptr) {
		return 0;
	}
	int i = 0;
	while (data[i] != '\0') {
		i++;
	}
	i++;
	return i;
}

int String::find(const String& substr, const int start) const
{
	if (start >= size - 1 || substr.data == nullptr || substr.data[0] == '\0' || this->data == nullptr || this->data[0] == '\0' || substr.size > this->size || start < 0) {
		return -1;
	}
	for (int i = start; i < size - 1; i++)
	{
		int index = 0;
		if (substr.data[index] == data[i]) {
			index++;
			for (int j = i + 1; j < size - 1 && index < substr.size - 1; j++)
			{
				if (substr.data[index] == data[j])
				{
					index++;
				}
				else {
					j = size;
				}
			}
			if (index == substr.size - 1)
			{
				return i;
			}
		}
	}

	return -1;
}

void String::insert(const int index, const String& subStr)
{
	if (subStr.data == nullptr || index < 0) {
		return;
	}
	if (!(*this)) {//if the des is nullptr
		if (index != 0) {
			return;
		}
		*this += subStr;
		return;
	}
	else if (index > size - 1)
	{
		return;
	}
	char* temp = new char[(size - 1) + subStr.size];
	int i = 0;
	while (i < index)
	{
		temp[i] = data[i];
		i++;
	}
	int x = i;
	for (int j = 0; j < subStr.size - 1; j++, i++)
	{
		temp[i] = subStr.data[j];
	}
	while (x < size - 1)
	{
		temp[i] = data[x];
		i++;
		x++;
	}
	temp[i] = '\0';
	delete[]data;
	size = (size - 1) + subStr.size;
	data = temp;
	return;
}

void String::remove(const int index, const int count) {
	if (index < 0 || index >= size - 1 || count <= 0)
	{
		return;
	}
	if (count > (size - 1 - index))
	{
		return;
	}
	if (index == 0 && count == size - 1)
	{
		delete[]data;
		size = 0;
		data = nullptr;
		return;
	}
	char* temp = new char[size - count];
	int i = 0;
	while (i < index) {
		temp[i] = data[i];
		i++;
	}
	int x = index + count;
	while (x < size - 1)
	{
		temp[i] = data[x];
		i++;
		x++;
	}
	temp[i] = '\0';
	size = size - count;
	delete[]data;
	data = temp;
	return;
}

int String::replace(const String& old, const String& newSubStr) {
	if (!(*this) || !old || !newSubStr)
	{
		return 0;
	}
	if (find(old) == -1)
	{
		return 0;
	}
	int count = 0;
	int start = 0;
	while (true)
	{
		int index = find(old, start);
		if (index == -1)
		{
			return count;
		}
		count++;
		remove(index, old.size - 1);
		insert(index, newSubStr);
		start = index + newSubStr.size - 1;
	}
}

void String::trimLeft()
{
	if (!(*this))
	{
		return;
	}
	int  i = 0;
	int count = 0;
	while (i < size - 1 && data[i] == ' ')
	{
		count++;
		i++;
	}
	remove(0, count);
}

void String::trimRight()
{
	if (!(*this))
	{
		return;
	}
	int i = size - 2;
	int count = 0;
	while (i >= 0 && data[i] == ' ')
	{
		count++;
		i--;
	}
	remove(i + 1, count);
}

void String::trim()
{
	if (!(*this))
	{
		return;
	}
	trimLeft();
	trimRight();
}

void String::makeUpper()
{
	if (!(*this))
	{
		return;
	}
	for (int i = 0; i < size - 1; i++)
	{
		if (data[i] >= 'a' && data[i] <= 'z')
		{
			data[i] = data[i] - 32;
		}
	}
	return;
}

void String::makeLower()
{
	if (!(*this))
	{
		return;
	}
	for (int i = 0; i < size - 1; i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
		{
			data[i] = data[i] + 32;
		}
	}
	return;
}

bool String::operator==(const String& s2) const
{
	return compare(s2) == 0;
}

bool String::operator>(const String& s2) const
{
	return compare(s2) > 0;
}

bool String::operator<(const String& s2) const
{
	return compare(s2) < 0;
}

bool String::operator>=(const String& s2) const
{
	return compare(s2) >= 0;
}

bool String::operator<=(const String& s2) const
{
	return compare(s2) <= 0;
}

bool String::operator!=(const String& s2) const
{
	return compare(s2) != 0;
}

void String::reverse()
{
	if (!(*this))
	{
		return;
	}
	char* temp = new char[size];
	int x = size - 2, i = 0;
	while (i < size - 1)
	{
		temp[i] = data[x];
		x--;
		i++;
	}
	temp[size - 1] = '\0';
	delete[]data;
	data = temp;
}

int String::compare(const String& s2) const
{
	if (this == &s2)
	{
		return 0;
	}
	if (!(*this) && !s2)
	{
		return 0;
	}
	if (!(*this))
	{
		return -1;
	}
	if (!s2)
	{
		return 1;
	}

	for (int i = 0; i < (size < s2.size ? size - 1 : s2.size - 1); i++)
	{
		if (data[i] < s2.data[i])
		{
			return -1;
		}
		else if (data[i] > s2.data[i])
		{
			return 1;
		}
	}
	if (getLength() < s2.getLength())
	{
		return -1;
	}
	if (getLength() > s2.getLength())
	{
		return 1;
	}
	return 0;
}

String String::left(const int count)
{
	int nonCount = count;
	if (!(*this) || count == 0) {
		String empty;
		return empty;
	}
	if (count > getLength())
	{
		nonCount = getLength();
	}
	char* temp = new char[nonCount + 1];
	int i = 0;
	while (i < nonCount)
	{
		temp[i] = data[i];
		i++;
	}
	temp[i] = '\0';
	String left{ temp };
	delete[]temp;
	return left;
}

String String::right(const int count)
{
	int nonCount = count;
	if (!(*this) || count == 0) {
		String empty;
		return empty;
	}
	if (count > getLength())
	{
		nonCount = getLength();
	}
	if (count <= 0)
	{
		return String{};
	}
	char* temp = new char[nonCount + 1];
	int i = getLength() - nonCount;
	int x = 0;
	while (x < nonCount)
	{
		temp[x] = data[i];
		i++;
		x++;
	}
	temp[x] = '\0';
	String right{ temp };
	delete[]temp;
	return right;
}

long long int String::convertToInteger() const
{

	if (!(*this))
	{
		return 0;
	}
	for (int i = 0; i < size - 1; i++)
	{
		if (data[i] < '0' || data[i]>'9' || data == nullptr)
		{
			return 0;
		}
	}
	bool neg = data[0] == '-';
	long long int num = 0;
	for (int i = neg ? 1 : 0; i < size - 1; i++)
	{
		num = (num * 10) + (data[i] - '0');
	}
	return neg ? num * -1 : num;
}

String String:: operator +(const String& s2) const
{
	if (data == nullptr && s2.data == nullptr)
	{
		String empty;
		return empty;
	}
	if (!(*this))
	{
		return s2;
	}
	if (!s2)
	{
		String concat{ *this };
		return concat;
	}
	char* temp = new char[(size - 1) + s2.size];
	int i = 0;
	while (i < size - 1)
	{
		temp[i] = data[i];
		i++;
	}
	int x = 0;
	while (x < s2.size - 1)
	{
		temp[i] = s2.data[x];
		i++;
		x++;
	}
	temp[i] = '\0';
	String concat;
	concat.data = temp;
	concat.size = (size - 1) + s2.size;
	return concat;
}

String String::operator += (const String& s2)
{
	if (!s2)
	{
		return *this;
	}
	if (data == nullptr)
	{
		data = new char[s2.size];
		for (int i = 0; i < s2.size; i++)
		{
			data[i] = s2.data[i];
		}
		size = s2.size;
		return *this;
	}
	int oldSize = size;
	resize((size - 1) + s2.size);
	for (int i = oldSize - 1, x = 0; x < s2.size; i++, x++)
	{
		data[i] = s2.data[x];
	}
	return *this;
}

String& String::operator =(const long long int num)
{
	if (data != nullptr)
	{
		delete[]data;
		size = 0;
	}
	int count = 0;
	bool negative = false;
	if (num < 0)
	{
		negative = true;
	}
	long long int temp = negative ? (-1 * num) : num;
	long long int temp2 = negative ? (-1 * num) : num;
	if (num == 0)
	{
		count++;
	}
	else {
		while (temp != 0)
		{
			temp /= 10;
			count++;
		}
		if (negative)
		{
			count++;
		}
	}
	data = new char[count + 1];
	int i = count - 1;
	char c;
	while (i >= (negative ? 1 : 0)) {
		c = (temp2 % 10) + '0';
		data[i] = c;
		temp2 /= 10;
		i--;
	}
	if (negative)
	{
		data[0] = '-';
	}
	data[count] = '\0';
	size = count + 1;
	return (*this);
}

String& String::operator=(const double num)
{
	if (data != nullptr)
	{
		delete[]data;
		data = nullptr;
		size = 0;
	}
	if (num == 0.0)
	{
		*this = String{ "0.0" };
		return *this;
	}
	bool neg = num < 0.0;
	double  temp = neg ? -num : num;
	int integral1 = (int)temp;

	*this = (long long int)num;
	*this += String{ '.' };

	temp = temp - integral1;

	for (int i = 0; i < 6; i++)
	{
		temp *= 10;
		int digit = (int)temp;
		char c = (digit % 10) + '0';
		*this += String{ c };
		temp -= digit;
	}
	return *this;
}

