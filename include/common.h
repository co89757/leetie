#ifndef COMMON_H__
#define COMMON_H__
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#define BUFSIZE 1024

#if defined(__gnu_linux__) || defined(__GNU__)
#define LEETIE_GNU
#include <cxxabi.h>
#include <execinfo.h>

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline void print_stacktrace(FILE* out = stderr,
                                    unsigned int max_frames = 63) {
  fprintf(out, "stack trace:\n");

  // storage array for stack trace address data
  void* addrlist[max_frames + 1];

  // retrieve current stack addresses
  int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

  if (addrlen == 0) {
    fprintf(out, "  <empty, possibly corrupt>\n");
    return;
  }

  // resolve addresses into strings containing "filename(function+address)",
  // this array must be free()-ed
  char** symbollist = backtrace_symbols(addrlist, addrlen);

  // allocate string which will be filled with the demangled function name
  size_t funcnamesize = 256;
  char* funcname = (char*)malloc(funcnamesize);

  // iterate over the returned symbol lines. skip the first, it is the
  // address of this function.
  for (int i = 1; i < addrlen; i++) {
    char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

    // find parentheses and +address offset surrounding the mangled name:
    // ./module(function+0x15c) [0x8048a6d]
    for (char* p = symbollist[i]; *p; ++p) {
      if (*p == '(')
        begin_name = p;
      else if (*p == '+')
        begin_offset = p;
      else if (*p == ')' && begin_offset) {
        end_offset = p;
        break;
      }
    }

    if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
      *begin_name++ = '\0';
      *begin_offset++ = '\0';
      *end_offset = '\0';

      // mangled name is now in [begin_name, begin_offset) and caller
      // offset in [begin_offset, end_offset). now apply
      // __cxa_demangle():

      int status;
      char* ret =
          abi::__cxa_demangle(begin_name, funcname, &funcnamesize, &status);
      if (status == 0) {
        funcname = ret;  // use possibly realloc()-ed string
        fprintf(out, "  %s : %s+%s\n", symbollist[i], funcname, begin_offset);
      } else {
        // demangling failed. Output function name as a C function with
        // no arguments.
        fprintf(out, "  %s : %s()+%s\n", symbollist[i], begin_name,
                begin_offset);
      }
    } else {
      // couldn't parse the line? print the whole line.
      fprintf(out, "  %s\n", symbollist[i]);
    }
  }

  free(funcname);
  free(symbollist);
}

#endif

static inline void ensure(bool expr, const char* fmt, ...) {
  char buf[BUFSIZ];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
  if (!expr) {
    fprintf(stderr, "%s", buf);
  } else {
    printf("\n==== OK ====\n");
  }
}

#if defined(__GNUC__)
#define __func__ __PRETTY_FUNCTION__
#endif

#define ASSERT(cond, fmt, ...)                                 \
  do {                                                         \
    if (cond) {                                                \
      printf("=== [AssertOK]===: (" #cond ")\n");              \
    } else {                                                   \
      ensure(cond,                                             \
             "[AssertFail] %s:%d:%s:\n"                        \
             "[Msg]:" fmt "\n[Failed Condition]: " #cond "\n", \
             __FILE__, __LINE__, __func__, ##__VA_ARGS__);     \
    }                                                          \
  } while (0)

template <typename E>
void Throwf(const char* fmt, ...) {
  char buf[BUFSIZ];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof buf, fmt, ap);
  va_end(ap);
  throw E(std::string(buf).c_str());
}

#define THROW_FMT(EXCEPTION, fmt, ...)                                  \
  Throwf<EXCEPTION>("[Error] %s:%d:%s:\n" fmt "\n", __FILE__, __LINE__, \
                    __func__, ##__VA_ARGS__)

std::vector<std::string> split(const char* s, const char* delim);

//************** COMMON DATA STRUCTURES ************//
/** List ***/
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int k) : val(k), next(NULL) {}
};

ListNode* createList(const std::initializer_list<int>& keys);
void printList(ListNode* head);
void freeList(ListNode* head);

/** Binary Tree ***/
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};
void tree_preorderPrint(TreeNode* root);
void tree_postorderPrint(TreeNode* root);

TreeNode* deserializeTree(const char* s);
std::string serializeTree(TreeNode* root);

#endif
