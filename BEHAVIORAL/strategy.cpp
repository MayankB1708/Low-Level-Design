#include<bits/stdc++.h>
using namespace std;

class PaymentStrategy{
    public:
    virtual void processPayment()=0;
    ~PaymentStrategy() {}
};

class CreditCardPayment:  public PaymentStrategy{
    public:
    void processPayment() override{
        cout<<"Processing CreditCard Payment"<<endl;
    }
};

class PaypalPayment:  public PaymentStrategy{
    public:
    void processPayment() override{
        cout<<"Processing Paypal Payment"<<endl;
    }
};

class CryptoPayment:  public PaymentStrategy{
    public:
    void processPayment() override{
        cout<<"Processing Crypto Payment"<<endl;
    }
};

class StripePayment:  public PaymentStrategy{
    public:
    void processPayment() override{
        cout<<"Processing Stripe Payment"<<endl;
    }
};

class PaymentProcessor{
    private:
    PaymentStrategy* ps;
    
    public:
    PaymentProcessor(){
        ps=nullptr;
    }
    PaymentProcessor(PaymentStrategy* strategy){
        ps=strategy;
    }
    void setPS(PaymentStrategy* strategy){
        ps=strategy;
    }
    void processPayment(){
        if(ps) ps->processPayment();
        else cout<<"No Payment Strategy selected"<<endl;
    }
};

int main(){
    PaymentStrategy* cc=new CreditCardPayment();
    PaymentStrategy* pp=new PaypalPayment();
    PaymentStrategy* cp=new CryptoPayment();
    PaymentStrategy* st=new StripePayment();

    PaymentProcessor processor;
    processor.processPayment();

    processor.setPS(cc);
    processor.processPayment();

    processor.setPS(pp);
    processor.processPayment();

    processor.setPS(cp);
    processor.processPayment();

    processor.setPS(st);
    processor.processPayment();

    delete cc;
    delete pp;
    delete cp;
    delete st;

    return 0;

}