#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Abstract Observer Interface
class ISubscriber {
public:
    virtual void update() = 0;
    virtual ~ISubscriber() {}
};

// Abstract Observable Interface
class IChannel {
public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subscriber) = 0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {}
};

// Concrete Subject
class Channel : public IChannel {
private:
    vector<ISubscriber*> subscribers;
    string name;
    string latestVideo;

public:
    Channel(const string& name) {
        this->name = name;
    }

    void subscribe(ISubscriber* subscriber) override {
        if (find(subscribers.begin(), subscribers.end(), subscriber) ==
            subscribers.end()) {
            subscribers.push_back(subscriber);
        }
    }

    void unsubscribe(ISubscriber* subscriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);

        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void notifySubscribers() override {
        for (ISubscriber* sub : subscribers) {
            sub->update();
        }
    }

    void uploadVideo(const string& title) {
        latestVideo = title;

        cout << "\n[" << name
             << " uploaded \"" << title
             << "\"]\n";

        notifySubscribers();
    }

    string getVideoData() {
        return latestVideo;
    }
};

// Concrete Observer
class Subscriber : public ISubscriber {
private:
    string name;
    Channel* channel;

public:
    Subscriber(const string& name, Channel* channel) {
        this->name = name;
        this->channel = channel;
    }

    void update() override {
        cout << "Hey " << name
             << ", New video uploaded: "
             << channel->getVideoData()
             << endl;
    }
};

int main() {

    // Create channel
    Channel* channel = new Channel("Up_Bihari_Trader");

    // Create subscribers
    Subscriber* subs1 = new Subscriber("Kishan", channel);
    Subscriber* subs2 = new Subscriber("Rahul", channel);

    // Subscribe
    channel->subscribe(subs1);
    channel->subscribe(subs2);

    // Upload first video
    channel->uploadVideo("Trading Related Tutorial");

    // Kishan unsubscribes
    channel->unsubscribe(subs1);

    // Upload second video
    channel->uploadVideo("Decorator Pattern Tutorial");

    // Cleanup
    delete subs1;
    delete subs2;
    delete channel;

    return 0;
}