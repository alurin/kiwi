#ifndef KIWI_LANG_NODE_INTERNAL
#define KIWI_LANG_NODE_INTERNAL

namespace kiwi { namespace lang {

    class Node
    {
        Node(const Node&);              ///< NOT IMPLEMENT!!!
        Node& operator=(const Node&);   ///< NOT IMPLEMENT!!!
    public:
        Node() { }

        virtual ~Node() {}
    };

} }

#endif