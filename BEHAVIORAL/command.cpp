#include<bits/stdc++.h>
using namespace std;

class TV{
    public:
    void turnOn(){
        cout<<"Turning on the TV.....TV is on"<<endl;
    }
    void turnOff(){
        cout<<"Turning off the TV......TV is off"<<endl;
    }
    void changeChannel(int channel){
        cout<<"Channel changed to "<<channel<<endl;
    }
    void adjustVolume(int vol){
        cout<<"Volume set to "<<vol<<endl;
    }
};

class Command{
    public:
    virtual void execute()=0;
    virtual ~Command() =default;
};

class TurnOnCommand: public Command{
    private:
    TV *tv;

    public:
    TurnOnCommand(TV* tv){
        this->tv=tv;
    }
    void execute() override{
        tv->turnOn();
    }
};

class TurnOffCommand: public Command{
    private:
    TV* tv;

    public:
    TurnOffCommand(TV* tv){
        this->tv=tv;
    }
    void execute() override{
        tv->turnOff();
    }
};

class ChangeChannelCommand: public Command{
    private:
    TV* tv;
    int channel;

    public:
    ChangeChannelCommand(TV* tv, int channel){
        this->tv=tv;
        this->channel=channel;
    }
    void execute() override{
        tv->changeChannel(channel);
    }
};

class AdjustVolumeCommand:public Command{
    private:
    TV* tv;
    int volume;

    public:
    AdjustVolumeCommand(TV* tv, int volume){
        this->tv=tv;
        this->volume=volume;
    }
    void execute() override{
        tv->adjustVolume(volume);
    }
};

class RemoteControl{
    private:
    Command* oncommand=nullptr;
    Command* offcommand=nullptr;

    public:
    void setOnCommand(Command* cmd){
        this->oncommand=cmd;
    }
    void setOffCommand(Command* cmd){
        this->offcommand=cmd;
    }
    void pressOnButton(){
        if(oncommand) oncommand->execute();
    }
    void pressOffButton(){
        if(offcommand) offcommand->execute();
    }
};

int main(){
    TV* tv=new TV();
    Command* turnon=new TurnOnCommand(tv);
    Command* turnoff=new TurnOffCommand(tv);
    Command* changevolume=new ChangeChannelCommand(tv,10);
    Command* adjustvolume=new AdjustVolumeCommand(tv,20);

    RemoteControl* rc=new RemoteControl();
    rc->setOffCommand(turnoff);
    rc->setOnCommand(turnon);

    rc->pressOnButton();
    changevolume->execute();
    adjustvolume->execute();
    rc->pressOffButton();

    delete turnon;
    delete turnoff;
    delete changevolume;
    delete adjustvolume;
    delete rc;
    delete tv;

    return 0;
}