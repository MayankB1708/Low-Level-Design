#include<bits/stdc++.h>
using namespace std;

class subscriber{
    public:
    virtual void update(const string& video) = 0;
    virtual ~subscriber()=default;
};

class YoutubeSubscriber: public subscriber{
    private:
    string name;
    
    public:
    YoutubeSubscriber(const string& name){
        this->name=name;
    }

    void update(const string& video) override{
        cout<<name<<" is watching the video "<<video<<endl;
    }
};

class EmailSubscriber: public subscriber{
    private:
    string email;
    
    public:
    EmailSubscriber(const string& email){
        this->email=email;
    }

    void update(const string& video) override{
        cout<<"Sending email to "<<email<<": New video uploaded: "<<video<<endl;
    }
};

class PushnotificationSubscriber: public subscriber{
    private:
    string device;
    
    public:
    PushnotificationSubscriber(const string& device){
        this->device=device;
    }

    void update(const string& video) override{
        cout<<"Sending push notification to "<<device<<": New video uploaded: "<<video<<endl;
    }
};

class YoutubeChannel{
    public:
    virtual void addSubscriber(subscriber* s)=0;
    virtual void removeSubscriber(subscriber* s)=0;
    virtual void notifySubscribers()=0;
    virtual ~YoutubeChannel()=default;
};

class YoutubeChannelImpl: public YoutubeChannel{
    private:
    unordered_set<subscriber*> subscribers;
    string video;

    public:
    void addSubscriber(subscriber* s) override{
        subscribers.insert(s);
    }
    void removeSubscriber(subscriber* s) override{
        subscribers.erase(s);
    }
    void notifySubscribers() override{
        for(auto sub:subscribers){
            sub->update(video);
        }
    }
    void uploadvideo(const string& video){
        this->video=video;
        notifySubscribers();
    }
};

int main(){
    YoutubeChannelImpl channel;
    subscriber* alice=new YoutubeSubscriber("Alice");
    subscriber* bob=new EmailSubscriber("bob@gmail.com");
    subscriber* phone=new PushnotificationSubscriber("iPhone");

    channel.addSubscriber(alice);
    channel.addSubscriber(bob);
    channel.addSubscriber(phone);

    channel.uploadvideo("LLD is interesting.....");
    cout<<"-------------Removing bob------------"<<endl;
    channel.removeSubscriber(bob);
    cout<<"-------------Removing alice------------"<<endl;
    channel.removeSubscriber(alice);
    cout<<"-------------Removing device------------"<<endl;
    channel.removeSubscriber(phone);

    delete alice;
    delete bob;
    delete phone;

    return 0;
}