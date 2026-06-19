#ifndef CHECKER_H
#define CHECKER_H

#include "Pattern.h"

class Checker : public Pattern
{
public:
    using Pattern::Pattern;

protected:
    const Color patternAt(const Tuple &patternPoint) const override;
};

#endif // CHECKER_H
