#ifndef KIWI_FRAMEWORK_INCLUDED
#define KIWI_FRAMEWORK_INCLUDED

namespace kiwi
{
    /**
     * General enter point for Kiwi compiler infrastructure
     *
     * @author Vasiliy Sheredeko
     * @since 2012-04-15
     */
    class Framework
    {
        Framework(const Framework&);    ///< NOT IMPLEMENT!!!
        operator=(const Framework&);    ///< NOT IMPLEMENT!!!

    public:
        static Framework create();
    };
}

#endif