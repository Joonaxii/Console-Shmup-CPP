#include "SyncThread.h"
#include <windows.h>

unsigned int SyncThread::CURRENT_ID = 0;

SyncThread::SyncThread(const std::string name, std::function<void(Time*)> onTick) : _waiting(false), _th(nullptr), _isRunning(false), _isStopping(false), _isMain(false), _onTick(onTick),  _name(name), _syncThread(nullptr), _id(CURRENT_ID++) {
    _time = new Time();
}

SyncThread::~SyncThread() {
    delete _time;
}

void SyncThread::setSyncThread(SyncThread* thread) {
    if (_syncThread != nullptr || thread->_isMain) { return; }

    _isMain = thread != nullptr;
    _syncThread = thread;

    if (_isMain) {
        _syncThread->_syncThread = this;
    }
}

const std::string SyncThread::getName() const {
    return _name;
}

const Time* SyncThread::getTime() const {
    return _time;
}

const bool SyncThread::getIsWaiting() const {
    return _waiting;
}

void SyncThread::start() {
    if (_isRunning || _isStopping) { return; }
    _isRunning = true;
    _isStopping = false;

    if (_isMain) {
        _syncThread->start();
    }

    if (_id == 0) {
        update();
        return;
    }

    auto lamb = [=] { update(); };
    _th = new std::thread(lamb);
}

void SyncThread::stop() {
    if (!_isRunning || _isStopping) { return; }
    _isRunning = true;
    _isStopping = true;

    if (_isMain) {
        _syncThread->stop();
        return;
    }
    _th->join();
}

void SyncThread::update() {
    OutputDebugStringA(("Starting thread [" + std::to_string(_id) + "] " + _name + "\n").c_str());
    while (_isRunning) {
        const auto framesA = _time->getFrames();
        if (_syncThread != nullptr) {
            const auto framesB = _syncThread->_time->getFrames();
            if (framesB < framesA) { _waiting = true; continue; }
        }

        _onTick(_time);
        _time->tick();

        _waiting = false;
    }
    _isStopping = false;

    if (!_isMain) {
        delete _th;
    }
}
