#include <algorithm>
#include "MagicalContainer.hpp"
using namespace std;
using namespace ariel;


/**
 * @about: This is the MagicalContainer.cpp implemantation file - Task 5 | part B.
 *         - Systems programing course N.2
 * @author: Itamar Kuznitsov.
 * @since: Jun. 2023
*/



// copy constructor
MagicalContainer::MagicalContainer(const MagicalContainer& other) {
    this->main_container = other.main_container;
    this->ascending_container = other.ascending_container;
    this->prime_container = other.prime_container;
    this->cross_container = other.cross_container;
}

// copy assignment operator
MagicalContainer& MagicalContainer::operator=(const MagicalContainer& other) {
    if (this != &other) {
        this->main_container = other.main_container;
        this->ascending_container = other.ascending_container;
        this->prime_container = other.prime_container;
        this->cross_container = other.cross_container;
    }
    return *this;
}

// move assignment operator
MagicalContainer& MagicalContainer::operator=(MagicalContainer&& other) noexcept {
    if (this != &other) {
        this->main_container = move(other.main_container);
        this->ascending_container = move(other.ascending_container);
        this->prime_container = move(other.prime_container);
        this->cross_container = move(other.cross_container);
    }
    return *this;
}


// move constructor
MagicalContainer::MagicalContainer(MagicalContainer&& other) noexcept {
    this->main_container = move(other.main_container);
    this->ascending_container = move(other.ascending_container);
    this->prime_container = move(other.prime_container);
    this->cross_container = move(other.cross_container);
}

// destructor
MagicalContainer:: ~MagicalContainer(){
    // free all inamic pointers that was allocated
    for(int* item : ascending_container){
        delete item;
    }
}


// adding number to the MegicalContiner
void MagicalContainer:: addElement(int element) {
    // add data to the main container
    this->main_container.push_back(element);
    // get a pointer to the newly pushed element
    int* pointer_to_element = new int(this->main_container.back());

    // update all indexs vectors 
    update_ascending_container(pointer_to_element);
    update_cross_container();
    if(isPrime(element))
        update_prime_container(pointer_to_element);
}


// remonving number from the MegicalContiner
void MagicalContainer:: removeElement(int element) {
    // find the iterator pointing to the item to delete in the main container vector
    auto deleteIterator = find(this->main_container.begin(), this->main_container.end(), element);  
    if (deleteIterator != this->main_container.end()) {
        // find the elements adress 
        int* element_pointer = nullptr;
        for(int* item : this->ascending_container){
            if (*item == element){
                element_pointer = item;
            }
        }
        
        // remove the item(data) from the main vector
        this->main_container.erase(deleteIterator);
       
        // find the pointer in the ascending vector and remove it
        auto deleteAscendingIterator = find(this->ascending_container.begin(), this->ascending_container.end(), element_pointer);
        if (deleteAscendingIterator != this->ascending_container.end()) {
            // Remove the item from the ascending vector
            this->ascending_container.erase(deleteAscendingIterator);
            delete element_pointer; // delete the dynamically allocated pointer
        }

        // find the pointer in the prime vector and remove it
        auto deletePrimeIterator = find(this->prime_container.begin(), this->prime_container.end(), element_pointer);
        if (deletePrimeIterator != this->prime_container.end()) {
            // Remove the item from the prime_container vector
            this->prime_container.erase(deletePrimeIterator);
            delete element_pointer; // delete the dynamically allocated pointer
        }

        // find the pointer in the cross vector and remove it
        auto deleteCrossIterator = find(this->cross_container.begin(), this->cross_container.end(), element_pointer);
        if (deleteCrossIterator != this->cross_container.end()) {
            // Remove the item from the cross_container vector
            this->cross_container.erase(deleteCrossIterator);
            delete element_pointer; // delete the dynamically allocated pointer
            // update cross_container order
            cross_sort();
        }
    }
    // if the number isn't in the container
    else{
        throw std::runtime_error("The number was not found");
    }   
}


// return the size of the container
int MagicalContainer:: size() const {
    return this->main_container.size();
}


// add number pointers to the ascending_container and sort it
void MagicalContainer:: update_ascending_container(int* pointer_to_element){
    // add pointer to the ascending container
    this->ascending_container.push_back(pointer_to_element);
    // sort the ascending_container based on the values pointed by the int pointers - https://stackoverflow.com/questions/5122804/how-to-sort-with-a-lambda
    sort(this->ascending_container.begin(), this->ascending_container.end(), [](int* a, int* b) {
        return (*a < *b);
    });
}


// add number pointers to the prime_container and sort it - as requested in the demo
void MagicalContainer:: update_prime_container(int* pointer_to_element){
    // add pointer to the prime container
    if(isPrime(*pointer_to_element)){
        this->prime_container.push_back(pointer_to_element);
        // sort the prime_container (using lambda expresion) - https://stackoverflow.com/questions/5122804/how-to-sort-with-a-lambda
        sort(this->prime_container.begin(), this->prime_container.end(), [](int* a, int* b) {
        return (*a < *b);
        });
    }
}


// call cross_sort() to add number pointers to the cross_container in cross order.
void MagicalContainer:: update_cross_container(){
    // sort the updated main_container by cross
    cross_sort();
}


// organize cross_container in cross order
void MagicalContainer:: cross_sort(){
    this->cross_container.clear();
    size_t size = this->main_container.size(); 
    bool even = true;
    size_t b = 0;
    size_t e = size - 1;
    // run throgh all elment and add to cross_container in cross order - one from the start one from the end and so on.
    for (size_t i = 0; i < size; i++) {
        // if even
        if (even) {
            this->cross_container.push_back(&(this->main_container[b]));
            b++;
            even = false;
        }
        // if odd
        else {
            this->cross_container.push_back(&(this->main_container[e]));
            e--;
            even = true;
        }
    }
}


// return true if num is prime otherwise false. 
bool MagicalContainer:: isPrime(int num){
    if(num < 2) return false;
    if(num == 2) return true;
    if(num%2 == 0) return false;

    for(int i= 3; (i*i)<= num; i+= 2){
        if(num % i == 0)
            return false;
    }
    return true;
}




// AscendingIterator
MagicalContainer::AscendingIterator:: AscendingIterator(MagicalContainer& cont)
    : container(cont), indx(0){
}

MagicalContainer::AscendingIterator:: AscendingIterator(AscendingIterator& other)
    : AscendingIterator(other.container){
}

MagicalContainer::AscendingIterator:: AscendingIterator(MagicalContainer& cont, int indx_)
    : container(cont), indx(indx_){}

// move constructor
MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator&& other) noexcept
    : container(other.container), indx(other.indx) {
    other.indx = 0;
}

// move assignment operator
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(AscendingIterator&& other) noexcept {
    if (this != &other) {
        this->container = std::move(other.container);
        this->indx = other.indx;
        other.indx = 0;
    }
    return *this;
}


MagicalContainer:: AscendingIterator& MagicalContainer::AscendingIterator:: operator=(const AscendingIterator& other){
    if (this->container.ascending_container != other.container.ascending_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    else{
        this->indx = other.indx;
        return *this;
    }
}

bool MagicalContainer::AscendingIterator:: operator==(AscendingIterator& other) {
    if (this->container.ascending_container != other.container.ascending_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.ascending_container == &other.container.ascending_container && this->indx == other.indx;
}

bool MagicalContainer::AscendingIterator:: operator!=(AscendingIterator& other){
    if (this->container.ascending_container != other.container.ascending_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator:: operator>(AscendingIterator& other) {
    if (this->container.ascending_container != other.container.ascending_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.ascending_container == &other.container.ascending_container && this->indx > other.indx;
}

bool MagicalContainer::AscendingIterator:: operator<(AscendingIterator& other) {
    if (this->container.ascending_container != other.container.ascending_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.ascending_container == &other.container.ascending_container && this->indx < other.indx;
}

int MagicalContainer::AscendingIterator:: operator*(){
    return *this->container.ascending_container[static_cast<std::vector<int*>::size_type>(indx)];
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if (indx == this->container.ascending_container.size()) {
        throw std::runtime_error("Attempt to increment beyond the end");
    }
    else {
        ++this->indx;
        return *this;
    }
}


MagicalContainer:: AscendingIterator MagicalContainer::AscendingIterator:: begin(){
    return AscendingIterator(container,0);
}

MagicalContainer:: AscendingIterator MagicalContainer::AscendingIterator:: end(){
    return AscendingIterator(container,this->container.ascending_container.size());
}





// PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& cont)
    : container(cont), indx(0) {}

MagicalContainer::PrimeIterator:: PrimeIterator(PrimeIterator& other)
    : PrimeIterator(other.container) {}

MagicalContainer::PrimeIterator:: PrimeIterator(MagicalContainer& cont, int indx_)
    : container(cont), indx(indx_) {}


// move constructor
MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator&& other) noexcept
    : container(other.container), indx(other.indx) {
    other.indx = 0;
}

// move assignment operator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(PrimeIterator&& other) noexcept {
    if (this != &other) {
        this->container = std::move(other.container);
        this->indx = other.indx;
        other.indx = 0;
    }
    return *this;
}



MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (this->container.prime_container != other.container.prime_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    else{
        this->indx = other.indx;
        return *this;
    }    
}

bool MagicalContainer::PrimeIterator::operator==(PrimeIterator& other) {
    if (this->container.prime_container != other.container.prime_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.prime_container == &other.container.prime_container && this->indx == other.indx;
}

bool MagicalContainer::PrimeIterator::operator!=(PrimeIterator& other) {
    if (this->container.prime_container != other.container.prime_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator:: operator>(PrimeIterator& other){
    if (this->container.prime_container != other.container.prime_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.prime_container == &other.container.prime_container && this->indx > other.indx;
}

bool MagicalContainer::PrimeIterator:: operator<(PrimeIterator& other){
    if (this->container.prime_container != other.container.prime_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.prime_container == &other.container.prime_container && this->indx < other.indx;
}

int MagicalContainer::PrimeIterator::operator*() {
    return *this->container.prime_container[static_cast<std::vector<int*>::size_type>(indx)];
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if (indx == this->container.prime_container.size()) {
        throw std::runtime_error("Attempt to increment beyond the end");
    }
    else {
        ++this->indx;
        return *this;
    }
}



MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return PrimeIterator(container,0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    return PrimeIterator(container, this->container.prime_container.size());
}







// SideCrossIterator
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& cont)
    : container(cont), indx(0) {}


MagicalContainer::SideCrossIterator:: SideCrossIterator(SideCrossIterator& other)
    : SideCrossIterator(other.container) {}


MagicalContainer::SideCrossIterator:: SideCrossIterator(MagicalContainer& cont, int indx_)
    : container(cont), indx(indx_) {}


// move constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& other) noexcept
    : container(other.container), indx(other.indx) {
    other.indx = 0;
}

// move assignment operator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(SideCrossIterator&& other) noexcept {
    if (this != &other) {
        this->container = std::move(other.container);
        this->indx = other.indx;
        other.indx = 0;
    }
    return *this;
}



MagicalContainer:: SideCrossIterator& MagicalContainer::SideCrossIterator:: operator=(const SideCrossIterator& other){
    if (this->container.cross_container != other.container.cross_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    else{
        this->indx = other.indx;
        return *this;
    }
}

bool MagicalContainer::SideCrossIterator::operator==(SideCrossIterator& other){
    if (this->container.cross_container != other.container.cross_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.cross_container == &other.container.cross_container && this->indx == other.indx;
}


bool MagicalContainer::SideCrossIterator::operator!=(SideCrossIterator& other){
    if (this->container.cross_container != other.container.cross_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator:: operator>(SideCrossIterator& other){
    if (this->container.cross_container != other.container.cross_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.cross_container == &other.container.cross_container && this->indx > other.indx;
}

bool MagicalContainer::SideCrossIterator:: operator<(SideCrossIterator& other){
    if (this->container.cross_container != other.container.cross_container) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return &this->container.cross_container == &other.container.cross_container && this->indx < other.indx;
}

int MagicalContainer::SideCrossIterator::operator*() {
    return *this->container.cross_container[static_cast<std::vector<int*>::size_type>(indx)];
}


MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (indx == this->container.cross_container.size()) {
        throw std::runtime_error("Attempt to increment beyond the end");
    }
    else {
        ++this->indx;
        return *this;
    }
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return SideCrossIterator(container,0);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    return SideCrossIterator(container, this->container.cross_container.size());
}


// end of program