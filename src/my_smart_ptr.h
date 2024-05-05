#ifndef MY_SMART_PTR_H
#define MY_SMART_PTR_H


template <typename T>
class my_smart_ptr{
public:
    my_smart_ptr() {
        obj = nullptr;
    }

    my_smart_ptr(T *obj) : obj(obj) { }

    T* get() {
        return this->obj;
    }

    void reset(T *obj) {
        if (this->obj != nullptr && this->obj != obj) {
            delete this->obj;
        }
        this->obj = obj;
    }

    void set(T value) {
        *(this->obj) = value;
    }

    ~my_smart_ptr() {
        if (this->obj != nullptr) {
            delete this->obj;
        }
    }

    T& operator* () {
        return *(this->obj);
    }

    T* operator-> () {
        return this->get();
    }
private:
    T * obj;
};




#endif // MY_SMART_PTR_H
