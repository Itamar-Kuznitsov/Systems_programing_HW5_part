#pragma once
#include <iostream>
#include <vector>
using namespace std;



/**
 * @about: This is the MagicalContainer.cpp header file - Task 5 | part B.
 *         - Systems programing course N.2
 * @author: Itamar Kuznitsov.
 * @since: Jun. 2023
*/



namespace ariel{

class MagicalContainer{
    private:
    // data vector
    vector<int> main_container;
    // vectors of indexs
    vector<int*> ascending_container;
    vector<int*> prime_container;
    vector<int*> cross_container;

    public:
    MagicalContainer() = default;
    MagicalContainer(const MagicalContainer& other);
    MagicalContainer(MagicalContainer&& other) noexcept;
    MagicalContainer& operator=(MagicalContainer&& other) noexcept;
    MagicalContainer& operator=(const MagicalContainer& other);

    
    ~MagicalContainer();
    void addElement(int);
    void removeElement(int);
    int size() const;

    // assistance functions 
    void update_ascending_container(int*);
    void update_prime_container(int*);
    void update_cross_container();
    bool isPrime(int);
    void cross_sort();



    // iterators:
    class AscendingIterator{
    private:
        MagicalContainer& container;
        int indx;
    public:
        AscendingIterator(MagicalContainer& cont);
        AscendingIterator(MagicalContainer& cont, int indx);
        AscendingIterator(AscendingIterator&& other) noexcept;
        AscendingIterator& operator=(AscendingIterator&& other) noexcept;
        AscendingIterator(AscendingIterator& other);
        ~AscendingIterator() = default; 

        AscendingIterator& operator=(const AscendingIterator& other);
        bool operator==(AscendingIterator& other);
        bool operator!=(AscendingIterator& other);
        bool operator>(AscendingIterator& other);
        bool operator<(AscendingIterator& other);
        int operator*();
        AscendingIterator& operator++();
        AscendingIterator begin();
        AscendingIterator end();
    };


    class PrimeIterator{
        private:
            MagicalContainer& container;
            int indx;
        public:
            PrimeIterator(MagicalContainer& cont);
            PrimeIterator(PrimeIterator& other);
            PrimeIterator(MagicalContainer&, int);
            PrimeIterator(PrimeIterator&& other) noexcept;
            PrimeIterator& operator=(PrimeIterator&& other) noexcept;
            ~PrimeIterator() = default; 

            PrimeIterator& operator=(const PrimeIterator& other);
            bool operator==(PrimeIterator& other);
            bool operator!=(PrimeIterator& other);
            bool operator>(PrimeIterator& other);
            bool operator<(PrimeIterator& other);
            int operator*();
            PrimeIterator& operator++();
            PrimeIterator begin();
            PrimeIterator end();
    };


    class SideCrossIterator{
    private:
        MagicalContainer& container;
        int indx;
    public:
        SideCrossIterator(MagicalContainer& cont);
        SideCrossIterator(SideCrossIterator& other);
        SideCrossIterator(MagicalContainer&, int);
        SideCrossIterator(SideCrossIterator&& other) noexcept;
        SideCrossIterator& operator=(SideCrossIterator&& other) noexcept;
        ~SideCrossIterator() = default; 

        SideCrossIterator& operator=(const SideCrossIterator& other);
        bool operator==(SideCrossIterator& other);
        bool operator!=(SideCrossIterator& other);
        bool operator>(SideCrossIterator& other);
        bool operator<(SideCrossIterator& other);
        int operator*();
        SideCrossIterator& operator++();
        SideCrossIterator begin();
        SideCrossIterator end();
    };

};
}

// end of program