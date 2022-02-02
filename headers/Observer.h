#ifndef OOP_PROJECT_OBSERVER_H
#define OOP_PROJECT_OBSERVER_H

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(int _score) = 0;
};

class Subject
{
public:
    virtual ~Subject() = default;
    virtual void add(Observer* o) = 0;
    virtual void remove(Observer* o) = 0;
    virtual void notify() = 0;
};

#endif
