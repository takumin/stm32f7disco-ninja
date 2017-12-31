#ifndef DEF_MACRO_H
#define DEF_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

// Memory Section
#define ITCM __attribute__((section(".itcm")))
#define DTCM __attribute__((section(".dtcm")))

// No Used Variable
#define UNUSED(x) x __attribute__((unused))

#ifdef __cplusplus
}
#endif

#endif  // DEF_MACRO_H
