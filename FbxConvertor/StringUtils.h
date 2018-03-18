#pragma once
#include<iostream>

class StringUtils
{
private:
	StringUtils();
	~StringUtils();
public:
	static StringUtils *instance;
	static StringUtils *getInstance();
public:
	int getFirstCharLocAt(const char *target,char ref);
	int getLastCharLocAt(const char *target, char ref);
	void sliceString(const char *target,int start,int end,char *&out);
};

