#include <iostream>
#include <string>
#include <map>
#include <vector>

class Error {
    std::string inf;
public:
    Error(std::string str) {
        inf = str;
    }
    std::string what() {
        return inf;
    }
};


class Base {
protected:
    int value;
public:
    Base(int val) :value(val) {}
    virtual void show() = 0;
};

class A :public Base {
public:
    A(int val) :Base(val) {}
    void show() { std::cout << "class A: " << value << '\n';}
};

class B :public Base {
public:
    B(int val) :Base(val) {}
    void show() { std::cout << "class B: " << value << '\n'; }
};

class C :public Base {
public:
    C(int val) :Base(val) {}
    void show() { std::cout << "class C: " << value << '\n'; }
};

std::vector<Base* > List;

class Functor {
public:
    virtual void operator()() {};
    virtual void operator()(std::string, int) {};
};

class FunctorShow :public Functor {
public:
    FunctorShow() {};
    void operator() ();
};

class FunctorCreate :public Functor {
public:
    FunctorCreate() {};
    void operator()(std::string classname, int value);
};

std::map <int, Functor*> mfunc;

int main() {
    try {
        Functor* FS = new FunctorShow;
        Functor* FC = new FunctorCreate;
        mfunc[0] = FS;
        mfunc[1] = FC;
        
        size_t N;
        std::cin >> N;
        for (size_t i = 0; i < N; i++) {
            std::string str;
            std::cin >> str;
            if (str == "create") {
                std::string classname;
                int val;
                std::cin >> classname >> val;
                Functor* ptr1 = mfunc[1];
                (*ptr1)(classname, val);
            }
            else if (str == "showall") {
                Functor* ptr2 = mfunc[0];
                (*ptr2)();
            }
        }
    }
    catch (Error& e) {
        std::cout << e.what() << '\n';
    }
    
    system("pause");
    return 0;
}

void FunctorCreate::operator() (std::string classname, int value) {
    Base* base;
    if (classname == "A")
        base = new A(value);
    else if (classname == "B")
        base = new B(value);
    else if (classname == "C")
        base = new C(value);
    else throw Error("NO such class");
    List.push_back(base);
}

void FunctorShow::operator() () {
    for (size_t i = 0; i < List.size(); i++)
        List[i]->show();
}