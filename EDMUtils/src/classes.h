#include "ManagerUtils/EDMUtils/interface/Counter.hpp"
#include "DataFormats/Common/interface/Wrapper.h"

namespace ManagerUtil_EDMUtils {
        struct dictionaryobjects {
                mgr::Counter mgrct;
                edm::Wrapper<mgr::Counter>  mgrct_wrp;
        };
}
