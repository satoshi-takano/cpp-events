//
//  Header.h
//  event
//
//  Created by  on 4/10/12.
//  Copyright (c) 2012 アップルジャパン株式会社. All rights reserved.
//

#pragma once

#include "Event.h"

namespace events {
    
    class ReceiverBase {
        friend class EventSender;
        
    public:
        ReceiverBase(){}
        virtual ~ReceiverBase(){}
        void* getObserver() const
        {
            return mObserver;
        }
    private:
        virtual void invoke(Event& evt) = 0;
        void* mObserver;
    };
    
}