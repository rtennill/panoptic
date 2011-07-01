// Copyright (c) 2011 Robert Kooima
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <SDL.h>
#include <SDL_thread.h>

#include "tree.hpp"

//------------------------------------------------------------------------------

template <typename T> class queue
{
public:

    queue(int);
   ~queue();

    void insert(T);
    T    remove( );
//    bool search(T);
    bool empty ( );
    bool full  ( );
    
private:

    SDL_sem   *full_slots;
    SDL_sem   *free_slots;
    SDL_mutex *data_mutex;

    tree<T> S;
    
    int first;
    int last;
    int size;
    T  *data;
};

//------------------------------------------------------------------------------

template <typename T> queue<T>::queue(int n)  : first(0), last(0), size(n)
{
    full_slots = SDL_CreateSemaphore(0);
    free_slots = SDL_CreateSemaphore(n);
    data_mutex = SDL_CreateMutex();

//    data = new T[n];
}

template <typename T> queue<T>::~queue()
{
//    delete [] data;
    
    SDL_DestroyMutex(data_mutex);
    SDL_DestroySemaphore(free_slots);
    SDL_DestroySemaphore(full_slots);
}

//------------------------------------------------------------------------------

template <typename T> void queue<T>::insert(T d)
{
    SDL_SemWait(free_slots);
    SDL_mutexP(data_mutex);
    {
        S.insert(d, 0);
    }
    SDL_mutexV(data_mutex);
    SDL_SemPost(full_slots);
}

template <typename T> T queue<T>::remove()
{
    T d;
    
    SDL_SemWait(full_slots);
    SDL_mutexP(data_mutex);
    {
        d = S.first();
    }
    SDL_mutexV(data_mutex);
    SDL_SemPost(free_slots);
    
    return d;
}
/*
template <typename T> bool queue<T>::search(T d)
{
    bool b = true;
    
    SDL_mutexP(data_mutex);
    {
        if (S.size())
        {
            T& e = S.search(d, 0);
            if (d < e) b = false;
            if (e < d) b = false;
        }
        else b = false;
    }
    SDL_mutexV(data_mutex);

    return b;
}
*/
template <typename T> bool queue<T>::empty()
{
    return (SDL_SemValue(full_slots) == 0);
}

template <typename T> bool queue<T>::full()
{
    return (SDL_SemValue(free_slots) == 0);
}

//------------------------------------------------------------------------------

#endif
