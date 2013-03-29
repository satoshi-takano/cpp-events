//
//  Header.h
//  event
//
//  Created by  on 4/10/12.
//  Copyright (c) 2012 アップルジャパン株式会社. All rights reserved.
//

#pragma once

namespace events {
    
    typedef unsigned long EventType;
    
    class Event {
    public:
        Event(EventType type) : mType(type){}
        virtual ~Event(){}
        
        const EventType getEventType() const
        {
            return mType;
        }
        
        void setTarget(void* target)
        {
            mTarget = target;
        }
        
    private:
        EventType mType;
        void* mTarget;
    };
    
}