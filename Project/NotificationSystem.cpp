#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

// Notification & decorator

class INotification{
    public:
        virtual string getContent() const= 0;
        virtual ~INotification(){}
};
// Concrete notification: Simple text notification.
class SimpleNotification : public INotification{
    private:
        string text;
    public:
        SimpleNotification(const string& msg){
            text=msg;
        }
        string getContent() const override{
            return text;
        }
};
// Abstract Decorator : wraps a  Notification object.
class INotificationDecorator : public INotification{
    protected:
        INotification* notification;
    public:
        INotificationDecorator(INotification* n){
            notification=n;
        }
        virtual ~INotificationDecorator(){
            delete notification;
        }
};
// Decorator to add a timestamp to the content
class TimestampDecorator : public INotification{
    public:
        TimestampDecorator(INotification* n) : INotificationDecorator(n){}

        string gettContent() const override{
            return "[2026-06-10] 14:22:00" + notification->getContent();
        }
};
// Decorator to append a signature to the content
class SignatureDecorator: public INotificationDecorator{
    private:
        string signature;
    public:
        SignatureDecorator(INotification* n,const string& sig) : INotificationDecorator(n){
            signature= sig;
        }
        string getContent() const override{
            return notification->getContent() + "\n--"+signature+"\n\n";
        }
};

// Observer pattern Components
// Observer interface: each observer gets an update with a notification pointer.
class IObserver{
    public:
        virtual void~update()= 0;
        virtual ~IObserver(){}
};
class IObservable{
    public:
        virtual void addObserver(IObserver* observer) = 0;
        virtual void removeObserver(IObserver* observer)= 0;
        virtual void notifyObservers() = 0;
};
// Concrete observable
class NotificationObservable: public IObservable{
    private:
        vector<IObserver*> observers;
        INotification* currentNotification;
    public:
        NotificationObservable(){
            currentNotification= nullptr;
        }
        void addObserver(IObserve* obs) override{
            observers.push_back(obs);
        }
        void removeObserver(IObserver* obs) override{
            observers.erase(remove(observers.begin(),observers.end(),obs),observers.end());
        }
        void notifyObservers() override{
            for(unsigned int i=0;i<observers.size();i++){
                observers[i]->update();
            }
        }
        void setNotification(INotification* notification){
            if(currentNotification !=nullptr){
                delete currentNotification;
            }
            currentNotification= notification;
            notifyObservers();
        }
        INOtification* getNotification(){
            return currentNotification;
        }
        string getNotificationContent(){
            return currentNotification->getContent();
        }
        ~NotificationObservable(){
          if(currentNotification!= NULL){
            delete currentNotification;
          }
        }
};
// Concrete  Observer 1
class Logger: public IObserver{
    private:
        NotificationObservable* NotificationObservable;
    public:
        Logger(NotificationObservable* observable){
            this->NotificationObservable= observable;
        }
        void update(){
            cout<<"Logging new notification: \n" << NotificationObservable->getNotificationContent();
        }
};
// Strategy pattern component( COncrete observer 2)
// Abstract class for different Notification strategies.
class INotificationStrategy{
    public:
        virtual void sendNotification(string content)= 0;
};
class EmailStrategy : publicINotificationStrategy{
    private:
        string emailId;
    public:
        EmailStrategy(string emailId){
            this->emailId= emailId;
        }
        void sendNotification(string content) override{
            // Simulate the process of sending an email notification
            // Representing bthe dispatch of messages to users via email
            cout<<"Sending email notification to "<<emailId<<"\n" <<content;
        }
};

class SMSStrategy : public INotificationStrategy{
    private:
        string mobileNumber;
    public:
        SMSStrategy(string mobileNumber){
            this->mobileNumber=mobileNumber;
        }
        void sendNotification(string content) override {
            // Simulate the process of sending an SMS notification,
            // Representing the dispatch of messages to users via SMS.
            cout<<"Sending SMS notification to:"<<mobileNumber<< "\n "<< content;
        }
};
class PopUpStrategy : public INotificationStrategy{
    public:
        void sendNotification(string content) override{
            // simulate the process of sending popup notification
            cout<<"Sending popUp notification:\n" << content;
        }
};
class NotificationEngine : public IObserver{
    private:
        NotificationObservable* NotificationObservable;
        vector<INotificationStrategy*>notificationStrategies;
    public:
        void addNotificationStrategy(INotificationStrategy* ns){
            this->notificationStrategies.push_back(ns);
        }
        // Can have RemoveNotification strategy as well
        void update(){
            string notificationContent= NotificationObservable->getNotificationContent();
            for(const auto notificationStrategy : notificationStrategies){
                notificationStrategy->sendNotification(notificationContent);
            }
        }
};
// NotificationService

// The NotificationService manages notifications. It keeps track of notifications.
// Any client code will interact with this service.

//Singleton class
class NotificationService{
    private:
        NotificationObservable* observable;
        static NotificationService* instance;
        vector<INotification*>notifications;

        NotificationService(){
            // Private constructor
            observable = new NotificationObservable();
        }
    public:
        static NotificationService* getInstance(){
            if(instance==nullptr){
                instance= new NotificationService();
            }
            return instance;
        }
        // Expose the observable so observers can attach
        NotificationObservable* getObservable(){
            return observable;
        }
        // creates a new notification and notifiers observers
        void sendNotification(INotification* notification){
            notifications.push_back(notification);
            observable->setNotification(notification);
        }
        ~NotificationService(){
            delete observable;
        }
};
NotificationService* NotificationService::instance = nullptr;

int main(){
    // Create notification service
    NotificationService* NotificationService= NotificationService::getInstance();
    // GetObservable
    NotificationObservable* notificationObservable = NotificationService->getObservable();
    // create logger Observer
    Logger* logger= new Logger(notificationObservable);
    // create notificationEngine observers
    NotificationEngine* NotificationEngine= new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(new EmailStrategy("kishan@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+ 9569324690"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

     // Attach these observers
     notificationObservable->addObserver(logger);
     notificationObservable->addObserver(notificationEngine);

     // Create a notification with decorators.
     INotification* notification= new SimpleNotification("Your order has been shipped!");
     notification= new TimestampDecorator(notification);
     notification=new SignatureDecorator(notification,"customer care");

     notificationService->sendNotification(notification);
     delete logger;
     delete NotificationEngine;
     
     return 0;

}