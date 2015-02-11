#include "StringAlg.h"


namespace astox
{

namespace stringAlg
{
#ifdef ASTOX_OS_WINDOWS
std::wstring stdString2wstring(std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
#endif

#ifdef ASTX_ENABLE_NODEJS
std::string v8Value2StdString(v8::Handle<v8::Value> value){
	v8::String::Utf8Value uftValue(value->ToString());
	return std::string(*uftValue);
}
#endif

std::string replace_allBetweenNeedles(std::string startNeedle, std::string endNeedle, std::string hayStack, std::string input){

	size_t start = input.find(startNeedle);
	size_t end = input.find(endNeedle);
	std::string rest;
	while(start != std::string::npos && end != std::string::npos){
		std::string startStr = input.substr(0, start);
		std::string endStr = input.substr(end, input.size());
		rest = input.replace(start, end+endNeedle.size(), hayStack);
		start = input.find(startNeedle);
		end = input.find(endNeedle);
	}

	return rest;
}


bool char_isWhitespace(char c){
	return (isgraph(c) == false || isspace(c) || iswspace(c));
}


std::string &trim_left(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}


std::string &trim_right(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

std::string &trim(std::string &s) {
        return trim_left(trim_right(s));
}

}

}
