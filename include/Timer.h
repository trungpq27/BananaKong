#ifndef TIMER_H
#define TIMER_H

#include <BaseFunc.h>

class Timer
{
    private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
		bool mPaused;
		bool mStarted;

    public:
		Timer();

		~Timer();

		void start();

		void stop();

		void pause();

		void unpause();

		Uint32 getTicks();

		bool isStarted();

		bool isPaused();
};

//-----Declare------
extern Timer gTimer;
extern void closeTimer();

#endif // TIMER_H
