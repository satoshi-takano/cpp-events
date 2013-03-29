#include "src/Event.h"
#include "src/EventSender.h"
#include "src/EventReceiver.h"

using namespace events;

class TestReceiver {
public:
    void receiveEvent(Event* event) {
        printf("received an event - event type : %ld\n", event->getEventType());
    }
};

int main(int argc, const char *argv[]) {
    Event event_0(0);
    Event event_1(1);
    
    EventSender* sender = new EventSender();
    TestReceiver* receiver = new TestReceiver();
    sender->addReceiver(0, receiver, &TestReceiver::receiveEvent);
    sender->addReceiver(1, receiver, &TestReceiver::receiveEvent);
    
    printf("I'll send event_0...\n");
    sender->invoke(event_0);
    printf("I'll send event_1...\n");
    sender->invoke(event_1);
    
    delete sender;
    delete receiver;
}