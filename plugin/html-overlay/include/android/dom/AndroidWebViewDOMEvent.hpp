/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Common.hpp"
#include "minko/dom/AbstractDOMElement.hpp"
#include "minko/dom/AbstractDOMEvent.hpp"

namespace android
{
    namespace dom
    {
        class AndroidWebViewDOMEvent : public virtual minko::dom::AbstractDOMEvent
        {
        public:
            typedef std::shared_ptr<AndroidWebViewDOMEvent> Ptr;

        protected:
            AndroidWebViewDOMEvent(const std::string& type, minko::dom::AbstractDOMElement::Ptr target) :
                _type(type),
                _target(target)
            {
            }

        public:
            static
            Ptr
            create(const std::string& type, minko::dom::AbstractDOMElement::Ptr target)
            {
                Ptr event(new AndroidWebViewDOMEvent(type, target));
                return event;
            }

            std::string
            type();

            minko::dom::AbstractDOMElement::Ptr
            target();

            void
            preventDefault();

            void
            stopPropagation();
        private:
            std::string _type;
            minko::dom::AbstractDOMElement::Ptr _target;
        };
    }
}