#ifndef KIWI_ENGINE_INCLUDED
#define KIWI_ENGINE_INCLUDED

namespace kiwi
{
    /// Start up Kiwi and prepare dependences
    void startup();

    /// Shut down Kiwi and clean up memory for dependences
    void shutdown();
}

#endif