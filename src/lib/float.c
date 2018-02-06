#include <stdlib.h>
#include <math.h>
#include "defs.h"
#include "err_msg.h"
#include "type.h"
#include "instr.h"
#include "import.h"

struct Type_ t_float = { "float", SZ_FLOAT, NULL,    te_float };
struct Type_ t_dur   = { "dur",   SZ_FLOAT, NULL,    te_dur };
struct Type_ t_time  = { "time",  SZ_FLOAT, NULL,    te_time };
struct Type_ t_now   = { "@now",  SZ_FLOAT, &t_time, te_now };

static INSTR(float_assign) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_float*)REG(0) = (**(m_float**)REG(0) = *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_plus) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_float*)REG(0) += *(m_float*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_minus) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_float*)REG(0) -= *(m_float*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

INSTR(float_times) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_float*)REG(0) *= *(m_float*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_divide) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_float*)REG(0) /= *(m_float*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_and) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) && *(m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_or) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) || *(m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_eq) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) == *(m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_neq)  {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) != *(m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_gt) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) > *(m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_ge) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) >= *(m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_lt) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) < * (m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_le) {
  POP_REG(shred, SZ_FLOAT * 2);
  *(m_int*)REG(0) = (*(m_float*)REG(0) <= *(m_float*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

INSTR(float_negate) {
  POP_REG(shred, SZ_FLOAT)
    *(m_float*)REG(0) = -*(m_float*)REG(0);
  PUSH_REG(shred, SZ_FLOAT);
}

INSTR(float_not) {
  POP_REG(shred, SZ_FLOAT)
    *(m_int*)REG(0) = !*(m_float*)REG(0);
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_r_assign) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  **(m_float**)REG(SZ_FLOAT) = *(m_float*)REG(0);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_r_plus) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_FLOAT) += (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_r_minus) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_FLOAT) -= (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_r_times) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_FLOAT) *= (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_r_divide) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_FLOAT) /= (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_assign) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (**(m_int**)REG(0) = *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_plus) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_float*)REG(0) = *(m_int*)REG(0) + *(m_float*)REG(SZ_INT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_minus) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_float*)REG(0) = *(m_int*)REG(0) + -*(m_float*)REG(SZ_INT);
  PUSH_REG(shred, SZ_FLOAT);
}

INSTR(int_float_timesf) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_float*)REG(0) = *(m_int*)REG(0) * *(m_float*)REG(SZ_INT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_divide) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_float*)REG(0) = *(m_int*)REG(0) / *(m_float*)REG(SZ_INT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_and) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) && *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_or) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) || *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_eq) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) == *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_neq) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) != *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_gt) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) > *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_ge) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) >= *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_lt) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) < * (m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_le) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) <= *(m_float*)REG(SZ_INT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(int_float_r_assign) {
  POP_REG(shred, SZ_INT * 2);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_INT) = *(m_int*)REG(0));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_r_plus) {
  POP_REG(shred, SZ_INT * 2);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_INT) += (*(m_int*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_r_minus) {
  POP_REG(shred, SZ_INT * 2);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_INT) -= (*(m_int*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_r_times) {
  POP_REG(shred, SZ_INT * 2);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_INT) *= (*(m_int*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(int_float_r_divide) {
  POP_REG(shred, SZ_INT * 2);
  *(m_float*)REG(0) = (**(m_float**)REG(SZ_INT) /= (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_int_assign) {
  POP_REG(shred, SZ_INT * 2);
  *(m_float*)REG(0) = (**(m_float**)REG(0) = *(m_int*)REG(SZ_INT));
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_int_plus) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) += *(m_int*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_int_minus) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) -= *(m_int*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

INSTR(float_int_timesf) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) *= *(m_int*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_int_divide) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_float*)REG(0) /= *(m_int*)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_FLOAT);
}

static INSTR(float_int_and) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_int*)REG(0) = (*(m_float*)REG(0) && *(m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_or) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_int*)REG(0) = (*(m_float*)REG(0) || *(m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_eq) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_int*)REG(0) = (*(m_float*)REG(0) == *(m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_neq) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_int*)REG(0) = (*(m_float*)REG(0) != *(m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_gt) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_int*)REG(0) = (*(m_float*)REG(0) > *(m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_ge) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (*(m_int*)REG(0) >= *(m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_lt) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_int*)REG(0) = (*(m_float*)REG(0) < * (m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_le) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  *(m_int*)REG(0) = (*(m_float*)REG(0) <= *(m_int*)REG(SZ_FLOAT));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_r_assign) {
  POP_REG(shred, SZ_FLOAT + SZ_INT);
  **(m_int**)REG(SZ_FLOAT) = *(m_float*)REG(0);
  *(m_int*)REG(0) = **(m_int**)REG(SZ_FLOAT);
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_r_plus) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (**(m_int**)REG(SZ_FLOAT) += (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_r_minus) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (**(m_int**)REG(SZ_FLOAT) += (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_r_times) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (**(m_int**)REG(SZ_FLOAT) *= (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_INT);
}

static INSTR(float_int_r_divide) {
  POP_REG(shred, SZ_INT + SZ_FLOAT);
  *(m_int*)REG(0) = (**(m_int**)REG(SZ_FLOAT) /= (*(m_float*)REG(0)));
  PUSH_REG(shred, SZ_INT);
}

static m_bool import_values(Importer importer) {
  ALLOC_PTR(d_zero, m_float, 0.0);
  ALLOC_PTR(sr,     m_float, (m_float)vm->sp->sr);
  ALLOC_PTR(samp,   m_float, 1.0);
  ALLOC_PTR(ms,     m_float, (m_float)*sr     / 1000.);
  ALLOC_PTR(second, m_float, (m_float)*sr);
  ALLOC_PTR(minute, m_float, (m_float)*sr     * 60.0);
  ALLOC_PTR(hour,   m_float, (m_float)*minute * 60.0);
  ALLOC_PTR(day,    m_float, (m_float)*hour   * 24.0);
  ALLOC_PTR(t_zero, m_float, 0.0);
  ALLOC_PTR(pi, m_float, M_PI);

  importer_item_ini(importer, "float", "samplerate");
  importer_item_end(importer, ae_flag_const, sr);
  importer_item_ini(importer, "float", "pi");
  importer_item_end(importer, ae_flag_const, pi);
  importer_item_ini(importer, "dur", "d_zero");
  importer_item_end(importer, ae_flag_const, d_zero);
  importer_item_ini(importer, "dur", "samp");
  importer_item_end(importer, ae_flag_const, samp);
  importer_item_ini(importer, "dur", "ms");
  importer_item_end(importer, ae_flag_const, ms);
  importer_item_ini(importer, "dur", "second");
  importer_item_end(importer, ae_flag_const, second);
  importer_item_ini(importer, "dur", "minute");
  importer_item_end(importer, ae_flag_const, minute);
  importer_item_ini(importer, "dur", "hour");
  importer_item_end(importer, ae_flag_const, hour);
  importer_item_ini(importer, "time", "t_zero");
  importer_item_end(importer, ae_flag_const, t_zero);
  return 1;
}

static OP_CHECK(chuck_now) {
  Exp_Binary* bin = (Exp_Binary*)data;
  CHECK_BO(err_msg(TYPE_, bin->pos, "can't assign 'now' to 'now'"))
  return NULL;
}

static OP_EMIT(opem_i2f) {
  CHECK_OB(emitter_add_instr(emit, Cast_i2f))
  return 1;
}

static OP_EMIT(opem_f2i) {
  CHECK_OB(emitter_add_instr(emit, Cast_f2i))
  return 1;
}

INSTR(Cast_i2f) {
  POP_REG(shred,  SZ_INT);
  *(m_float*)REG(0) = *(m_int*)REG(0);
  PUSH_REG(shred,  SZ_FLOAT);
}


INSTR(Cast_f2i) {
  POP_REG(shred,  SZ_FLOAT);
  *(m_int*)REG(0) = *(m_float*)REG(0);
  PUSH_REG(shred,  SZ_INT);
}

m_bool import_float(Importer importer) {
  CHECK_BB(importer_add_type(importer,  &t_float))
  CHECK_BB(importer_add_type(importer,  &t_time))
  CHECK_BB(importer_add_type(importer,  &t_dur))
  CHECK_BB(importer_add_type(importer,  &t_now))
  CHECK_BB(importer_oper_ini(importer, "float", "float", "float"))
  CHECK_BB(importer_oper_add(importer, opck_assign))
  CHECK_BB(importer_oper_end(importer, op_assign,        float_assign))
  CHECK_BB(importer_oper_end(importer, op_plus,          float_plus))
  CHECK_BB(importer_oper_end(importer, op_minus,         float_minus))
  CHECK_BB(importer_oper_end(importer, op_times,         float_times))
  CHECK_BB(importer_oper_end(importer, op_divide,        float_divide))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_chuck,         float_r_assign))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_plus_chuck,    float_r_plus))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_minus_chuck,   float_r_minus))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_times_chuck,   float_r_times))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_divide_chuck,  float_r_divide))
  CHECK_BB(importer_oper_ini(importer, "float", "float", "int"))
  CHECK_BB(importer_oper_end(importer, op_and,           float_and))
  CHECK_BB(importer_oper_end(importer, op_or,            float_or))
  CHECK_BB(importer_oper_end(importer, op_eq, 			 float_eq))
  CHECK_BB(importer_oper_end(importer, op_neq, 			 float_neq))
  CHECK_BB(importer_oper_end(importer, op_gt, 			 float_gt))
  CHECK_BB(importer_oper_end(importer, op_ge, 			 float_ge))
  CHECK_BB(importer_oper_end(importer, op_lt, 			 float_lt))
  CHECK_BB(importer_oper_end(importer, op_le, 			 float_le))
  CHECK_BB(importer_oper_ini(importer, NULL,   "float", "float"))
  CHECK_BB(importer_oper_end(importer, op_minus,         float_negate))
  CHECK_BB(importer_oper_ini(importer, NULL,   "float", "int"))
  CHECK_BB(importer_oper_end(importer, op_exclamation,   float_not))
  CHECK_BB(importer_oper_ini(importer, NULL,   "time", "int"))
  CHECK_BB(importer_oper_end(importer, op_exclamation,   float_not))
  CHECK_BB(importer_oper_ini(importer, NULL,   "dur", "int"))
  CHECK_BB(importer_oper_end(importer, op_exclamation,   float_not))
  CHECK_BB(importer_oper_ini(importer, "int", "float", "int"))
  CHECK_BB(importer_oper_add(importer, opck_assign))
  CHECK_BB(importer_oper_end(importer, op_assign,        int_float_assign))
  CHECK_BB(importer_oper_end(importer, op_and,           int_float_and))
  CHECK_BB(importer_oper_end(importer, op_or,            int_float_or))
  CHECK_BB(importer_oper_end(importer, op_eq, 			 int_float_eq))
  CHECK_BB(importer_oper_end(importer, op_neq, 			 int_float_neq))
  CHECK_BB(importer_oper_end(importer, op_gt, 			 int_float_gt))
  CHECK_BB(importer_oper_end(importer, op_ge, 			 int_float_ge))
  CHECK_BB(importer_oper_end(importer, op_lt, 			 int_float_lt))
  CHECK_BB(importer_oper_end(importer, op_le, 			 int_float_le))
  CHECK_BB(importer_oper_ini(importer, "int", "float", "float"))
  CHECK_BB(importer_oper_end(importer, op_plus,          int_float_plus))
  CHECK_BB(importer_oper_end(importer, op_times,         int_float_timesf))
  CHECK_BB(importer_oper_end(importer, op_minus,         int_float_minus))
  CHECK_BB(importer_oper_end(importer, op_divide,        int_float_divide))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_chuck,        int_float_r_assign))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_plus_chuck,   int_float_r_plus))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_minus_chuck,  int_float_r_minus))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_times_chuck,  int_float_r_times))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_divide_chuck, int_float_r_divide))
  CHECK_BB(importer_oper_add(importer, opck_basic_cast))
  CHECK_BB(importer_oper_emi(importer, opem_i2f))
  CHECK_BB(importer_oper_end(importer, op_dollar,       Cast_i2f))
  CHECK_BB(importer_oper_ini(importer, "float", "int", "float"))
  CHECK_BB(importer_oper_add(importer, opck_assign))
  CHECK_BB(importer_oper_end(importer, op_assign,       float_int_assign))
  CHECK_BB(importer_oper_end(importer, op_plus,         float_int_plus))
  CHECK_BB(importer_oper_end(importer, op_minus,        float_int_minus))
  CHECK_BB(importer_oper_end(importer, op_times,        float_int_timesf))
  CHECK_BB(importer_oper_end(importer, op_divide,       float_int_divide))
  CHECK_BB(importer_oper_ini(importer, "float", "int", "int"))
  CHECK_BB(importer_oper_end(importer, op_and,          float_int_and))
  CHECK_BB(importer_oper_end(importer, op_or,           float_int_or))
  CHECK_BB(importer_oper_end(importer, op_eq, 			float_int_eq))
  CHECK_BB(importer_oper_end(importer, op_neq, 			float_int_neq))
  CHECK_BB(importer_oper_end(importer, op_gt, 			float_int_gt))
  CHECK_BB(importer_oper_end(importer, op_ge, 			float_int_ge))
  CHECK_BB(importer_oper_end(importer, op_lt, 			float_int_lt))
  CHECK_BB(importer_oper_end(importer, op_le, 			float_int_le))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_chuck,        float_int_r_assign))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_plus_chuck,   float_int_r_plus))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_minus_chuck,  float_int_r_minus))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_times_chuck,  float_int_r_times))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_divide_chuck, float_int_r_divide))
  CHECK_BB(importer_oper_add(importer, opck_basic_cast))
  CHECK_BB(importer_oper_emi(importer, opem_f2i))
  CHECK_BB(importer_oper_end(importer, op_dollar, Cast_f2i))

  CHECK_BB(importer_oper_ini(importer, "dur", "dur", "dur"))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_chuck,        float_r_assign))
  CHECK_BB(importer_oper_end(importer, op_plus,         float_plus))
  CHECK_BB(importer_oper_end(importer, op_minus,        float_minus))
  CHECK_BB(importer_oper_end(importer, op_times,        float_times))
  CHECK_BB(importer_oper_ini(importer, "dur", "dur", "float"))
  CHECK_BB(importer_oper_end(importer, op_divide,       float_divide))

  CHECK_BB(importer_oper_ini(importer, "dur", "dur", "int"))
  CHECK_BB(importer_oper_end(importer, op_gt,           float_gt))
  CHECK_BB(importer_oper_end(importer, op_ge,           float_ge))
  CHECK_BB(importer_oper_end(importer, op_lt,           float_lt))
  CHECK_BB(importer_oper_end(importer, op_le,           float_le))

  CHECK_BB(importer_oper_ini(importer, "time", "time", "time"))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_chuck,        float_r_assign))

  CHECK_BB(importer_oper_ini(importer, "time", "dur", "time"))
  CHECK_BB(importer_oper_end(importer, op_plus,         float_plus))
  CHECK_BB(importer_oper_ini(importer, "dur", "time", "time"))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_chuck,        float_r_assign))
  CHECK_BB(importer_oper_end(importer, op_plus,         float_plus))
  CHECK_BB(importer_oper_ini(importer,  "dur",  "@now", "time"))
  CHECK_BB(importer_oper_add(importer, opck_rassign))
  CHECK_BB(importer_oper_end(importer, op_chuck,        Time_Advance))
  CHECK_BB(importer_oper_ini(importer,  "@now",  "@now", NULL))
  CHECK_BB(importer_oper_add(importer,  chuck_now))
  CHECK_BB(importer_oper_end(importer, op_chuck,        NULL))

  CHECK_BB(importer_oper_ini(importer, "time", "time", "int"))
  CHECK_BB(importer_oper_end(importer, op_gt,           float_gt))
  CHECK_BB(importer_oper_end(importer, op_ge, 			 	    float_ge))
  CHECK_BB(importer_oper_end(importer, op_lt, 			 	    float_lt))
  CHECK_BB(importer_oper_end(importer, op_le, 			 	    float_le))

  CHECK_BB(import_values(importer))
  return 1;
}
