//what are the different operation you can perform with atomic
//1. store()
//2 load()
//3. compare_exchange_weak() and compare_exchange_strong()
// compare_exchange_weak can supriously fail, if the atomic value equals expected.
// when your algorithm isnt structured around compare_exchange_Strong() or with a tighter loop

//Memory_order_relaxed: Gurrantee atomicity only, no ordering or sync with other operation
//Memory order_release: This gurrantes that all prior read/writes in the same thread beccomes visible before this
// atomic become visible to other tha


#include <atomic>
#include <cassert>
#include <thread>

int data=0;
std::atomic<bool> ready(false);

void producer()
{
	data= 100;
	ready.store(true);
	//replace ready.store with ready.sttore(true,. std::memory_order_relaxed)
	//using this, they both now have a shared variable anmd can agree upon a value of data
}

void consumer
{
	while(!ready.load()) //replace with (!ready.load(std::memory_order_relaxed)
	{

	}
	assert(data==100);
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();

	return 0;
}


//Order will be thread1, write data 100
//thread 2, will ee the load(ready) == true
// thread 1 will store(ready,true)
// threa2 will read the data
//These value can be re-ordered

Thread 1                  Memory                  Thread 2
---------                 -------                 ---------
  |                          |                          |
  |   write(data, 100)       |                          |
  | -----------------------> |                          |
  |                          |     load(ready) == true  |
  |                          | <----------------------  |
  |                          |                          |
  |   store(ready, true)     |                          |
  | -----------------------> |                          |
  |                          |                          |
  |                          |       read(data)         |
  |                          | <----------------------  |
  |                          |                          |


//memory barrier say that nothing before the store operation and nothing after the load operation can be re-ordered

Thread 1                  Memory                  Thread 2
---------                 -------                 ---------
  |                          |                          |
  |   write(data, 100)       |                          |
  | -----------------------> |                          |
  |                          |                          |
  |  ================Memory Barrier===================  |
  |   store(ready, true)     |                          |
  | -----------------------> |                          |
  |                          |   load(ready) == true    |                   
  |                          | <----------------------  |
  |  ================Memory Barrier===================  |
  |                          |                          |
  |                          |       read(data)         |
  |                          | <----------------------  |
  |                          |                          |


  //Thread 2 now has the gurrantee that the compiler will not place the store data before the write data

  // while (!ready.load(std::memory_order_acquire))


  //Further notes
  std:: atomic <int> counter {0};

  void event()
  {
  	counter.fetch_add(1, std::memory_order_relaxed);
  }


  //memory order release, is the ordering constraint for the writes
  //All the non-atomic writes before this release in program , becomes visible to other thread 
  //acquire ensure the subsequent reads see all the write before the release

  //All ordinary writes (to non-atomic data) before that store in program order must become visible to other threads before the store itself becomes visible.
  “Everything I’ve written so far must be published before I send this signal.”
  //The compiler/CPU cannot move those writes after the release store.

  //Relaxed means that I have finished writing, nothing after this store moves before it
  // acquire, i am about to start reading, nothing before this load moves after it.

 // memory_order_acquire):

//All ordinary reads/writes after that load in program order cannot be moved before the load.
