#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

template <typename Comparable>
class OrderedCollection
{
public:
    bool isEmpty()
    {
        return size == 0;
    }

    void makeEmpty()
    {
        delete[] data;
        size = 0;
        max_size = 2;
        data = new Comparable[max_size];
    }

    void insert(Comparable element)
    {
        if (size == max_size)
        {
            Comparable *new_data = new Comparable[max_size * 2];
            for (int i = 0; i < size; i++)
            {
                new_data[i] = data[i];
            }
            data = new_data;
            max_size *= 2;
        }
        data[size] = element;
        size++;
    }

    void remove(Comparable element)
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == element)
            {
                for (int j = i + 1; j < size; j++)
                    data[j - 1] = data[j];
                size--;
                return;
            }
        }
        throw runtime_error("Element not found.");
    }

    Comparable findMax()
    {
        if (isEmpty())
            throw runtime_error("The collection is empty.");
        return *max_element(data, data + size);
    }

    Comparable findMin()
    {
        if (isEmpty())
            throw runtime_error("The collection is empty.");
        return *min_element(data, data + size);
    }

    ~OrderedCollection()
    {
        delete[] data;
    }

private:
    Comparable *data = new Comparable[2];
    int size = 0;
    int max_size = 2;
};

int main()
{
    OrderedCollection<int> test;
    test.insert(2);
    assert(test.findMin() == 2 and test.findMax() == 2);
    test.insert(1);
    assert(test.findMin() == 1 and test.findMax() == 2);
    test.insert(3);
    assert(test.findMin() == 1 and test.findMax() == 3);
    test.remove(1);
    assert(test.findMin() == 2 and test.findMax() == 3);
    cout << "Tests passed.\n";
}