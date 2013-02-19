#ifndef __ASSERT_X_HPP__
#define __ASSERT_X_HPP__

#include <stdio.h>
#include <stdlib.h>

// c http://www.semicomplete.com/blog/geekery/insist-on-better-asserts.html
#define INSIST(conditional, args...) \
  ( \
    (conditional) ? (void)(0) : ( \
      fprintf(stderr, "Assertion failed %s:%d in %s(), INSIST(%s): ", \
              __FILE__, __LINE__, __PRETTY_FUNCTION__, __STRING(conditional)), \
      fprintf(stderr, ## args), \
      fprintf(stderr, "\n"), \
      abort() \
    ) \
  )

#define INSIST_RETURN(conditional, return_value, args...) \
  if (!(conditional)) { \
      fprintf(stderr, "Assertion failed %s:%d in %s(), INSIST_RETURN(%s): ", \
              __FILE__, __LINE__, __PRETTY_FUNCTION__, __STRING(conditional)); \
      fprintf(stderr, ## args); \
      fprintf(stderr, "\n"); \
      return(return_value); \
  }

#endif // __ASSERT_X_HPP__

