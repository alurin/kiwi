#ifndef KIWI_LANG_EXPRESSIONNODE_INTERNAL
#define KIWI_LANG_EXPRESSIONNODE_INTERNAL

#include "Node.hpp"

namespace kiwi { namespace lang {

    class ExpressionNode : public Node  { };

    class LeftNode : ExpressionNode    { };
    class RightNode : ExpressionNode   { };

    class ExpressionFactory {
    public:
        RightNode* getNeg(RightNode* right)
        { return 0; }

        RightNode* getAdd(RightNode* right)
        { return 0; }

        RightNode* getNot(RightNode* right)
        { return 0; }

        RightNode* getDec(RightNode* right, bool post = false)
        { return 0; }

        RightNode* getInc(RightNode* right, bool post = false)
        { return 0; }

        RightNode* getAdd(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getSub(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getMul(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getDiv(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getLsh(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getRsh(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getOr(RightNode* left, RightNode* right, bool logic = false)
        { return 0; }

        RightNode* getAnd(RightNode* left, RightNode* right, bool logic = false)
        { return 0; }

        RightNode* getEq(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getNeq(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getGe(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getLe(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getGt(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getLt(RightNode* left, RightNode* right)
        { return 0; }

        RightNode* getAssign(LeftNode* left, RightNode* right)
        { return 0; }

    };
}}

#endif