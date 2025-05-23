#pragma once

#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>

#define assert($Expression, ...)                                               \
  ((void)((!!($Expression))                                                    \
          || (cdbg_assert(__FILE__, __func__, __LINE__, #$Expression, true, ##__VA_ARGS__), 0)))

#define assert_soft($Expression, ...)                                          \
  ((void)((!!($Expression))                                                    \
          || (cdbg_assert(__FILE__, __func__, __LINE__, #$Expression, false, ##__VA_ARGS__), 0)))

void
cdbg_assert(
  const char *a_file,
  const char *a_function,
  uint64_t a_line,
  const char *a_expression,
  bool a_abort,
  ...
);

void
cdbg_abort();

typedef struct cdbg_breakpoint_s
{
  bool m_armed;
  struct
  {
    const char *m_file;
    const char *m_function;
    uint64_t m_line;
  } m_set_site;
  struct
  {
    jmp_buf m_buffer;
    const char *m_file;
    const char *m_function;
    uint64_t m_line;
  } m_jump_site;
} cdbg_breakpoint_t;

void
cdbg_breakpoint_set(
  cdbg_breakpoint_t *a_breakpoint,
  const char *a_file,
  const char *a_function,
  uint64_t a_line
);

void
cdbg_breakpoint_break(
  cdbg_breakpoint_t *a_breakpoint,
  const char *a_file,
  const char *a_function,
  uint64_t a_line
);

void
cdbg_breakpoint_clear(cdbg_breakpoint_t *a_breakpoint);

#define breakpoint_set($Breakpoint)                                            \
  (cdbg_breakpoint_set($Breakpoint, __FILE__, __func__, __LINE__))

#define breakpoint_trigger($Breakpoint)                                        \
  (cdbg_breakpoint_break($Breakpoint, __FILE__, __func__, __LINE__))

#define breakpoint_clear($Breakpoint) (cdbg_breakpoint_clear($Breakpoint))
