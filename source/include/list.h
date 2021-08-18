#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>  // cout, endl
using std::cout;
using std::endl;

#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
using std::copy;
#include <cstddef>   // std::ptrdiff_t
#include <type_traits>

namespace sc { // linear sequence. Better name: sequence container (same as STL).
    /*!
     * A class representing a biderectional iterator defined over a linked list.
     *
     * \note
     * This iterator only works for traversing elements inside the same list.
     *
     * This class is incomplete and it is provided "as is".
     *
     * \date May, 2nd 2017.
     * \author Selan R. dos Santos
     */

    template < typename T >
    class list
    {
        private:
        //=== the data node.
        struct Node
        {
            T data; // Tipo de informação a ser armazenada no container.
            Node * next;
            Node * prev;

            Node( const T &d=T{} , Node * n=nullptr, Node * p=nullptr )
                : data {d}, next{n}, prev{p}
            { /* empty */ }
        };


        //=== The iterator classes.
        public:

        class const_iterator : public std::bidirectional_iterator_tag 
        {
            //=== Some aliases to help writing a clearer code.
            public:
                using value_type        = T;         //!< The type of the value stored in the list.
                using pointer           = T *;       //!< Pointer to the value.
                using reference         = T &;       //!< reference to the value.
                using const_reference   = const T &; //!< const reference to the value.
                using difference_type   = std::ptrdiff_t;
                using iterator_category = std::bidirectional_iterator_tag;

            private:
                Node * m_ptr; //!< The raw pointer.

            public:
                const_iterator( Node * ptr = nullptr ) : m_ptr {ptr} {}
                ~const_iterator() = default;
                const_iterator( const const_iterator & ) = default;
                const_iterator& operator=( const const_iterator & ) = default;
                reference operator*() {
                    return m_ptr->data;
                }
                const_reference operator*() const {
                    return m_ptr->data;
                }
                const_iterator operator++() {
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator++(): iterator already in end of list");
                    m_ptr = m_ptr->next;
                    return *this;
                }
                const_iterator operator++(int) {
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator++(): iterator already in end of list");
                    auto old {m_ptr};
                    m_ptr = m_ptr->next;
                    return const_iterator{old};
                }
                const_iterator operator--() {
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator--(): iterator already in begin of list");
                    m_ptr = m_ptr->prev;
                    return *this; 
                }
                const_iterator operator--(int) {
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator--(): iterator already in begin of list");
                    auto old {m_ptr};
                    m_ptr = m_ptr->prev;
                    return const_iterator{old}; 
                }
                bool operator==( const const_iterator & rhs ) const {  
                    return m_ptr == rhs.m_ptr; 
                }
                bool operator!=( const const_iterator & rhs ) const { 
                    return m_ptr != rhs.m_ptr;
                }

                //=== Other methods that you might want to implement.
                /// it += 3; // Go back  3 positions within the container. 
                const_iterator operator+=( difference_type step) {  
                    return const_iterator{}; 
                }
                /// it -= 3; // Go back  3 positions within the container. 
                const_iterator operator-=(  difference_type step ) { /* TODO */ return const_iterator{}; }
                /// it->method()
                pointer operator->( void ) const { /* TODO */ return nullptr; }
                /// it1 - it2
                difference_type operator-( const const_iterator & rhs ) const { /* TODO */ return 0; }

                // We need friendship so the list<T> class may access the m_ptr field.
                friend class list<T>;

                friend std::ostream & operator<< ( std::ostream & os_, const const_iterator & s_ )
                {
                    os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
                    return os_;
                }
        };


        class iterator : public std::bidirectional_iterator_tag 
        {
            //=== Some aliases to help writing a clearer code.
            public:
                using value_type        = T; //!< The type of the value stored in the list.
                using pointer           = T *; //!< Pointer to the value.
                using reference         = T &; //!< reference to the value.
                using const_reference   = const T &; //!< const reference to the value.
                using difference_type   = std::ptrdiff_t;
                using iterator_category = std::bidirectional_iterator_tag;

            private:
                Node * m_ptr; //!< The raw pointer.

            public:
                iterator( Node * ptr = nullptr ) : m_ptr {ptr} {}
                ~iterator() = default;
                iterator( const iterator & ) = default;
                iterator& operator=( const iterator & ) = default;
                reference  operator*() {
                    return m_ptr->data;
                }
                const_reference operator*() const {
                    return m_ptr->data;
                }
                iterator operator++() {
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator++(): iterator already in end of list");
                    m_ptr = m_ptr->next;
                    return *this;
                }
                iterator operator++(int) {
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator++(): iterator already in end of list");
                    auto old {m_ptr};
                    m_ptr = m_ptr->next;
                    return iterator{old};
                }
                iterator operator--() { 
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator--(): iterator already in begin of list");
                    m_ptr = m_ptr->prev;
                    return *this; 
                 }
                iterator operator--(int) {
                    if (m_ptr == nullptr)
                        throw std::out_of_range("operator--(): iterator already in begin of list");
                    auto old {m_ptr};
                    m_ptr = m_ptr->prev; 
                    return iterator{old}; 
                }
                bool operator==( const iterator & rhs ) const { 
                    return m_ptr == rhs.m_ptr;
                 }
                bool operator!=( const iterator & rhs ) const { 
                    return m_ptr != rhs.m_ptr;
                }

                //=== Other methods that you might want to implement.
                /// it += 3; // Go back  3 positions within the container. 
                iterator operator+=( difference_type step) { /* TODO */ return iterator{}; }
                /// it -= 3; // Go back  3 positions within the container. 
                iterator operator-=(  difference_type step ) { /* TODO */ return iterator{}; }
                /// it->method()
                pointer operator->( void ) const { /* TODO */ return nullptr; }
                /// it1 - it2
                difference_type operator-( const iterator & rhs ) const { /* TODO */ return 0; }

                // We need friendship so the list<T> class may access the m_ptr field.
                friend class list<T>;

                friend std::ostream & operator<< ( std::ostream & os_, const iterator & s_ )
                {
                    os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
                    return os_;
                }
        };


        //=== Private members.
        private:
            size_t m_len;    // comprimento da lista.
            Node * m_head; // nó cabeça.
            Node * m_tail; // nó calda.

        public:
        //=== Public interface

        //=== [I] Special members
        list() : m_len{0}, m_head{new Node}, m_tail{new Node} { 
            /*  Head & tail nodes.
             *     +---+    +---+
             *     |   |--->|   |--+
             *     | H |    | T |  |
             *  +--|   |<---|   |  |
             *  |  +---+    +---+  |
             *  |                  |
             * ===                ===
             *  =                  =
             */
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }

        explicit list( size_t count ) {
            m_head = new Node;
            m_tail = new Node;
            auto prev {m_head};
            for (auto i {0u}; i < count; i++) {
                auto curr {new Node};
                prev->next = curr;
                curr->prev = prev;
                prev = curr;
            }
            m_len = count;
        }
        template< typename InputIt >
        list( InputIt first, InputIt last ) { /* TODO */ }
        list( const list & clone ) : m_len{clone.m_len}, m_head{new Node}, m_tail{new Node} {
            auto prev = m_head;
            for (auto it {clone.cbegin()}; it != clone.cend(); it++) {
                auto curr {new Node{*it}};
                prev->next = curr;
                curr->prev = prev;
                prev = curr;
            }
            prev->next = m_tail;
            m_tail->prev = prev;
        }
        list( std::initializer_list<T> ilist ) { 
            m_head = new Node;
            m_tail = new Node;
            auto prev {m_head};
            for (auto it {ilist.begin()}; it != ilist.end(); it++) {
                auto curr {new Node{*it}};
                prev->next = curr;
                curr->prev = prev;
                prev = curr;
            }
            prev->next = m_tail;
            m_tail->prev = prev;
            m_len = ilist.size();
        }
        ~list() { /* TODO */ }
        // TODO (davi): maybe change to use erase insted of first while
        list & operator=( const list & rhs ) {
            // Ensure the size this lsit is not greater than the other, liberating memory if necessary
            while (m_len > rhs.m_len)
                pop_back();
            
            // Puts all the values this values this list can hold right now
            auto last {std::next(rhs.cbegin(), m_len)};
            std::copy(rhs.cbegin(), last, begin());

            // Pushs the remaing valeus to the end of list
            for (auto it {last}; it != rhs.cend(); it++)
                push_back(*it);

            return *this;
        }
        list & operator=( std::initializer_list<T> ilist_ ) { /* TODO */ return *this;}
        //=== [II] ITERATORS
        iterator begin() {
            return iterator{m_head->next};
        }
        const_iterator cbegin() const  { 
            return const_iterator{m_head->next}; }
        iterator end() {
            return iterator{m_tail};
        }
        const_iterator cend() const  { 
            return const_iterator{m_tail}; 
        }
        //=== [III] Capacity/Status
        bool empty ( void ) const { 
            return m_head->next == m_tail;
         }
        size_t size(void) const {
            return m_len;
        }
        //=== [IV] Modifiers
        void clear()  { 
            auto L = m_head->next;
            while (L != m_tail) {
                auto target = L;
                L = L->next;
                delete target;
            }
            m_head->next = m_tail;
            m_tail->prev = m_head;
            m_len = 0;
         }
        T front( void ) {
            if ( empty() ) {
               throw std::out_of_range("front(): cannot use the front method on an empty list.");
            }
            auto element = m_head->next; 
            return T{element->data}; 
        }
        T front( void ) const  { 
            if ( empty() ) {
               throw std::out_of_range("front(): cannot use the front method on an empty list.");
            }
            auto element = m_head->next; 
            return T{element->data}; 
        }
        T back( void ) {             
            if ( empty() ) {
               throw std::out_of_range("back(): cannot use the back method on an empty list.");
            }
            auto element = m_tail->prev; 
            return T{element->data};  
        }
        T back( void ) const  { 
            if ( empty() ) {
               throw std::out_of_range("back(): cannot use the back method on an empty list.");
            }
            auto element = m_tail->prev; 
            return T{element->data};  
         }

        void push_front( const T & value_ ) { /* TODO */ }

        void push_back( const T & value ) {
            insert(end(), value);
        }

        void pop_front() {
            auto L {m_head->next};
            m_head->next = m_head->next->next;
            m_head->next->prev = m_head;
            delete L;
        }

        // TODO (thiago): FIX THIS
        void pop_back() { 
            m_len--;
        }

        //=== [IV-a] MODIFIERS W/ ITERATORS
        template < class InItr >
        void assign( InItr first_, InItr last_ )
        { /* TODO */ }

        void assign( std::initializer_list<T> ilist_ )
        { /* TODO */ }

        /*!
         *  Inserts a new value in the list before the iterator 'it'
         *  and returns an iterator to the new node.
         *
         *  \param pos An iterator to the position before which we want to insert the new data.
         *  \param value The value we want to insert in the list.
         *  \return An iterator to the new element in the list.
         */
        iterator insert( iterator pos, const T & value ) {
            auto new_node {new Node{value}};
            new_node->prev       = pos.m_ptr->prev;
            new_node->prev->next = new_node;
            new_node->next       = pos.m_ptr;
            new_node->next->prev = new_node;

            m_len++;

            return iterator{new_node};
        }

        template < typename InItr >
        iterator insert( iterator pos, InItr first, InItr last ) { 
            // Go trough range in reverse order and insert always at the same position
            for (auto it {last}; it != first; it--)
                pos = insert(pos, *std::prev(it));
            return pos;
        }
        
        iterator insert( iterator cpos_, std::initializer_list<T> ilist_ )
        { /* TODO */ return iterator{}; }

        /*!
         *  Erases the node pointed by 'it_' and returns an iterator
         *  to the node just past the deleted node.
         *
         *  \param it_ The node we wish to delete.
         *  \return An iterator to the node following the deleted node.
         */
        iterator erase( iterator it_ )
        { /* TODO */ return iterator{}; }
        // Erase items from [start; end) and return a iterator just past the deleted node.
        iterator erase( iterator start, iterator end )
        { /* TODO */ return iterator{}; }

        const_iterator find( const T & value_ ) const
        { /* TODO */ return const_iterator{}; }

        iterator find( const T & value_ )
        { /* TODO */ return iterator{}; }

        //=== [V] UTILITY METHODS
        void merge( list & other ) {
            auto curr1 {m_head->next};
            
            while (not other.empty()) {
                auto curr2 {other.m_head->next};

                if (curr1 == m_tail or curr2->data < curr1->data) {
                    // Erase the curr value of the second list
                    other.m_head->next = curr2->next;
                    curr2->next->prev  = other.m_head;

                    // Inserts the curr value of second list before the curr value of first list
                    curr2->prev       = curr1->prev;
                    curr2->prev->next = curr2;
                    curr2->next       = curr1;
                    curr2->next->prev = curr2;
                } else
                    curr1 = curr1->next;
            }

            m_len += other.m_len;
            other.m_len = 0;
        }
        void splice( const_iterator pos, list & other ){ return; }
        void reverse( void ){ return; }
        void unique( void ){ return; }
        void sort( void ){ return; }
    };

    //=== [VI] OPETARORS
    template < typename T >
    inline bool operator==( const sc::list<T> & l1, const sc::list<T> & l2 ) {
        if (l1.size() != l2.size())
            return false;
        auto it1 {l1.cbegin()};
        auto it2 {l2.cbegin()};
        while (it1 != l1.cend() && it2 != l2.cend()) {
            if (*it1++ != *it2++)
                return false;
        }
        return true;
    }

    template < typename T >
    inline bool operator!=( const sc::list<T> & l1, const sc::list<T> & l2 ) {
        if (l1.size() != l2.size())
            return true;  
        bool oneCase{ false };
        auto it1 {l1.cbegin()};
        auto it2 {l2.cbegin()};
        while (it1 != l1.cend() && it2 != l2.cend()) {
            if (*it1++ != *it2++)
                oneCase = true;
        }
        return oneCase;
    }
}
#endif

