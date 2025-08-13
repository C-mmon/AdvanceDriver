#include <vector>

//Think this as a driver for sensor, serial port, button,
class LowLevelPeripheral
{
private:
    //std:: function can store and call any kind of a callable object, hides the exact type of the thing it store and just 
    // remember how to call it, the return type of the callabale function is nothing here () and further takes no parameter
    std::vector<std::function<void() >> eventCallBack_;

public:
    template <typename TFunc>
    void setEventCallBack(TFunc&& func)
    {
        eventCallBack_.emplace_back(std::forward<TFunc>(func));
        //Now what does forward<TFunc> does, if you give it a temporary, it moves it into eventCallBack_
        // if you give it an lvalue, it copies it into eventCallBack_

    }

    void eventHandler()
    {
        for(auto &cb: eventCallBack_)
        {
            if(cb)
            {
                cb();
            }
        }
    }

    
}

//User of the driver, decides what to do when the event happens
//Hardware → LowLevelPeripheral → SomeGenericControl → Application

class GenericControl
{
public:
    GenericControl()
    {
        //When your hardare events happens, please call back my eventCallBack handler
        // a non-static function needs an object to work on, its not a free function
        //We cant just call GenericControl::eventCallBackHandler() without an object
        //Bind takes a callable and then arguments to pass into it later, basically it bind to this the current instance of the Generic Controller
        //Pro
        periph_.setEventCallBack(std::bind(&GenericControl::eventCallBackHandler, this))
    }

    void eventCallBackHandler()
    {
        //Handle the reported event
        std::cout <<"Some generic recieved"<<std::endl;
    }
private:
    LowLevelPeripheral periph_; //reference to shared peripheral
}

int main()
{
    int a =10;
    int& ref= a; 
    int & bad = 5; //cant bind lvalue ref to rvalue


    //Now reference to rvalue 
    int &&r=5; //okay
    int &&rr2= a; //reference to lvalue;

    //when you write something like this
    // template<typename T>
    // void func(T&& x) {}, when we type T&& it is reference to both lvalue and rvalue;


    LowLevelPeripheral peripheral;
    SomeGenericControl ctrl1(periph);


    periph.eventHandler(); // triggers BOTH callbacks
        peripheral.setEventCallBack([](){
        std::cout << "Lambda handler fired\n";
    });

    std::cout << "Triggering again:\n";
    peripheral.eventHandler();

    //we can set a callback function that takes no parameters
    peripheral.setEventCallBack([]() {
    });
    //lvalue are the location in memory you can point to 
    //rvalue are just temporary number 


    auto myHandler

    return 0;
}


//Low level peripheral : Knows how to talk to the hardware
// High level logic owns the the low level peripheral
// In its constructor, we want low peripheral to say whenever a event happens , please call my eventCallBackHandler
//Now, low-level peripheral stores thecall back, when i detect a event, i will call ctrl.eventCallBackHandler

//In real world, hardare interrupt, polling detect events
// Lowlevel peripheral sees it
// CALL EVENT HANDLER()
// event handler callls stored callback
//some genericControl:: eventCallBackHandler
