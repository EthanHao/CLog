/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lock.h
 * Author: ethan
 *
 * Created on February 1, 2017, 9:26 AM
 */

#ifndef LOCK_H
#define LOCK_H

#include <mutex>

namespace CLOG{
    
class Lock
{
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

class LockFromCpp : public Lock
{
private:
    std::mutex _mutex;
public:
    virtual void lock() {_mutex.lock();}
    virtual void unlock() {_mutex.unlock();}
};



}//namespace
#endif /* LOCK_H */

