#include <cstring>
#include <iostream>

class MyString {
    friend MyString operator+(const MyString& lhs, const MyString& rhs) {
        char* result = new char[strlen(lhs.str) + strlen(rhs.str) + 1];
        for (int i = 0; i < strlen(lhs.str); i++) {
            result[i] = lhs.str[i];
        }
        for (int i = 0; i < strlen(rhs.str); i++) {
            result[i + strlen(lhs.str)] = rhs.str[i];
        }
        result[strlen(lhs.str) + strlen(rhs.str) + 1] = '\0';
        MyString res {result};
        delete[] result;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj) {
        os << obj.str;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, const MyString& obj) {
        is >> obj.str;
        return is;
    }

    public: 
        char* str = nullptr;
        MyString() {
            str = new char[1];
            str[0] = '\0';
        };

        MyString(char* chr) {
            if (chr == nullptr) {
                str = new char[1];
                str[0] = '\0';
                return;
            }
            str = new char[strlen(chr) + 1];
            strcpy(str, chr);
        } 

        MyString(MyString& copyStr) {
            str = new char[strlen(copyStr.str) + 1];
            strcpy(str, copyStr.str);
        }

        MyString(MyString&& moveStr) {
            str = moveStr.str;
            moveStr.str = nullptr;
        }

        ~MyString() {
            delete str;
        }

        void pop_back() {
            str[strlen(str) - 1] = '\0';
        }

        void push_back(char chr) {
            char* buff = new char[strlen(str) + 1];
            strcpy(buff, str);

            str = new char[strlen(buff) + 2];
            strcpy(str, buff);
            str[strlen(buff) + 1] = '\0';
            str[strlen(buff)] = chr;

            delete[] buff;
        }

        int length() {
            return (int) strlen(str);
        }

        void copy(char*& s, int pos, int len) {
            s = new char[len + 1];
            for (int i = 0; i < len; i++) {
                s[i] = str[pos + i];
            }
            s[len] = '\0';
        }

        void swp(MyString& rhs) {
            char* temp = nullptr;
            temp = rhs.str;
            rhs.str = str;
            str = temp;
        }
};

int main() {
    // Constructor with no arguments
	MyString a;
    std::cout << "Constructor with no arguments:" << std::endl;
    std::cout << a << std::endl;

	// Convert string literal to
	// char array
	char temp[] = "Hello";

	// Constructor with one argument
	MyString b{temp};
    std::cout << "Constructor with one arguments:" << std::endl;
    std::cout << b << std::endl;

	// Copy constructor
	MyString c{b};
    std::cout << "Copy constructor:" << std::endl;
    std::cout << c << std::endl;
    std::cout << b << std::endl;

	// One arg constructor called,
	// then the move constructor
	MyString d{ MyString{ temp } };
    std::cout << "Move constructor:" << std::endl;
    std::cout << d << std::endl;

    d.pop_back();
    std::cout << "Pop back last element:" << std::endl;
    std::cout << d << std::endl;

    d.push_back('o');
    std::cout << "Push back o to last:" << std::endl;
    std::cout << d << std::endl;

    std::cout << "Length:" << std::endl;
    std::cout << d.length() << std::endl;

    char* s;
    d.copy(s, 0, 5);
    std::cout << "Copy:" << std::endl;
    std::cout << s << std::endl;

    char temp1[] = "World";
    MyString e{temp1};
    d.swp(e);
    std::cout << "Swap:" << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;

    std::cout << "Concatenation:" << std::endl;
    MyString f(e + d);
    std::cout << f << std::endl;

	return 0;
}