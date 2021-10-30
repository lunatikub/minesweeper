#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

/**
 * Provides helpers to declare functions can be used in unit-test but not in the
 * binaries.
 *
 * PROTOTYPE_FOR_UNIT_TEST: declare a prototype of function will be used in
 * unit-test. PRIVATE_EXCEPT_UNIT_TEST: function can be used in unit-test but
 * not in other modules.
 */

#ifdef UNIT_TEST_TARGET

#define PROTOTYPE_FOR_UNIT_TEST(prototype) prototype
#define PRIVATE_EXCEPT_UNIT_TEST

#else

#define PROTOTYPE_FOR_UNIT_TEST(prototype)
#define PRIVATE_EXCEPT_UNIT_TEST static inline

#endif

#endif /* !__UNIT_TEST_H__ */
