#include <vector>
#include <algorithm>
#include <stdexcept>

template <class T>
class MaxHeap
{
public:
    MaxHeap() {} // initialize empty heap

    void insert(T value)
    {
        heap.push_back(value); // append value to the end of the heap
        int currentIndex = heap.size() - 1; // index of the last element

        /**
         * Ensure the maximum heap attribute of the heap. It will continue as long as the current element 
         * (heap[currentIndex]) is larger than its parent element (heap[parent(currentIndex)])
         */
        while (currentIndex > 0 && heap[currentIndex] > heap[parent(currentIndex)])
        {
            /**
             * if the current element is larger than its parent element, swap them
             */
            std::swap(heap[currentIndex], heap[parent(currentIndex)]);
            currentIndex = parent(currentIndex);
        }
    }

    T extract() // remove the maximum value from the heap
    {
        // check if the heap is empty
        if (heap.size() == 0)
        {
            throw std::runtime_error("Heap is empty");
        }
        T maxValue = heap[0];  // the maximum value is the first element
        heap[0] = heap.back(); // replace the first element with the last element
        heap.pop_back();       // remove the last element
        heapify(0);            // ensure the maximum heap attribute of the heap
        return maxValue;
    }

    int count() const
    {
        return heap.size(); // return the number of elements in the heap
    }

private:
    std::vector<T> heap;

    int parent(int index) { return (index - 1) / 2; }

    int leftChild(int index) { return 2 * index + 1; }

    int rightChild(int index) { return 2 * index + 2; }

    void heapify(int index)
    {
        // Maintain the properties of the largest heap when removing elements or resizing the heap
        int left = leftChild(index);
        int right = rightChild(index);
        int largest = index;

        if (left < heap.size() && heap[left] > heap[index])
        {
            /**
             * if the left child is larger than the current element, set the left child as the largest element
             */
            largest = left;
        }
        if (right < heap.size() && heap[right] > heap[largest])
        {
            /**
             * if the right child is larger than the current element, set the right child as the largest element
             */
            largest = right;
        }

        if (largest != index)
        {
            /**
             * if the largest element is not the current element, swap them
             */
            std::swap(heap[index], heap[largest]);
            heapify(largest);
        }
    }
};
