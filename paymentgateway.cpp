#include<bits/stdc++.h>
using namespace std;

enum class GatewayType { RAZORPAY, STRIPE };

class PaymentRequest{
    public:
    double amount;
    string userId;
    GatewayType gatewayType;
};

class PaymentResponse{
    public:
    string transactionId;
    bool isSuccess;
};

class PaymentGatewayStrategy{
    public:
    virtual PaymentResponse processPayment(const PaymentRequest& req) = 0;
    virtual ~PaymentGatewayStrategy() {}
};

class IBankingSystem{
    public:
    virtual PaymentResponse executeTransaction(const PaymentRequest& req) = 0;
    virtual ~IBankingSystem() {}
};

class HDFCBank: public IBankingSystem{
    public:
    PaymentResponse executeTransaction(const PaymentRequest& req) override{
        cout<<"HDFC executing transaction amount of Rs. "<<req.amount<<endl;
        PaymentResponse response;
        response.isSuccess=true;
        response.transactionId="TXN_HDFC_12345";
        return response;
    }
};

class RazorpayGateway: public PaymentGatewayStrategy{
    IBankingSystem* bank;
    
    public:
    RazorpayGateway(IBankingSystem* bank): bank(bank) {}

    PaymentResponse processPayment(const PaymentRequest& req) override{
        cout<<"Razorpay processing payment of amount Rs. "<<req.amount<<endl;
        return bank->executeTransaction(req);
    }
};

class RetryPaymentProxy: public PaymentGatewayStrategy{
    PaymentGatewayStrategy* realGateway;
    int maxtries;

    public:
    RetryPaymentProxy(PaymentGatewayStrategy* rg, int t): realGateway(rg), maxtries(t) {}

    PaymentResponse processPayment(const PaymentRequest& req) override{
        PaymentResponse response;
        int count=0;

        while(count<maxtries){
            cout<<"Proxy Attempt "<<count+1<<" of "<<maxtries<<endl;
            response=realGateway->processPayment(req);

            if(response.isSuccess){
                cout<<"Proxy attempt successful."<<endl;
                return response;
            }
            cout<<"Proxy attempt failed. Retrying....."<<endl;
            count++;
        }

        cout<<"Proxy max tries reached. Payment failed."<<endl;
        response.isSuccess=false;
        response.transactionId="Failed12345";
        return response;
    }
};

class GatewayFactory{
    public:
    static PaymentGatewayStrategy* getGateway(GatewayType type, int maxtries){
        IBankingSystem* bank=new HDFCBank();
        PaymentGatewayStrategy* gateway=NULL;

        if(type==GatewayType::RAZORPAY){
            gateway=new RazorpayGateway(bank);
        }
        else{
            cout<<"Stripe not implemented yet"<<endl;
        }

        return new RetryPaymentProxy(gateway,maxtries);
    }
};

class PaymentService{
    PaymentGatewayStrategy* gateway;
    
    public:
    PaymentService(): gateway(nullptr) {}

    PaymentResponse makePayment(const PaymentRequest& req){
        gateway=GatewayFactory::getGateway(req.gatewayType,3);
        if(!gateway){
            PaymentResponse response;
            response.isSuccess=false;
            response.transactionId="Failed at Gateway Creation";
            return response;
        }
        return gateway->processPayment(req);
    }
};

class PaymentController{
    PaymentService* service;
    public:
    PaymentController(){
        service=new PaymentService();
    }
    PaymentResponse processPayment(const PaymentRequest& req){
        return service->makePayment(req);
    }
};

int main(){
    PaymentController* controller=new PaymentController();
    PaymentRequest req;
    req.amount=150000;
    req.gatewayType=GatewayType::RAZORPAY;
    req.userId="User12345";

    PaymentResponse res=controller->processPayment(req);
    cout<<"Payment Result:"<<endl;
    cout<<"TransactionID: "<<res.transactionId<<endl;
    cout<<"Success: "<<(res.isSuccess ? "Yes" : "No")<<endl;

    return 0;
}