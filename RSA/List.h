//
//  List.h
//  Containers
//
//  Created by Андрей Рычков on 28.02.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef Containers_List_h
#define Containers_List_h

#include <iostream>

template<typename TIP>
class List
{
    struct Node
    {
        Node *prev, *next;
        TIP data;
        Node(const TIP &x): prev(NULL), next(NULL), data(x){}
    };
    Node *first, *last;
    unsigned int count;
public:
    List():first(NULL), last(NULL), count(0){}
    List( const List&);
    
    List &operator=(const List&);
    
    void push_back(const TIP &);
    void push_front(const TIP &);
    void clear();
    void sort();
    void empty()
    {
        clear();
    }
    ~List()
    {
        clear();
    }
    unsigned int size()const
    {
        return count;
    }
    TIP &operator[](long)const;
    class iterator
    {
        Node *current;
    public:
        iterator( Node *p=NULL):current(p){}
        TIP &operator*()const
        {
            return current->data;
        }
        bool operator==(const iterator &p)const
        {
            return current==p.current;
        }
        bool operator!=(const iterator &p)const
        {
            return current!=p.current;
        }
        iterator &operator++()
        {
            if(current)
                current=current->next;
            else
                throw "Iterator: Out of bounds";
            return *this;
        }
        iterator operator++(int)
        {
            Node *tmp = current;
            if(current)
                current=current->next;
            else
                throw "Iterator: Out of bounds";
            return iterator(tmp);
        }
        friend class List;
    };
    iterator begin()const
    {
        return iterator(first);
    }
    iterator end()const
    {
        return iterator(NULL);
    }
    class reverse_iterator
    {
        Node *current;
    public:
        reverse_iterator( Node *p=NULL):current(p){}
        TIP &operator*()const
        {
            return current->data;
        }
        bool operator==(const reverse_iterator &p)const
        {
            return current==p.current;
        }
        bool operator!=(const reverse_iterator &p)const
        {
            return current!=p.current;
        }
        reverse_iterator &operator++()
        {
            if(current)
                current=current->prev;
            else
                throw "Iterator: Out of bounds";
            return *this;
        }
        reverse_iterator operator++(int)
        {
            Node *tmp = current;
            if(current)
                current=current->prev;
            else
                throw "Iterator: Out of bounds";
            return iterator(tmp);
        }
        
    };
    reverse_iterator rbegin()const
    {
        return reverse_iterator(last);
    }
    reverse_iterator rend()const
    {
        return reverse_iterator(NULL);
    }
    
    iterator Find(const TIP&)const;
    void erase(const TIP&);
    void sort1();
    
};
template <typename TIP>
List<TIP>::List(const List<TIP> &A)
{
    Node *tmp = A.first;
    if (tmp)
    {
        first = new Node(tmp->data);
        tmp = tmp->next;
        last = first;
        while (tmp)
        {
            last->next = new Node(tmp->data);
            last->next->prev = last;
            last = last->next;
            tmp = tmp->next;
        }
    }else
        first = last = NULL;
    count = A.count;
}

template <typename TIP>
List<TIP> &List<TIP>::operator=(const List<TIP> &A)
{
    if (this!=&A)
    {
        clear();
        Node *tmp = A.first;
        if (tmp)
        {
            first = new Node(tmp->data);
            tmp = tmp->next;
            last = first;
            while (tmp)
            {
                last->next = new Node(tmp->data);
                last->next->prev = last;
                last = last->next;
                tmp = tmp->next;
            }
        }else
            first = last = NULL;
        count = A.count;
    }
    return *this;
}

template <typename TIP>
void List<TIP>::sort()
{
    if (!first)
        return;
    if (first == last)
        return;
    bool notSorted = true;
    do
    {
        Node *Begins[2], *Ends[2];
        unsigned char p=0;
        // Split
        Ends[p] = Begins[p] = first;
        first = first->next;
        Ends[!p] = Begins[!p] = NULL;
        while(first)
        {
            if (first->data < Ends[p]->data)
                p=!p;
            if (!Begins[p])
                Begins[p] = first;
            else
                Ends[p]->next=first;
            Ends[p] = first;
            first = first->next;
        }
        if (Ends[p])
            Ends[p]->next = NULL;
        if (Ends[!p])
            Ends[!p]->next = NULL;
        //Merge
        if (Begins[!p])
        {
            bool s1, s2;
            p = (Begins[0]->data < Begins[1]->data) ? 0:1;
            last = first = Begins[p];
            Begins[p] = Begins[p]->next;
            while( Begins[p])
            {
                s1 = (Begins[p]->data < last->data)? true:false;
                s2 = (Begins[!p]->data < last->data)? true:false;
                if (s1 == s2)
                    p = (Begins[0]->data < Begins[1]->data) ? 0:1;
                else
                    if (s1)
                        p = !p;
                last->next = Begins[p];
                Begins[p] = Begins[p]->next;
                last = last->next;
            }
            last->next = Begins[!p];
            last = Ends[p];
        }else
        {
            first = Begins[p];
            notSorted = false;
        }
    }while(notSorted);
    // Refresh Bounds;
    first->prev = NULL;
    Node *now = first;
    while (now->next)
    {
        now->next->prev = now;
        now = now->next;
    }
    last = now;
}

template <typename TIP>
void List<TIP>::push_back(const TIP &x)
{
    if (!first)
    {
        first = last = new Node(x);
    }else
    {
        last->next = new Node(x);
        last->next->prev = last;
        last = last->next;
    }
    ++count;
}

template <typename TIP>
void List<TIP>::push_front(const TIP &x)
{
    if (!first)
        first = last = new Node(x);
    else
    {
        first->prev = new Node(x);
        first->prev->next = first;
        first = first->prev;
    }
    ++count;
}

template <typename TIP>
void List<TIP>::clear()
{
    Node *tmp;
    while (first)
    {
        tmp=first;
        first = first->next;
        delete tmp;
    }
    count = 0;
    first = last = NULL;
}

template <typename TIP>
TIP& List<TIP>::operator[](long i)const
{
    if (i>=count) throw "Out of list bounds";
    Node *tmp = first;
    unsigned int n=0;
    while (n<i)
    {
        tmp = tmp->next;
        ++n;
    }
    if (tmp) return tmp->data;
    throw "Out of list bounds";
}

template <typename TIP>
typename List<TIP>::iterator List<TIP>::Find(const TIP& x)const
{
    Node *now = first;
    while(now)
    {
        if(now->data == x)
            return iterator(now);
        now = now->next;
    }
    return end();
}

template <typename TIP>
void List<TIP>::erase(const TIP& x)
{
    Node *now = first;
    while(now)
    {
        if(now->data == x)
        {
            if (now == first)
            {
                first = now->next;
                if (first) now->next->prev = NULL;
            }else if (now == last)
            {
                last = now->prev;
                if (last) now->prev->next = NULL;
            }else
            {
                now->prev->next = now->next;
                now->next->prev = now->prev;
            }
            break;
        }
        now = now->next;
    }
    --count;
    delete now;
}

#endif
