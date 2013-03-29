//
//  EventSender.h
//  event
//
//  Created by  on 4/10/12.
//  Copyright (c) 2012 アップルジャパン株式会社. All rights reserved.
//

#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>

#include "Event.h"
#include "ReceiverBase.h"
#include "EventReceiver.h"

namespace events {
    
    class EventSender {
    public:
        EventSender() {
            mReceiver = new std::map<int, std::vector<ReceiverBase*>* >();
        };
        virtual ~EventSender() {
            std::map<int, std::vector<ReceiverBase*>* >::iterator it;
            for (it = mReceiver->begin(); it != mReceiver->end(); ++it) {
                std::pair<int, std::vector<ReceiverBase*>* > pair = *it;
                std::vector<ReceiverBase*>* vec = pair.second;
                std::vector<ReceiverBase*>::iterator vecit;
                for (vecit = vec->begin(); vecit != vec->end(); ++vecit) {
                    ReceiverBase* receiver = *vecit;
                    delete receiver;
                }
                delete vec;
            }
            delete mReceiver;
        };
        
        template <class T, class E> void addReceiver(EventType eventType, T* receiver, void (T::*function)(E*))
        {
            std::vector<ReceiverBase*>* receivers;
            
            if (mReceiver->count(eventType)) {
                receivers = mReceiver->at(eventType);
            } else {
                receivers = new std::vector<ReceiverBase*>();
                mReceiver->insert(std::map<EventType, std::vector<ReceiverBase*>* >::value_type(eventType, receivers));
            }
            EventReceiver<T, E>* base = new EventReceiver<T, E>(eventType, receiver, function);
            receivers->push_back(base);
        }
        
        template <class T, class E> void removeReceivers(EventType eventType, T* receiver, void (T::*function)(E*))
        {
            if (mReceiver->count(eventType)) {
                std::vector<ReceiverBase*>* receivers;
                receivers = mReceiver->at(eventType);
                std::vector<ReceiverBase*>::iterator it;
                for (it = receivers->begin(); it != receivers->end(); ++it) {
                    ReceiverBase* base = *it;
                    EventReceiver<T, E>* source = static_cast<EventReceiver<T, E>*>(base);
                    int b = source->mTarget == receiver;
                    if (b) {
                        receivers->erase(it);
                        delete base;
                        if (receivers->size() == 0) {
                            delete mReceiver->at(eventType);
                            mReceiver->erase(eventType);
                        }
                        return;
                    }
                }
            }
        }
        
        void invoke(Event& event) {
            std::vector<ReceiverBase*>* receivers;
            if (mReceiver->count(event.getEventType())) {
                receivers = mReceiver->at(event.getEventType());
                // handler で removeReceiver されるた場合, ここ iterator で回すと clash する.
                for (int i = 0, len = receivers->size(); i < len; i++) {
                    ReceiverBase* receiver = receivers->at(i);
                    event.setTarget(receiver->getObserver());
                    receiver->invoke(event);
                }
            }
        };
        
    private:
        std::map<int, std::vector<ReceiverBase*>* >* mReceiver;
    };

}