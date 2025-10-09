#include<bits/stdc++.h>
using namespace std;

class car{
    public:
    class carbuilder{
        private:
        string engine="V8";
        int wheels=4;
        int seats=5;
        string color="black";
        bool sr=false;
        bool ns=false;

        friend class car; // carbuilder can access private members of the car class bcoz it is inside the car clas but
        //car class to access the private members of the builder class the car class should be a friend class

        public:
        carbuilder& setengine(const string &eng){
            this->engine=eng;
            return *this;
        }
        carbuilder& setwheels(int w){
            this->wheels=w;
            return *this;
        }
        carbuilder& setseats(int s){
            this->seats=s;
            return *this;
        }
        carbuilder& setcolor(const string &c){
            this->color=c;
            return *this;
        }
        carbuilder& setsr(bool sr){
            this->sr=sr;
            return *this;
        }
        carbuilder& setns(bool ns){
            this->ns=ns;
            return *this;
        }

        car build(){
            return car(*this);
        }
    };
    private:
    string engine;
    int wheels;
    int seats;
    string color;
    bool sr;
    bool ns;

    car(const carbuilder& builder){
        this->engine=builder.engine;
        this->wheels=builder.wheels;
        this->seats=builder.seats;
        this->color=builder.color;
        this->sr=builder.sr;
        this->ns=builder.ns;
    }
    public:
    string getengine() const{
        return this->engine;
    }
    int getwheels() const{
        return this->wheels;
    }
    int getseats() const{
        return this->seats;
    }
    string getcolor() const{
        return this->color;
    }
    bool getsr() const{
        return this->sr;
    }
    bool getns() const{
        return this->ns;
    }

    void print() const{
        cout << "Car [engine=" << engine
             << ", wheels=" << wheels
             << ", seats=" << seats
             << ", color=" << color
             << ", sunroof=" << (sr ? "true" : "false")
             << ", navigationSystem=" << (ns ? "true" : "false")
             << "]" << endl;
    }

    
};

int main() {
    car::carbuilder builder;
    car car1 = builder.setengine("V8").setcolor("Red").setseats(5).setsr(true).build();
    car1.print();

    car car2 = builder.setengine("V6").setcolor("Blue").setseats(4).build();
    car2.print();

    return 0;
}