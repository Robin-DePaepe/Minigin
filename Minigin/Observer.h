#pragma once

namespace minigin
{
    template<typename enumEvents, typename subject>
    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void onNotify(const subject& entity, enumEvents event) = 0;
    };
}