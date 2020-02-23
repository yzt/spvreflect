#if !defined(INTERNAL_SPVREFLECT_HEADER_GUARD__)
#define INTERNAL_SPVREFLECT_HEADER_GUARD__

#include <stdint.h>

typedef struct {
    uint32_t magic_number;
    uint8_t version_major, version_minor;
    uint32_t generator;
    uint32_t id_upper_bound;
    int instruction_count;
} spvrefl_info;

typedef enum {
    spvrefl_error_none = 0,
    spvrefl_error_unknown,
    spvrefl_error_bad_params,
    spvrefl_error_bad_input_length,
    spvrefl_error_bad_magic_number,
} spvrefl_error_code;

typedef struct {
    spvrefl_error_code error_code;
    int error_position_byte;
    spvrefl_info * reflection_info;
    int reflection_info_size;
} spvrefl_result;

spvrefl_result
spvrelf_reflect (
    void const * input_spirv,
    int input_size_bytes,
    void * scratch_memory,
    int scratch_memory_size_bytes
);

#if defined(SPVREFL_IMPLEMENTATION)
#include <stdio.h>

spvrefl_result
spvrelf_reflect (
    void const * input_spirv,
    int input_size_bytes,
    void * scratch_memory,
    int scratch_memory_size_bytes
) {
    spvrefl_result ret = {};
    uint8_t * scratch = (uint8_t *)scratch_memory;
    int scratch_left = scratch_memory_size_bytes;

    //ret.error_code = spvrefl_error_unknown;

    if (!input_spirv || input_size_bytes <= 0) {
        ret.error_code = spvrefl_error_bad_params;
        return ret;
    }
    if (input_size_bytes % 4 != 0 || input_size_bytes < 20) {
        ret.error_code = spvrefl_error_bad_input_length;
        return ret;
    }
//        (!scratch_memory || scratch_memory_size_bytes > 0
    int word_count = input_size_bytes / 4;
    uint32_t const * words = (uint32_t const *)input_spirv;
    uint32_t const * words_end = words + word_count;
    uint32_t const * words_cur = words;

    uint32_t magic_number = *words_cur++;
    if (magic_number != 0x07230203) {
        ret.error_code = spvrefl_error_bad_magic_number;
        return ret;
    }
    uint32_t version = *words_cur++;
    uint32_t generator = *words_cur++;
    uint32_t bound = *words_cur++;
    /**uint32_t reserved =/*/ (void)/**/*words_cur++;

    int instruction_count = 0;
    while (words_cur < words_end) {
        uint32_t w = *words_cur++;
        uint16_t wc = (uint16_t)(w >> 16);
        uint16_t op = (uint16_t)(w & 0xFFFF);
        instruction_count += 1;
        ::printf("- %hu, 0x%04hX\n", wc, op);

        for (unsigned i = 1; i < wc; ++i)
            words_cur++;
    }

    if (scratch && scratch_left >= sizeof(spvrefl_info)) {
        spvrefl_info * info = (spvrefl_info *)scratch;
        scratch += sizeof(*info);
        scratch_left -= sizeof(*info);

        info->magic_number = magic_number;
        info->version_major = (version >> 16) & 0xFF;
        info->version_minor = (version >>  8) & 0xFF;
        info->generator = generator;
        info->id_upper_bound = bound;
        info->instruction_count = instruction_count;

        ret.reflection_info = info;
        ret.reflection_info_size = scratch_memory_size_bytes - scratch_left;
    }

    return ret;
}

#endif  // SPVREFL_IMPLEMENTATION
#endif  // INTERNAL_SPVREFLECT_HEADER_GUARD__
