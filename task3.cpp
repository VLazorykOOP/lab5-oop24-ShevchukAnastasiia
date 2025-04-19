#include <iostream>
#include <cstring>
#include <cctype>

class String {
protected:
    char* data;

public:
    // Default constructor
    String() : data(nullptr) {}

    // Constructor from C-string
    String(const char* str) {
        if (str) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

    // Copy constructor
    String(const String& other) {
        if (other.data) {
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    // Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            if (other.data) {
                data = new char[strlen(other.data) + 1];
                strcpy(data, other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    // Destructor
    virtual ~String() {
        delete[] data;
    }

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        if (s.data) {
            os << s.data;
        }
        return os;
    }

    // Input stream operator
    friend std::istream& operator>>(std::istream& is, String& s) {
        char buffer[1000];
        is >> buffer;
        s = String(buffer);
        return is;
    }

    const char* getData() const {
        return data;
    }
};

class DigitString : public String {
public:
    // Default constructor
    DigitString() : String() {}

    // Constructor from C-string
    DigitString(const char* str) {
        if (isDigitString(str)) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

    // Copy constructor
    DigitString(const DigitString& other) : String(other) {}

    // Assignment operator
    DigitString& operator=(const DigitString& other) {
        if (this != &other) {
            String::operator=(other);
        }
        return *this;
    }

    // Input stream operator
    friend std::istream& operator>>(std::istream& is, DigitString& s) {
        char buffer[1000];
        is >> buffer;
        if (isDigitString(buffer)) {
            s = DigitString(buffer);
        } else {
            std::cerr << "Invalid input: string must contain digits only.\n";
            s = DigitString();  // Reset to empty
        }
        return is;
    }

private:
    static bool isDigitString(const char* str) {
        if (!str) return false;
        for (int i = 0; str[i]; ++i) {
            if (!isdigit(str[i])) return false;
        }
        return true;
    }
};

// Testing
int main() {
    String s1("Hello");
    String s2 = s1;

    std::cout << "s1: " << s1 << "\ns2 (copy of s1): " << s2 << "\n";

    DigitString d1("12345");
    DigitString d2;
    std::cout << "Enter a digit-only string: ";
    std::cin >> d2;

    std::cout << "d1: " << d1 << "\nd2: " << d2 << "\n";

    return 0;
}
