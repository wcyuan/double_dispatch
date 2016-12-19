#include <iostream>
/**
 * Double dipatch involves two object hierarchies.  One is the
 * Host, one is the Visitor.  The problem is to have a function
 * that takes one Host and one Visitor, and whose behavior depends
 * on the dynamic types of both objects.
 *
 * If it depended only on the compile-time type, then function
 * overloading solves the problem.  If it depended only on the
 * dynamic type of one object, then a virtual method solves the
 * problem.
 * https://en.wikipedia.org/wiki/Double_dispatch
 *
 *
 * Compile with:
 * g++ -std=c++0x double_dispatch.cc
 * Run with:
 * ./a.out
 */

// -------------------------------------------------
// Host
//
// Since Host and Visitor refer to one another, we
// have to define things in a particular order.
//  - First forward declare the empty class Visitor
//  - Then declare Host, including all methods
//  - Then define Visitor
//  - Then define Host.
class Visitor;

class Host {
  public:
    virtual void AcceptVisitor(Visitor& visitor);
};

// Every subclass has to override AcceptVisitor even though
// the definitions are exactly the same.
class Host1 : public Host {
  public:
    virtual void AcceptVisitor(Visitor& visitor) override;
};
class Host2 : public Host {
  public:
    virtual void AcceptVisitor(Visitor& visitor) override;
};
class Host3 : public Host {
  public:
    virtual void AcceptVisitor(Visitor& visitor) override;
};

// -------------------------------------------------
// Visitor
//
// Every Visitor class, even the Bass class, has to have
// a method for every Host class
class Visitor {
  public:
    virtual void VisitHost(Host& host) {
        ::std::cout << "Base visitor visiting base host" << ::std::endl;
    }
    virtual void VisitHost(Host1& host) {
        ::std::cout << "Base visitor visiting Host1" << ::std::endl;
    }
    virtual void VisitHost(Host2& host) {
        ::std::cout << "Base visitor visiting Host2" << ::std::endl;
    }
    virtual void VisitHost(Host3& host) {
        ::std::cout << "Base visitor visiting Host3" << ::std::endl;
    }
};

void Host::AcceptVisitor(Visitor& visitor) {
    visitor.VisitHost(*this);
}
void Host1::AcceptVisitor(Visitor& visitor) {
    visitor.VisitHost(*this);
}
void Host2::AcceptVisitor(Visitor& visitor) {
    visitor.VisitHost(*this);
}
void Host3::AcceptVisitor(Visitor& visitor) {
    visitor.VisitHost(*this);
}

class Visitor1 : public Visitor {
    virtual void VisitHost(Host1& host) override {
        ::std::cout << "Visitor1 visiting Host1" << ::std::endl;
    }
    virtual void VisitHost(Host2& host) override {
        ::std::cout << "Visitor1 visiting Host2" << ::std::endl;
    }
    virtual void VisitHost(Host3& host) override { 
        ::std::cout << "Visitor1 visiting Host3" << ::std::endl;
    }
};
class Visitor2 : public Visitor {
    virtual void VisitHost(Host1& host) override {
        ::std::cout << "Visitor2 visiting Host1" << ::std::endl;
    }
    virtual void VisitHost(Host2& host) override {
        ::std::cout << "Visitor2 visiting Host2" << ::std::endl;
    }
    virtual void VisitHost(Host3& host) override {
        ::std::cout << "Visitor2 visiting Host3" << ::std::endl;
    }
};
class Visitor3 : public Visitor {
    virtual void VisitHost(Host1& host) override {
        ::std::cout << "Visitor3 visiting Host1" << ::std::endl;
    }
    virtual void VisitHost(Host2& host) override {
        ::std::cout << "Visitor3 visiting Host2" << ::std::endl;
    }
    virtual void VisitHost(Host3& host) override {
        ::std::cout << "Visitor3 visiting Host3" << ::std::endl;
    }
};

// -------------------------------------------------
int main(int argc, char* argv[]) {
    Host* hosts[] = { new Host1(), new Host2(), new Host3() };
    Visitor* visitors[] = { new Visitor1(), new Visitor2(), new Visitor3() };
    for (Host* host : hosts) {
        for (Visitor* visitor : visitors) {
            // Doesn't work to tell the visitor to visit the host,
            // you have to start with the hosts.
            //
            // visitor->VisitHost(*host);
            host->AcceptVisitor(*visitor);
        }
    }
    return 0;
}

