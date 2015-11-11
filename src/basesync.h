#ifndef BASESYNC_H
#define BASESYNC_H

#include "repository/repository.h"
#include "optionsargs.h"

class BaseSync
{
    Repository repository;
    soci::session odbc;
public:
    BaseSync(const OptionsArgs& optrions);
    void init();
    ~BaseSync();
};

#endif // BASESYNC_H
