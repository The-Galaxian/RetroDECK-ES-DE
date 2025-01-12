//  SPDX-License-Identifier: MIT
//
//  ES-DE
//  AsyncHandle.h
//
//  Asynchronous operations used by GuiScraperSearch and Scraper.
//

#ifndef ES_CORE_ASYNC_HANDLE_H
#define ES_CORE_ASYNC_HANDLE_H

#include <string>

enum AsyncHandleStatus {
    ASYNC_IN_PROGRESS,
    ASYNC_ERROR,
    ASYNC_DONE
};

// Handle for some asynchronous operations.
class AsyncHandle
{
public:
    AsyncHandle()
        : mStatus(ASYNC_IN_PROGRESS)
        , mRetry {true}
    {
    }
    virtual ~AsyncHandle() {}

    virtual void update() = 0;

    // Update and return the latest status.
    AsyncHandleStatus status()
    {
        update();
        return mStatus;
    }

    const bool getRetry() { return mRetry; }

    // User-friendly string of our current status.
    // Will return error message if status() == SEARCH_ERROR.
    std::string getStatusString()
    {
        switch (mStatus) {
            case ASYNC_IN_PROGRESS:
                return "in progress";
            case ASYNC_ERROR:
                return mError;
            case ASYNC_DONE:
                return "done";
            default:
                return "something impossible has occured; row, row, fight the power";
        }
    }

protected:
    void setStatus(AsyncHandleStatus status) { mStatus = status; }
    void setError(const std::string& error, bool retry)
    {
        setStatus(ASYNC_ERROR);
        mError = error;
        mRetry = retry;
    }

    std::string mError;
    AsyncHandleStatus mStatus;
    bool mRetry;
};

#endif // ES_CORE_ASYNC_HANDLE_H
