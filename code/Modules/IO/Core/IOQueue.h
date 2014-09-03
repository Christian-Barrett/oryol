#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::IO::IOQueue
    @brief simplify asynchronous loading of multiple files

    IOQueues are used to load one or more files asynchronously, and associate
    a success (and optional failure) callback with an IO request.
    
    See the IOQueue sample application to see how it works :)
*/
#include "Core/Types.h"
#include "Core/String/StringAtom.h"
#include "IO/IOProtocol.h"
#include "Core/Containers/Array.h"
#include <functional>

namespace Oryol {
namespace IO {
    
class IOQueue {
public:
    /// constructor
    IOQueue();
    /// destructor
    ~IOQueue();

    /// callback function signature for success
    typedef std::function<void(const Core::Ptr<IO::Stream>&)> SuccessFunc;
    /// callback function signature for failure
    typedef std::function<void(const IO::URL& url, IOStatus::Code ioStatus)> FailFunc;

    /// start queue processing
    void Start();
    /// stop queue processing
    void Stop();
    /// return true if queue is in started state
    bool IsStarted() const;
    
    /// add a file load request to the queue
    void Add(const URL& url, SuccessFunc onSuccess, FailFunc onFail=FailFunc());
    /// return true if queue is empty
    bool Empty() const;
    
private:
    /// update the queue, called per frame from runloop
    void update();
    
    bool isStarted;
    int32 runLoopId;
    struct item {
        Core::Ptr<IO::IOProtocol::Get> ioRequest;
        SuccessFunc successFunc;
        FailFunc failFunc;
    };
    Core::Array<item> ioRequests;
};
    
} // namespace IO
} // namespace Oryol