#include <cassert>
#include <iostream>
#include <shared_ptr.h>

#include "shared_ptr.h"

// Storage class
shared_ptr::Storage::Storage(Matrix *mtx) {
    data_  = mtx;
    ref_count_ = 1;
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}

void shared_ptr::Storage::decr() {
    ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix *shared_ptr::Storage::getObject() const {
    return data_;
}

shared_ptr::Storage::~Storage() {
    delete(data_);
}

// Shared_ptr class
shared_ptr::shared_ptr(Matrix *obj) {
    if (obj == 0) {
       storage_ = 0;
    } else {
        storage_ = new Storage(obj);
    }
}

shared_ptr::shared_ptr(const shared_ptr &other) {
    if (other.isNull()) {
       storage_ = 0;
    } else {
        storage_ = other.storage_;
        storage_->incr();
    }
}

shared_ptr &shared_ptr::operator=(shared_ptr other) {
    if(other.isNull()) {
        storage_ = 0;
    } else {
        unbind_storage();
        storage_ = other.storage_;
        storage_->incr();
    }
    return *this;
}

shared_ptr::~shared_ptr() {
    unbind_storage();
}

Matrix *shared_ptr::ptr() const {
    return (isNull()) ? 0 : storage_->getObject();
}

bool shared_ptr::isNull() const {
    return storage_ == 0;
}

void shared_ptr::reset(Matrix *obj) {
    unbind_storage();
    if(obj == 0) {
        storage_ = 0;
    } else {
        storage_ = new Storage(obj);
    }
}

Matrix *shared_ptr::operator->() const {
    return ptr();
}

Matrix &shared_ptr::operator*() const {
    return *ptr();
}

void shared_ptr::unbind_storage() {
    if (!isNull()) {
        storage_->decr();
        if (storage_->getCounter() == 0) {
            delete(storage_);
        }
    }
}











