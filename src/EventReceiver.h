/* =====================================================
 Copyright (c) 2012 Satoshi Takano
 
 The MIT License
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ===================================================== */

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