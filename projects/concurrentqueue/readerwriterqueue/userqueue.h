#pragma once

template <typename T>
class UserQueue
{
 public:
    void enqueue(T element)
    {
        elements.push_back(element);
    }

    T dequeue()
    {
        T element = elements.front();
        elements.erase(elements.begin());
        return element;
    }

 private:
    std::vector<T> elements;
};