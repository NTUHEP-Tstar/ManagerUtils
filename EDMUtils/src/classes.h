#include "DataFormats/Common/interface/Wrapper.h"
#include "ManagerUtils/EDMUtils/interface/Counter.hpp"

namespace ManagerUtil_EDMUtils {
struct dictionaryobjects
{
  mgr::Counter               mgrct;
  edm::Wrapper<mgr::Counter> mgrct_wrp;
};
}
