#pragma once
#include "Observer.h"


template<typename enumEvents,typename subject>
class Subject
{
public:
    void addObserver(Observer<enumEvents,subject>* observer);
    void removeObserver(Observer<enumEvents, subject>* observer);


protected:
    void notify(const subject&entity, enumEvents event);

private:
    Observer<enumEvents, subject>* m_Observers[10];
    int m_NumObservers{ 0 };
};

template<typename enumEvents, typename subject>
void Subject<enumEvents, subject>::addObserver(Observer<enumEvents, subject>* observer)
{
    m_Observers[m_NumObservers] = observer;
    ++m_NumObservers;
}

template<typename enumEvents, typename subject>
void Subject<enumEvents, subject>::removeObserver(Observer<enumEvents, subject>* observer)
{
    for (int i = 0; i < m_NumObservers; i++)
    {
        if (m_Observers[i] == observer)
        {
            delete m_Observers[i];
            m_Observers[i] = m_Observers[m_NumObservers];
            --m_NumObservers;
        }
    }
    m_Observers[m_NumObservers] = observer;
    --m_NumObservers;
}

template<typename enumEvents, typename subject>
inline void Subject<enumEvents, subject>::notify(const subject& entity, enumEvents event)
{
    for (int i = 0; i < m_NumObservers; i++)
    {
        m_Observers[i]->onNotify(entity, event);
    }
}

