#include "defs.h"
#include "type.h"
#include "err_msg.h"
#include "lang.h"
#include "import.h"

static struct Type_ t_invalid_var_name = { "invalid_var_name", SZ_INT, t_object };

MFUN(test_mfun){}
IMPORT
{
  CHECK_BB(gwi_class_end(gwi))
  return 1;
}
