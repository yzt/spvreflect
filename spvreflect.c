//#if defined(SPVREFL_IMPLEMENTATION)
#include "spvreflect.h"

#include <stdio.h>
#define DEBUG_PRINT(...)    printf(__VA_ARGS__)

typedef struct {
    uint32_t code;
    spvrefl_capability_e enum_bit;
    spvrefl_capability_e also_declares_enum_bit [2];
    char const * str;
} spvrefl_internal_capability_entry_t;

static spvrefl_internal_capability_entry_t const spvrefl_internal_capability_data [] = {
    {   0, spvrefl_capability_Matrix, {-1, -1}, "Matrix"},
    {   1, spvrefl_capability_Shader, {spvrefl_capability_Matrix, -1}, "Shader"},
    {   2, spvrefl_capability_Geometry, {spvrefl_capability_Shader, -1}, "Geometry"},
    {   3, spvrefl_capability_Tessellation, {spvrefl_capability_Shader, -1}, "Tessellation"},
    {   4, spvrefl_capability_Addresses, {-1, -1}, "Addresses"},
    {   5, spvrefl_capability_Linkage, {-1, -1}, "Linkage"},
    {   6, spvrefl_capability_Kernel, {-1, -1}, "Kernel"},
    {   7, spvrefl_capability_Vector16, {spvrefl_capability_Kernel, -1}, "Vector16"},
    {   8, spvrefl_capability_Float16Buffer, {spvrefl_capability_Kernel, -1}, "Float16Buffer"},
    {   9, spvrefl_capability_Float16, {-1, -1}, "Float16"},
    {  10, spvrefl_capability_Float64, {-1, -1}, "Float64"},
    {  11, spvrefl_capability_Int64, {-1, -1}, "Int64"},
    {  12, spvrefl_capability_Int64Atomics, {spvrefl_capability_Int64, -1}, "Int64Atomics"},
    {  13, spvrefl_capability_ImageBasic, {spvrefl_capability_Kernel, -1}, "ImageBasic"},
    {  14, spvrefl_capability_ImageReadWrite, {spvrefl_capability_ImageBasic, -1}, "ImageReadWrite"},
    {  15, spvrefl_capability_ImageMipmap, {spvrefl_capability_ImageBasic, -1}, "ImageMipmap"},
    {  17, spvrefl_capability_Pipes, {spvrefl_capability_Kernel, -1}, "Pipes"},
    {  18, spvrefl_capability_Groups, {-1, -1}, "Groups"},
    {  19, spvrefl_capability_DeviceEnqueue, {spvrefl_capability_Kernel, -1}, "DeviceEnqueue"},
    {  20, spvrefl_capability_LiteralSampler, {spvrefl_capability_Kernel, -1}, "LiteralSampler"},
    {  21, spvrefl_capability_AtomicStorage, {spvrefl_capability_Shader, -1}, "AtomicStorage"},
    {  22, spvrefl_capability_Int16, {-1, -1}, "Int16"},
    {  23, spvrefl_capability_TessellationPointSize, {spvrefl_capability_Tessellation, -1}, "TessellationPointSize"},
    {  24, spvrefl_capability_GeometryPointSize, {spvrefl_capability_Geometry, -1}, "GeometryPointSize"},
    {  25, spvrefl_capability_ImageGatherExtended, {spvrefl_capability_Shader, -1}, "ImageGatherExtended"},
    {  27, spvrefl_capability_StorageImageMultisample, {spvrefl_capability_Shader, -1}, "StorageImageMultisample"},
    {  28, spvrefl_capability_UniformBufferArrayDynamicIndexing, {spvrefl_capability_Shader, -1}, "UniformBufferArrayDynamicIndexing"},
    {  29, spvrefl_capability_SampledImageArrayDynamicIndexing, {spvrefl_capability_Shader, -1}, "SampledImageArrayDynamicIndexing"},
    {  30, spvrefl_capability_StorageBufferArrayDynamicIndexing, {spvrefl_capability_Shader, -1}, "StorageBufferArrayDynamicIndexing"},
    {  31, spvrefl_capability_StorageImageArrayDynamicIndexing, {spvrefl_capability_Shader, -1}, "StorageImageArrayDynamicIndexing"},
    {  32, spvrefl_capability_ClipDistance, {spvrefl_capability_Shader, -1}, "ClipDistance"},
    {  33, spvrefl_capability_CullDistance, {spvrefl_capability_Shader, -1}, "CullDistance"},
    {  34, spvrefl_capability_ImageCubeArray, {spvrefl_capability_SampledCubeArray, -1}, "ImageCubeArray"},
    {  35, spvrefl_capability_SampleRateShading, {spvrefl_capability_Shader, -1}, "SampleRateShading"},
    {  36, spvrefl_capability_ImageRect, {spvrefl_capability_SampledRect, -1}, "ImageRect"},
    {  37, spvrefl_capability_SampledRect, {spvrefl_capability_Shader, -1}, "SampledRect"},
    {  38, spvrefl_capability_GenericPointer, {spvrefl_capability_Addresses, -1}, "GenericPointer"},
    {  39, spvrefl_capability_Int8, {-1, -1}, "Int8"},
    {  40, spvrefl_capability_InputAttachment, {spvrefl_capability_Shader, -1}, "InputAttachment"},
    {  41, spvrefl_capability_SparseResidency, {spvrefl_capability_Shader, -1}, "SparseResidency"},
    {  42, spvrefl_capability_MinLod, {spvrefl_capability_Shader, -1}, "MinLod"},
    {  43, spvrefl_capability_Sampled1D, {-1, -1}, "Sampled1D"},
    {  44, spvrefl_capability_Image1D, {spvrefl_capability_Sampled1D, -1}, "Image1D"},
    {  45, spvrefl_capability_SampledCubeArray, {spvrefl_capability_Shader, -1}, "SampledCubeArray"},
    {  46, spvrefl_capability_SampledBuffer, {-1, -1}, "SampledBuffer"},
    {  47, spvrefl_capability_ImageBuffer, {spvrefl_capability_SampledBuffer, -1}, "ImageBuffer"},
    {  48, spvrefl_capability_ImageMSArray, {spvrefl_capability_Shader, -1}, "ImageMSArray"},
    {  49, spvrefl_capability_StorageImageExtendedFormats, {spvrefl_capability_Shader, -1}, "StorageImageExtendedFormats"},
    {  50, spvrefl_capability_ImageQuery, {spvrefl_capability_Shader, -1}, "ImageQuery"},
    {  51, spvrefl_capability_DerivativeControl, {spvrefl_capability_Shader, -1}, "DerivativeControl"},
    {  52, spvrefl_capability_InterpolationFunction, {spvrefl_capability_Shader, -1}, "InterpolationFunction"},
    {  53, spvrefl_capability_TransformFeedback, {spvrefl_capability_Shader, -1}, "TransformFeedback"},
    {  54, spvrefl_capability_GeometryStreams, {spvrefl_capability_Geometry, -1}, "GeometryStreams"},
    {  55, spvrefl_capability_StorageImageReadWithoutFormat, {spvrefl_capability_Shader, -1}, "StorageImageReadWithoutFormat"},
    {  56, spvrefl_capability_StorageImageWriteWithoutFormat, {spvrefl_capability_Shader, -1}, "StorageImageWriteWithoutFormat"},
    {  57, spvrefl_capability_MultiViewport, {spvrefl_capability_Geometry, -1}, "MultiViewport"},
    {  58, spvrefl_capability_SubgroupDispatch, {spvrefl_capability_DeviceEnqueue, -1}, "SubgroupDispatch"},
    {  59, spvrefl_capability_NamedBarrier, {spvrefl_capability_Kernel, -1}, "NamedBarrier"},
    {  60, spvrefl_capability_PipeStorage, {spvrefl_capability_Pipes, -1}, "PipeStorage"},
    {  61, spvrefl_capability_GroupNonUniform, {-1, -1}, "GroupNonUniform"},
    {  62, spvrefl_capability_GroupNonUniformVote, {spvrefl_capability_GroupNonUniform, -1}, "GroupNonUniformVote"},
    {  63, spvrefl_capability_GroupNonUniformArithmetic, {spvrefl_capability_GroupNonUniform, -1}, "GroupNonUniformArithmetic"},
    {  64, spvrefl_capability_GroupNonUniformBallot, {spvrefl_capability_GroupNonUniform, -1}, "GroupNonUniformBallot"},
    {  65, spvrefl_capability_GroupNonUniformShuffle, {spvrefl_capability_GroupNonUniform, -1}, "GroupNonUniformShuffle"},
    {  66, spvrefl_capability_GroupNonUniformShuffleRelative, {spvrefl_capability_GroupNonUniform, -1}, "GroupNonUniformShuffleRelative"},
    {  67, spvrefl_capability_GroupNonUniformClustered, {spvrefl_capability_GroupNonUniform, -1}, "GroupNonUniformClustered"},
    {  68, spvrefl_capability_GroupNonUniformQuad, {spvrefl_capability_GroupNonUniform, -1}, "GroupNonUniformQuad"},
    {  69, spvrefl_capability_ShaderLayer, {-1, -1}, "ShaderLayer"},
    {  70, spvrefl_capability_ShaderViewportIndex, {-1, -1}, "ShaderViewportIndex"},
    {4423, spvrefl_capability_SubgroupBallotKHR, {-1, -1}, "SubgroupBallotKHR"},
    {4427, spvrefl_capability_DrawParameters, {spvrefl_capability_Shader, -1}, "DrawParameters"},
    {4431, spvrefl_capability_SubgroupVoteKHR, {-1, -1}, "SubgroupVoteKHR"},
    {4433, spvrefl_capability_StorageBuffer16BitAccess, {-1, -1}, "StorageBuffer16BitAccess"},
    //{4433, spvrefl_capability_StorageUniformBufferBlock16, {-1, -1}, "StorageUniformBufferBlock16"},
    {4434, spvrefl_capability_UniformAndStorageBuffer16BitAccess, {spvrefl_capability_StorageBuffer16BitAccess, -1}, "UniformAndStorageBuffer16BitAccess"},
    //{4434, spvrefl_capability_StorageUniform16, {spvrefl_capability_StorageBuffer16BitAccess, spvrefl_capability_StorageUniformBufferBlock16}, "StorageUniform16"},
    {4435, spvrefl_capability_StoragePushConstant16, {-1, -1}, "StoragePushConstant16"},
    {4436, spvrefl_capability_StorageInputOutput16, {-1, -1}, "StorageInputOutput16"},
    {4437, spvrefl_capability_DeviceGroup, {-1, -1}, "DeviceGroup"},
    {4439, spvrefl_capability_MultiView, {spvrefl_capability_Shader, -1}, "MultiView"},
    {4441, spvrefl_capability_VariablePointersStorageBuffer, {spvrefl_capability_Shader, -1}, "VariablePointersStorageBuffer"},
    {4442, spvrefl_capability_VariablePointers, {spvrefl_capability_VariablePointersStorageBuffer, -1}, "VariablePointers"},
    {4445, spvrefl_capability_AtomicStorageOps, {-1, -1}, "AtomicStorageOps"},
    {4447, spvrefl_capability_SampleMaskPostDepthCoverage, {-1, -1}, "SampleMaskPostDepthCoverage"},
    {4448, spvrefl_capability_StorageBuffer8BitAccess, {-1, -1}, "StorageBuffer8BitAccess"},
    {4449, spvrefl_capability_UniformAndStorageBuffer8BitAccess, {spvrefl_capability_StorageBuffer8BitAccess, -1}, "UniformAndStorageBuffer8BitAccess"},
    {4450, spvrefl_capability_StoragePushConstant8, {-1, -1}, "StoragePushConstant8"},
    {4464, spvrefl_capability_DenormPreserve, {-1, -1}, "DenormPreserve"},
    {4465, spvrefl_capability_DenormFlushToZero, {-1, -1}, "DenormFlushToZero"},
    {4466, spvrefl_capability_SignedZeroInfNanPreserve, {-1, -1}, "SignedZeroInfNanPreserve"},
    {4467, spvrefl_capability_RoundingModeRTE, {-1, -1}, "RoundingModeRTE"},
    {4468, spvrefl_capability_RoundingModeRTZ, {-1, -1}, "RoundingModeRTZ"},
    {5008, spvrefl_capability_Float16ImageAMD, {spvrefl_capability_Shader, -1}, "Float16ImageAMD"},
    {5009, spvrefl_capability_ImageGatherBiasLodAMD, {spvrefl_capability_Shader, -1}, "ImageGatherBiasLodAMD"},
    {5010, spvrefl_capability_FragmentMaskAMD, {spvrefl_capability_Shader, -1}, "FragmentMaskAMD"},
    {5013, spvrefl_capability_StencilExportEXT, {spvrefl_capability_Shader, -1}, "StencilExportEXT"},
    {5015, spvrefl_capability_ImageReadWriteLodAMD, {spvrefl_capability_Shader, -1}, "ImageReadWriteLodAMD"},
    {5055, spvrefl_capability_ShaderClockKHR, {spvrefl_capability_Shader, -1}, "ShaderClockKHR"},
    {5249, spvrefl_capability_SampleMaskOverrideCoverageNV, {spvrefl_capability_SampleRateShading, -1}, "SampleMaskOverrideCoverageNV"},
    {5251, spvrefl_capability_GeometryShaderPassthroughNV, {spvrefl_capability_Geometry, -1}, "GeometryShaderPassthroughNV"},
    {5254, spvrefl_capability_ShaderViewportIndexLayerEXT, {spvrefl_capability_MultiViewport, -1}, "ShaderViewportIndexLayerEXT"},
    //{5254, spvrefl_capability_ShaderViewportIndexLayerNV, {spvrefl_capability_MultiViewport, -1}, "ShaderViewportIndexLayerNV"},
    {5255, spvrefl_capability_ShaderViewportMaskNV, {spvrefl_capability_ShaderViewportIndexLayerEXT, -1}, "ShaderViewportMaskNV"},
    {5259, spvrefl_capability_ShaderStereoViewNV, {spvrefl_capability_ShaderViewportMaskNV, -1}, "ShaderStereoViewNV"},
    {5260, spvrefl_capability_PerViewAttributesNV, {spvrefl_capability_MultiView, -1}, "PerViewAttributesNV"},
    {5265, spvrefl_capability_FragmentFullyCoveredEXT, {spvrefl_capability_Shader, -1}, "FragmentFullyCoveredEXT"},
    {5266, spvrefl_capability_MeshShadingNV, {spvrefl_capability_Shader, -1}, "MeshShadingNV"},
    {5282, spvrefl_capability_ImageFootprintNV, {-1, -1}, "ImageFootprintNV"},
    {5284, spvrefl_capability_FragmentBarycentricNV, {-1, -1}, "FragmentBarycentricNV"},
    {5288, spvrefl_capability_ComputeDerivativeGroupQuadsNV, {-1, -1}, "ComputeDerivativeGroupQuadsNV"},
    {5291, spvrefl_capability_FragmentDensityEXT, {spvrefl_capability_Shader, -1}, "FragmentDensityEXT"},
    {5291, spvrefl_capability_ShadingRateNV, {spvrefl_capability_Shader, -1}, "ShadingRateNV"},
    {5297, spvrefl_capability_GroupNonUniformPartitionedNV, {-1, -1}, "GroupNonUniformPartitionedNV"},
    {5301, spvrefl_capability_ShaderNonUniform, {spvrefl_capability_Shader, -1}, "ShaderNonUniform"},
    //{5301, spvrefl_capability_ShaderNonUniformEXT, {spvrefl_capability_Shader, -1}, "ShaderNonUniformEXT"},
    {5302, spvrefl_capability_RuntimeDescriptorArray, {spvrefl_capability_Shader, -1}, "RuntimeDescriptorArray"},
    //{5302, spvrefl_capability_RuntimeDescriptorArrayEXT, {spvrefl_capability_Shader, -1}, "RuntimeDescriptorArrayEXT"},
    {5303, spvrefl_capability_InputAttachmentArrayDynamicIndexing, {spvrefl_capability_InputAttachment, -1}, "InputAttachmentArrayDynamicIndexing"},
    //{5303, spvrefl_capability_InputAttachmentArrayDynamicIndexingEXT, {spvrefl_capability_InputAttachment, -1}, "InputAttachmentArrayDynamicIndexingEXT"},
    {5304, spvrefl_capability_UniformTexelBufferArrayDynamicIndexing, {spvrefl_capability_SampledBuffer, -1}, "UniformTexelBufferArrayDynamicIndexing"},
    //{5304, spvrefl_capability_UniformTexelBufferArrayDynamicIndexingEXT, {spvrefl_capability_SampledBuffer, -1}, "UniformTexelBufferArrayDynamicIndexingEXT"},
    {5305, spvrefl_capability_StorageTexelBufferArrayDynamicIndexing, {spvrefl_capability_ImageBuffer, -1}, "StorageTexelBufferArrayDynamicIndexing"},
    //{5305, spvrefl_capability_StorageTexelBufferArrayDynamicIndexingEXT, {spvrefl_capability_ImageBuffer, -1}, "StorageTexelBufferArrayDynamicIndexingEXT"},
    {5306, spvrefl_capability_UniformBufferArrayNonUniformIndexing, {spvrefl_capability_ShaderNonUniform, -1}, "UniformBufferArrayNonUniformIndexing"},
    //{5306, spvrefl_capability_UniformBufferArrayNonUniformIndexingEXT, {spvrefl_capability_ShaderNonUniform, -1}, "UniformBufferArrayNonUniformIndexingEXT"},
    {5307, spvrefl_capability_SampledImageArrayNonUniformIndexing, {spvrefl_capability_ShaderNonUniform, -1}, "SampledImageArrayNonUniformIndexing"},
    //{5307, spvrefl_capability_SampledImageArrayNonUniformIndexingEXT, {spvrefl_capability_ShaderNonUniform, -1}, "SampledImageArrayNonUniformIndexingEXT"},
    {5308, spvrefl_capability_StorageBufferArrayNonUniformIndexing, {spvrefl_capability_ShaderNonUniform, -1}, "StorageBufferArrayNonUniformIndexing"},
    //{5308, spvrefl_capability_StorageBufferArrayNonUniformIndexingEXT, {spvrefl_capability_ShaderNonUniform, -1}, "StorageBufferArrayNonUniformIndexingEXT"},
    {5309, spvrefl_capability_StorageImageArrayNonUniformIndexing, {spvrefl_capability_ShaderNonUniform, -1}, "StorageImageArrayNonUniformIndexing"},
    //{5309, spvrefl_capability_StorageImageArrayNonUniformIndexingEXT, {spvrefl_capability_ShaderNonUniform, -1}, "StorageImageArrayNonUniformIndexingEXT"},
    {5310, spvrefl_capability_InputAttachmentArrayNonUniformIndexing, {spvrefl_capability_InputAttachment, spvrefl_capability_ShaderNonUniform}, "InputAttachmentArrayNonUniformIndexing"},
    //{5310, spvrefl_capability_InputAttachmentArrayNonUniformIndexingEXT, {spvrefl_capability_InputAttachment, spvrefl_capability_ShaderNonUniform}, "InputAttachmentArrayNonUniformIndexingEXT"},
    {5311, spvrefl_capability_UniformTexelBufferArrayNonUniformIndexing, {spvrefl_capability_SampledBuffer, spvrefl_capability_ShaderNonUniform}, "UniformTexelBufferArrayNonUniformIndexing"},
    //{5311, spvrefl_capability_UniformTexelBufferArrayNonUniformIndexingEXT, {spvrefl_capability_SampledBuffer, spvrefl_capability_ShaderNonUniform}, "UniformTexelBufferArrayNonUniformIndexingEXT"},
    {5312, spvrefl_capability_StorageTexelBufferArrayNonUniformIndexing, {spvrefl_capability_ImageBuffer, spvrefl_capability_ShaderNonUniform}, "StorageTexelBufferArrayNonUniformIndexing"},
    //{5312, spvrefl_capability_StorageTexelBufferArrayNonUniformIndexingEXT, {spvrefl_capability_ImageBuffer, spvrefl_capability_ShaderNonUniform}, "StorageTexelBufferArrayNonUniformIndexingEXT"},
    {5340, spvrefl_capability_RayTracingNV, {spvrefl_capability_Shader, -1}, "RayTracingNV"},
    {5345, spvrefl_capability_VulkanMemoryModel, {-1, -1}, "VulkanMemoryModel"},
    //{5345, spvrefl_capability_VulkanMemoryModelKHR, {-1, -1}, "VulkanMemoryModelKHR"},
    {5346, spvrefl_capability_VulkanMemoryModelDeviceScope, {-1, -1}, "VulkanMemoryModelDeviceScope"},
    //{5346, spvrefl_capability_VulkanMemoryModelDeviceScopeKHR, {-1, -1}, "VulkanMemoryModelDeviceScopeKHR"},
    {5347, spvrefl_capability_PhysicalStorageBufferAddresses, {spvrefl_capability_Shader, -1}, "PhysicalStorageBufferAddresses"},
    //{5347, spvrefl_capability_PhysicalStorageBufferAddressesEXT, {spvrefl_capability_Shader, -1}, "PhysicalStorageBufferAddressesEXT"},
    {5350, spvrefl_capability_ComputeDerivativeGroupLinearNV, {-1, -1}, "ComputeDerivativeGroupLinearNV"},
    {5357, spvrefl_capability_CooperativeMatrixNV, {spvrefl_capability_Shader, -1}, "CooperativeMatrixNV"},
    {5363, spvrefl_capability_FragmentShaderSampleInterlockEXT, {spvrefl_capability_Shader, -1}, "FragmentShaderSampleInterlockEXT"},
    {5372, spvrefl_capability_FragmentShaderShadingRateInterlockEXT, {spvrefl_capability_Shader, -1}, "FragmentShaderShadingRateInterlockEXT"},
    {5373, spvrefl_capability_ShaderSMBuiltinsNV, {spvrefl_capability_Shader, -1}, "ShaderSMBuiltinsNV"},
    {5378, spvrefl_capability_FragmentShaderPixelInterlockEXT, {spvrefl_capability_Shader, -1}, "FragmentShaderPixelInterlockEXT"},
    {5379, spvrefl_capability_DemoteToHelperInvocationEXT, {spvrefl_capability_Shader, -1}, "DemoteToHelperInvocationEXT"},
    {5568, spvrefl_capability_SubgroupShuffleINTEL, {-1, -1}, "SubgroupShuffleINTEL"},
    {5569, spvrefl_capability_SubgroupBufferBlockIOINTEL, {-1, -1}, "SubgroupBufferBlockIOINTEL"},
    {5570, spvrefl_capability_SubgroupImageBlockIOINTEL, {-1, -1}, "SubgroupImageBlockIOINTEL"},
    {5579, spvrefl_capability_SubgroupImageMediaBlockIOINTEL, {-1, -1}, "SubgroupImageMediaBlockIOINTEL"},
    {5584, spvrefl_capability_IntegerFunctions2INTEL, {spvrefl_capability_Shader, -1}, "IntegerFunctions2INTEL"},
    {5696, spvrefl_capability_SubgroupAvcMotionEstimationINTEL, {-1, -1}, "SubgroupAvcMotionEstimationINTEL"},
    {5697, spvrefl_capability_SubgroupAvcMotionEstimationIntraINTEL, {-1, -1}, "SubgroupAvcMotionEstimationIntraINTEL"},
    {5698, spvrefl_capability_SubgroupAvcMotionEstimationChromaINTEL, {-1, -1}, "SubgroupAvcMotionEstimationChromaINTEL"},
};

typedef struct {
    uint32_t const * ptr_begin;
    uint32_t const * ptr_end;
    uint32_t const * ptr_cur;

    uint32_t cur_word;
    uint16_t inst_word_count;
    uint16_t inst_opcode;
} spvrefl_internal_input_t;

static void
spvrefl_internal_input_init (spvrefl_internal_input_t * input, void const * data, int size_in_words) {
    input->ptr_begin = (uint32_t const *)data;
    input->ptr_end = input->ptr_begin + size_in_words;
    input->ptr_cur = input->ptr_begin;
}

static bool
spvrefl_internal_input_ended (spvrefl_internal_input_t const * input) {
    return !input || !input->ptr_cur || input->ptr_cur >= input->ptr_end;
}

static uint32_t
spvrefl_internal_input_advance_data (spvrefl_internal_input_t * input) {
    if (input->ptr_cur < input->ptr_end)
        input->cur_word = *input->ptr_cur++;
    else
        input->cur_word = 0;
    return input->cur_word;
}

static void
spvrefl_internal_input_advance_instruction (spvrefl_internal_input_t * input) {
    spvrefl_internal_input_advance_data(input);
    input->inst_word_count = (uint16_t)(input->cur_word >> 16);
    input->inst_opcode = (uint16_t)(input->cur_word & 0xFFFF);
}

spvrefl_result_t
spvrelf_reflect (
    void const * input_spirv,
    int input_size_bytes,
    void * scratch_memory,
    int scratch_memory_size_bytes
) {
    spvrefl_result_t ret = {0};
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
    spvrefl_internal_input_t input_storage;
    spvrefl_internal_input_t * input = &input_storage;
    spvrefl_internal_input_init(input, input_spirv, input_size_bytes / 4);

    uint32_t magic_number = spvrefl_internal_input_advance_data(input);
    if (magic_number != 0x07230203) {
        ret.error_code = spvrefl_error_bad_magic_number;
        return ret;
    }
    uint32_t version = spvrefl_internal_input_advance_data(input);
    uint32_t generator = spvrefl_internal_input_advance_data(input);
    uint32_t bound = spvrefl_internal_input_advance_data(input);
    /*uint32_t reserved =*/ spvrefl_internal_input_advance_data(input);

    int instruction_count = 0;
    while (!spvrefl_internal_input_ended(input)) {
        spvrefl_internal_input_advance_instruction(input);
        instruction_count += 1;
        DEBUG_PRINT("- %hu, 0x%04hX\n", input->inst_word_count, input->inst_opcode);

        switch (input->inst_opcode) {
        case 17: {                      // OpCapability
            spvrefl_internal_input_advance_data(input);
            //uint32_t cap = input->cur_word;
        } break;
        default: {
            for (unsigned i = 1; i < input->inst_word_count; ++i)
                spvrefl_internal_input_advance_data(input);
        } break;
        }
    }

    if (scratch && scratch_left >= sizeof(spvrefl_info_t)) {
        spvrefl_info_t * info = (spvrefl_info_t *)scratch;
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

//#endif  // SPVREFL_IMPLEMENTATION
