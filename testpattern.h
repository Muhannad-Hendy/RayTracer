#ifndef TESTPATTERN_H
#define TESTPATTERN_H

#include "Pattern.h"

class TestPattern : public Pattern
{
public:
    using Pattern::Pattern;

protected:
    const Color patternAt(const Tuple &patternPoint) const override;
};

#endif // TESTPATTERN_H
