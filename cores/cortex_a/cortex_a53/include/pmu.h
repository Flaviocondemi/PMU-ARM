#ifndef PMU_A53_H
#define PMU_A53_H

// PMU Event Definitions
#define EVENT_SW_INCR                      0x00  // Software increment.
#define EVENT_L1I_CACHE_REFILL             0x01  // L1 Instruction cache refill.
#define EVENT_L1I_TLB_REFILL               0x02  // L1 Instruction TLB refill.
#define EVENT_L1D_CACHE_REFILL             0x03  // L1 Data cache refill.
#define EVENT_L1D_CACHE                    0x04  // L1 Data cache access.
#define EVENT_L1D_TLB_REFILL               0x05  // L1 Data TLB refill.
#define EVENT_LD_RETIRED                   0x06  // Load instruction executed.
#define EVENT_ST_RETIRED                   0x07  // Store instruction executed.
#define EVENT_INST_RETIRED                 0x08  // Instruction executed.
#define EVENT_INST_RETIRED_TWO             0x08  // Two instructions executed.
#define EVENT_EXC_TAKEN                    0x09  // Exception taken.
#define EVENT_EXC_RETURN                   0x0A  // Exception return.
#define EVENT_CID_WRITE_RETIRED            0x0B  // Context ID change retired.
#define EVENT_PC_WRITE_RETIRED             0x0C  // PC write instruction executed.
#define EVENT_BR_IMMED_RETIRED             0x0D  // Immediate branch executed.
#define EVENT_BR_RETURN_RETIRED            0x0E  // Procedure return executed.
#define EVENT_UNALIGNED_LDST_RETIRED       0x0F  // Unaligned load/store executed.
#define EVENT_BR_MIS_PRED                  0x10  // Mispredicted branch executed.
#define EVENT_CPU_CYCLES                   0x11  // CPU cycle.
#define EVENT_BR_PRED                      0x12  // Predicted branch executed.
#define EVENT_MEM_ACCESS                   0x13  // Data memory access.
#define EVENT_L1I_CACHE                    0x14  // L1 Instruction cache access.
#define EVENT_L1D_CACHE_WB                 0x15  // L1 Data cache Write-Back.
#define EVENT_L2D_CACHE                    0x16  // L2 Data cache access.
#define EVENT_L2D_CACHE_REFILL             0x17  // L2 Data cache refill.
#define EVENT_L2D_CACHE_WB                 0x18  // L2 Data cache Write-Back.
#define EVENT_BUS_ACCESS                   0x19  // Bus access.
#define EVENT_MEMORY_ERROR                 0x1A  // Local memory error.
#define EVENT_BUS_CYCLES                   0x1D  // Bus cycle.
#define EVENT_CHAIN                        0x1E  // Odd performance counter chain mode.
#define EVENT_BUS_ACCESS_LD                0x60  // Bus access - Read.
#define EVENT_BUS_ACCESS_ST                0x61  // Bus access - Write.
#define EVENT_BR_INDIRECT_SPEC             0x7A  // Indirect branch executed.
#define EVENT_EXC_IRQ                      0x86  // IRQ exception taken.
#define EVENT_EXC_FIQ                      0x87  // FIQ exception taken.
#define EVENT_EXTERNAL_MEMORY_REQUEST      0xC0  // External memory request.
#define EVENT_NONCACHE_MEMORY_REQUEST      0xC1  // Non-cacheable external memory request.
#define EVENT_PREFETCH_LINEFILL            0xC2  // Linefill due to prefetch.
#define EVENT_ICACHE_THROTTLE              0xC3  // Instruction cache throttle occurred.
#define EVENT_READ_ALLOC_ENTER             0xC4  // Entering read allocate mode.
#define EVENT_READ_ALLOC_ACTIVE            0xC5  // Read allocate mode.
#define EVENT_PREDECODE_ERROR              0xC6  // Pre-decode error.
#define EVENT_STORE_BUFFER_FULL            0xC7  // Pipeline stall due to full store buffer.
#define EVENT_SNOOPED_DATA                 0xC8  // Snooped data from another CPU.
#define EVENT_CONDITIONAL_BRANCH_EXEC      0xC9  // Conditional branch executed.
#define EVENT_INDIRECT_BRANCH_MISPRED      0xCA  // Indirect branch mispredicted.
#define EVENT_ADDR_MISCOMPARE              0xCB  // Address miscompare on indirect branch.
#define EVENT_CONDITIONAL_MISPREDICT       0xCC  // Conditional branch mispredicted.
#define EVENT_L1I_CACHE_ERROR              0xD0  // L1 Instruction cache error.
#define EVENT_L1D_CACHE_ERROR              0xD1  // L1 Data cache error.
#define EVENT_TLB_ERROR                    0xD2  // TLB memory error.
#define EVENT_ATTRIB_PERF_EMPTY_DPU        0xE0  // DPU IQ empty, not due to misses.
#define EVENT_ATTRIB_PERF_ICACHE_MISS      0xE1  // DPU IQ empty, instruction cache miss.
#define EVENT_ATTRIB_PERF_TLB_MISS         0xE2  // DPU IQ empty, micro-TLB miss.
#define EVENT_ATTRIB_PERF_PREDECODE_ERR    0xE3  // DPU IQ empty, pre-decode error.
#define EVENT_ATTRIB_PERF_INTERLOCK        0xE4  // Interlock, non-SIMD/FP stall.
#define EVENT_ATTRIB_PERF_LDST_INTERLOCK   0xE5  // Load/store interlock stall.
#define EVENT_ATTRIB_PERF_SIMD_INTERLOCK   0xE6  // SIMD/FP interlock stall.
#define EVENT_ATTRIB_PERF_WR_LOAD_STALL    0xE7  // Write stage stall due to load miss.
#define EVENT_ATTRIB_PERF_WR_STORE_STALL   0xE8  // Write stage stall due to store.


/** PMU API for ARM Cortex-A53 **/

/**
 * @brief Enable the PMU in user mode.
 * @details This function enables the PMU in user mode, 
 * allowing user-level
 */
static inline void arm_a53_pmu_enable_user_mode(void) {
    int value = 0;

    // Enable PMU, reset cycle counter, and event counters
    value |= 1;
    asm volatile("msr PMUSERENR_EL0, %0" : "=r"(value));
}

/**
 * @brief Enable the PMU and reset cycle/event counters.
 */
static inline void arm_a53_pmu_enable(void) {
    int value;

    // Read PMCR_EL0 (Performance Monitor Control Register)
    asm volatile("mrs %0, PMCR_EL0" : "=r"(value));

    // Enable PMU, reset cycle counter, and event counters
    value |= (1 << 0) | (1 << 2) | (1 << 3);
    asm volatile("msr PMCR_EL0, %0" : : "r"(value));
}

/**
 * @brief Enable the cycle counter.
 */
static inline void arm_a53_pmu_enable_cyclecounter(void) {
    int value = (1 << 31); // Enable bit 31 for the cycle counter
    asm volatile("msr PMCNTENSET_EL0, %0" : : "r"(value));
}

/**
 * @brief Disable the cycle counter.
 */
static inline void arm_a53_pmu_disable_cyclecounter(void) {
    int value = (1UL << 31); // Disable bit 31 for the cycle counter
    asm volatile("msr PMCNTENCLR_EL0, %0" : : "r"(value));
}

/**
 * @brief Read the cycle counter value.
 * @return The current cycle counter value.
 */
static inline int arm_a53_pmu_read_cyclecounter(void) {
    int value;

    // Read PMCCNTR_EL0 (Cycle Counter)
    asm volatile("mrs %0, PMCCNTR_EL0" : "=r"(value));
    return value;
}

/**
 * @brief Set an event type for a given counter.
 * @param counter Counter index (0-5).
 * @param event_type Event type to monitor.
 */
static inline void arm_a53_pmu_set_eventcounter(int counter, int event_type) {
    if (counter > 5) return; // Limit to event counters 0-5

    // Write the event type to PMEVTYPERn_EL0 (Event Type Register)
    asm volatile("msr PMEVTYPER%0_EL0, %1" : : "r"(counter), "r"(event_type));
}

/**
 * @brief Enable an event counter.
 * @param counter Counter index (0-5).
 */
static inline void arm_a53_pmu_enable_eventcounter(int counter) {
    if (counter > 5) return; // Limit to event counters 0-5

    int value = (1UL << counter);
    asm volatile("msr PMCNTENSET_EL0, %0" : : "r"(value));
}

/**
 * @brief Disable an event counter.
 * @param counter Counter index (0-5).
 */
static inline void arm_a53_pmu_disable_eventcounter(int counter) {
    if (counter > 5) return; // Limit to event counters 0-5

    int value = (1UL << counter);
    asm volatile("msr PMCNTENCLR_EL0, %0" : : "r"(value));
}

/**
 * @brief Read the value of an event counter.
 * @param counter Counter index (0-5).
 * @return The value of the event counter.
 */
static inline int arm_a53_pmu_read_eventcounter(int counter) {
    int value;
    if (counter > 5) return 0; // Limit to event counters 0-5

    // Read PMEVTCOUNTERn_EL0 (Event Counter Register)
    asm volatile("mrs %0, PMEVTCOUNTER%0_EL0" : "=r"(value) : "r"(counter));
    return value;
}

/**
 * @brief Reset all counters.
 */
static inline void arm_a53_pmu_reset_counters(void) {
    int value;

    // Read PMCR_EL0
    asm volatile("mrs %0, PMCR_EL0" : "=r"(value));

    // Reset cycle counter and event counters
    value |= (1 << 2) | (1 << 3);
    asm volatile("msr PMCR_EL0, %0" : : "r"(value));
}

/**
 * @brief Disable the PMU.
 */
static inline void arm_a53_pmu_disable(void) {
    int value;

    // Read PMCR_EL0
    asm volatile("mrs %0, PMCR_EL0" : "=r"(value));

    // Disable PMU
    value &= ~(1 << 0);
    asm volatile("msr PMCR_EL0, %0" : : "r"(value));
}

#endif /* PMU_A53_H */
