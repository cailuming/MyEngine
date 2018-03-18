#include "StringUtils.h"

StringUtils::StringUtils()
{
	memset(this, 0, sizeof(*this));
}


StringUtils::~StringUtils()
{

}
 
StringUtils *StringUtils::instance=0;

StringUtils *StringUtils::getInstance() {
	if (nullptr==instance) {
		instance = new StringUtils();
	}
	return instance;
};

int StringUtils::getFirstCharLocAt(const char *target, char ref) {
	char *p = (char*)target;
	int index = 0;
	while (p) {
		if (*p==ref){
			break;
		}
		++p;
		++index;
	}
	return index;
};

int StringUtils::getLastCharLocAt(const char *target, char ref) {
	char *p = (char*)target;
	int index = 0;
	int ret = 0;
	while (*p) {
		if (*p == ref) {
			ret = index;
		}
		++p;
		++index;
	}
	return ret;
};

void StringUtils::sliceString(const char *target, int start, int end, char *&out) {
	if (start >= end) return;

	char *p = (char*)&target[start];
	memcpy(out, p, end - start-4);
	out[end - start - 4] = 0;
};



