#pragma once
#include "Time.h"
#include <string>
#include <functional>
#include <thread>

class SyncThread
{
public:

    SyncThread(const std::string name, std::function<void(Time*)> onTick);
    ~SyncThread();

    void setSyncThread(SyncThread* thread);

    const std::string getName() const;
    const Time* getTime() const;

    const bool getIsWaiting() const;

    void start();
    void stop();

private:
    static unsigned int CURRENT_ID;

    bool _waiting;
    bool _isRunning;
    bool _isStopping;
    bool _isMain;
    SyncThread* _syncThread;

    std::thread* _th;

    std::function<void(Time*)> _onTick;
    std::string _name;
    unsigned int _id;
    Time* _time;

    void update();
};

