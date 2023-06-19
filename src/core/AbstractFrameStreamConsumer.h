#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

class AbstractFrameStreamConsumer;
template <typename frame>
class FrameStreamConsumer;
class AbstractFrameStream;
template <typename frame>
class FrameStream;

class AbstractFrameStreamConsumer
{
    friend AbstractFrameStream;

protected:
    AbstractFrameStream* owner;
    std::string          name;

public:
    AbstractFrameStreamConsumer( AbstractFrameStream* owner, const std::string& name, bool keepSyncedToOwner = true );

    virtual void connect( std::shared_ptr<FrameStream<double>> signal );

public:
    virtual void setConstant( double k );

    /**
     * Synchronise the plugged instrument with the owner
     */
    void sync( int clock );

    /**
     * If this is false, the inputs syncronisation should be manually handled by
     * the owners `action`. This allows for all kind of pausing, rerating, phasing
     * or buffering of dependency signals.
     */
    bool keepSyncedToOwner;
    void syncToOwner();

    std::string label();

protected:
    std::shared_ptr<AbstractFrameStream> untypedConnection;

public:
    void checkConnection();

public:
    void reset();
};
