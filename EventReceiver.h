//
//  EventReceiver.h
//  event
//
//  Created by  on 4/10/12.
//  Copyright (c) 2012 アップルジャパン株式会社. All rights reserved.
//

#pragma once

#include <functional>
#include "Event.h"
#include "ReceiverBase.h"

namespace events {
    template <class _Tp, class _Ep>
    class EventReceiver : public ReceiverBase {
        // EventSender からのみインスタンス化を許す
        friend class EventSender;
        
    public:
        ~EventReceiver() {}
        
    private:
        EventReceiver(EventType type, _Tp* target, void (_Tp::*function)(_Ep*)) : mTarget(target), mMemFun(function){};
        
        void invoke(Event& evt) {
            // EventSender の invoke メソッドの引数は Event 型であり
            // ダウンキャスト成功が保証されているので null チェックはしない.
            _Ep* e = dynamic_cast<_Ep*>(&evt);
            mMemFun(mTarget, e);
        }
        
        std::mem_fun1_t<void, _Tp, _Ep*> mMemFun;
        _Tp* mTarget;
    };
}