#ifndef ANANSI_CONTEXT_H
#define ANANSI_CONTEXT_H

#include <linux/module.h>

#include "types.h"

typedef struct {
    uint64_t low, high;
} uint128_t;

typedef struct {
    uint128_t low, high;
} uint256_t;

typedef struct {
    uint256_t low, high;
} uint512_t;

/* http://www.sandpile.org/x86/gpr.htm
 * Must match up with struct declaration in anansi_context.asm */
struct anansi_context {
    /* Traditional GPRs */
    uint64_t rax;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rbx;
    uint64_t rsp;
    uint64_t rbp;
    uint64_t rsi;
    /* rdi has been omitted because according to unix ABI, arguments
     * will be passed on registers */

    /* Additional GPRs */
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    /* Instruction pointer */
    uint64_t rip;

    /* Control registers */
    uint64_t cr0;
    uint64_t cr3;
    uint64_t cr4;

    /* Segment registers */
    uint16_t cs;
    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;

    /* TODO: Add SIMD registers too */
};

extern void
anansi_context_capture(struct anansi_context *ctx);

extern void
anansi_context_restore(struct anansi_context *ctx);

#endif /* ANANSI_CONTEXT_H */
