// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "elevatortest.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	// printf("*** thread %d looped %d times\n", which, num);
        printf("*** thread name %s userid %d threadid %d looped %d times \n",
            currentThread->getName(),currentThread->getUserID(),currentThread->getUserID(),num);
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

// void
// ThreadTest1()
// {
//     DEBUG('t', "Entering ThreadTest1");

//     Thread *t = new Thread("forked thread");

//     t->Fork(SimpleThread, (void*)1);
//     SimpleThread(0);
// }
void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t1 = new Thread("forked thread");
    Thread *t2 = new Thread("forked thread");
    Thread *t3 = new Thread("forked thread");
    Thread *t4 = new Thread("forked thread");

    t1->Fork(SimpleThread, t1->getThreadID());
    t2->Fork(SimpleThread, t2->getThreadID());
    t3->Fork(SimpleThread, t3->getThreadID());
    t4->Fork(SimpleThread, t4->getThreadID());
    SimpleThread(0);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

void receiveMessage(int which){
    char content[MaxMessage];
    ASSERT(currentThread->Receive(content)>0);
    printf("%s receive \"%s\"\n",currentThread->getName(),content);
}

void MessageTest(char *content){
    Thread *t=new Thread("forked");
    t->Fork(receiveMessage,0);
    ASSERT(currentThread->Send(content,t->getThreadID()));
    printf("%s send \"%s\" to %s\n",currentThread->getName(),content,t->getName());
}