#if !defined(INTERNAL_SPVREFLECT_HEADER_GUARD__)
#define INTERNAL_SPVREFLECT_HEADER_GUARD__

#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(SPVREFL_OPT_MAX_USED_EXTENSIONS)
    #define SPVREFL_OPT_MAX_USED_EXTENSIONS                         4
#endif
#if !defined(SPVREFL_OPT_MAX_USED_EXTENDED_INSTRUCTION_SET_IMPORT)
    #define SPVREFL_OPT_MAX_USED_EXTENDED_INSTRUCTION_SET_IMPORT    4
#endif
#if !defined(SPVREFL_OPT_MAX_USED_SOURCE_EXTENSIONS)
    #define SPVREFL_OPT_MAX_USED_SOURCE_EXTENSIONS                  4
#endif
#if !defined(SPVREFL_OPT_MAX_STRUCT_COUNT)
    #define SPVREFL_OPT_MAX_STRUCT_COUNT                            16
#endif
#if !defined(SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT)
    #define SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT                     16
#endif

typedef enum {
    spvrefl_error_none = 0,
    spvrefl_error_unknown,
    spvrefl_error_bad_params,
    spvrefl_error_bad_input_length,
    spvrefl_error_bad_magic_number,
    spvrefl_error_insufficient_scratch_mem,
} spvrefl_error_e;

typedef enum {
    spvrefl_sourcelang_Unknown     = 0, // NOTE: These values are based on the spec and mustn't change
    spvrefl_sourcelang_ESSL        = 1,
    spvrefl_sourcelang_GLSL        = 2,
    spvrefl_sourcelang_OpenCL_C    = 3,
    spvrefl_sourcelang_OpenCL_CPP  = 4,
    spvrefl_sourcelang_HLSL        = 5,
} spvrefl_sourcelang_e;

typedef enum {
    spvrefl_idtype_unknown = 0,
    spvrefl_idtype_source_file_name,
    spvrefl_idtype_struct,
} spvrefl_idtype_e;

typedef enum {
    spvrefl_capability_Matrix,
    spvrefl_capability_Shader,
    spvrefl_capability_Geometry,
    spvrefl_capability_Tessellation,
    spvrefl_capability_Addresses,
    spvrefl_capability_Linkage,
    spvrefl_capability_Kernel,
    spvrefl_capability_Vector16,
    spvrefl_capability_Float16Buffer,
    spvrefl_capability_Float16,
    spvrefl_capability_Float64,
    spvrefl_capability_Int64,
    spvrefl_capability_Int64Atomics,
    spvrefl_capability_ImageBasic,
    spvrefl_capability_ImageReadWrite,
    spvrefl_capability_ImageMipmap,
    spvrefl_capability_Pipes,
    spvrefl_capability_Groups,
    spvrefl_capability_DeviceEnqueue,
    spvrefl_capability_LiteralSampler,
    spvrefl_capability_AtomicStorage,
    spvrefl_capability_Int16,
    spvrefl_capability_TessellationPointSize,
    spvrefl_capability_GeometryPointSize,
    spvrefl_capability_ImageGatherExtended,
    spvrefl_capability_StorageImageMultisample,
    spvrefl_capability_UniformBufferArrayDynamicIndexing,
    spvrefl_capability_SampledImageArrayDynamicIndexing,
    spvrefl_capability_StorageBufferArrayDynamicIndexing,
    spvrefl_capability_StorageImageArrayDynamicIndexing,
    spvrefl_capability_ClipDistance,
    spvrefl_capability_CullDistance,
    spvrefl_capability_ImageCubeArray,
    spvrefl_capability_SampleRateShading,
    spvrefl_capability_ImageRect,
    spvrefl_capability_SampledRect,
    spvrefl_capability_GenericPointer,
    spvrefl_capability_Int8,
    spvrefl_capability_InputAttachment,
    spvrefl_capability_SparseResidency,
    spvrefl_capability_MinLod,
    spvrefl_capability_Sampled1D,
    spvrefl_capability_Image1D,
    spvrefl_capability_SampledCubeArray,
    spvrefl_capability_SampledBuffer,
    spvrefl_capability_ImageBuffer,
    spvrefl_capability_ImageMSArray,
    spvrefl_capability_StorageImageExtendedFormats,
    spvrefl_capability_ImageQuery,
    spvrefl_capability_DerivativeControl,
    spvrefl_capability_InterpolationFunction,
    spvrefl_capability_TransformFeedback,
    spvrefl_capability_GeometryStreams,
    spvrefl_capability_StorageImageReadWithoutFormat,
    spvrefl_capability_StorageImageWriteWithoutFormat,
    spvrefl_capability_MultiViewport,
    spvrefl_capability_SubgroupDispatch,
    spvrefl_capability_NamedBarrier,
    spvrefl_capability_PipeStorage,
    spvrefl_capability_GroupNonUniform,
    spvrefl_capability_GroupNonUniformVote,
    spvrefl_capability_GroupNonUniformArithmetic,
    spvrefl_capability_GroupNonUniformBallot,
    spvrefl_capability_GroupNonUniformShuffle,
    spvrefl_capability_GroupNonUniformShuffleRelative,
    spvrefl_capability_GroupNonUniformClustered,
    spvrefl_capability_GroupNonUniformQuad,
    spvrefl_capability_ShaderLayer,
    spvrefl_capability_ShaderViewportIndex,
    spvrefl_capability_SubgroupBallotKHR,
    spvrefl_capability_DrawParameters,
    spvrefl_capability_SubgroupVoteKHR,
    spvrefl_capability_StorageBuffer16BitAccess,
    //spvrefl_capability_StorageUniformBufferBlock16,
    spvrefl_capability_UniformAndStorageBuffer16BitAccess,
    //spvrefl_capability_StorageUniform16,
    spvrefl_capability_StoragePushConstant16,
    spvrefl_capability_StorageInputOutput16,
    spvrefl_capability_DeviceGroup,
    spvrefl_capability_MultiView,
    spvrefl_capability_VariablePointersStorageBuffer,
    spvrefl_capability_VariablePointers,
    spvrefl_capability_AtomicStorageOps,
    spvrefl_capability_SampleMaskPostDepthCoverage,
    spvrefl_capability_StorageBuffer8BitAccess,
    spvrefl_capability_UniformAndStorageBuffer8BitAccess,
    spvrefl_capability_StoragePushConstant8,
    spvrefl_capability_DenormPreserve,
    spvrefl_capability_DenormFlushToZero,
    spvrefl_capability_SignedZeroInfNanPreserve,
    spvrefl_capability_RoundingModeRTE,
    spvrefl_capability_RoundingModeRTZ,
    spvrefl_capability_Float16ImageAMD,
    spvrefl_capability_ImageGatherBiasLodAMD,
    spvrefl_capability_FragmentMaskAMD,
    spvrefl_capability_StencilExportEXT,
    spvrefl_capability_ImageReadWriteLodAMD,
    spvrefl_capability_ShaderClockKHR,
    spvrefl_capability_SampleMaskOverrideCoverageNV,
    spvrefl_capability_GeometryShaderPassthroughNV,
    spvrefl_capability_ShaderViewportIndexLayerEXT,
    //spvrefl_capability_ShaderViewportIndexLayerNV,
    spvrefl_capability_ShaderViewportMaskNV,
    spvrefl_capability_ShaderStereoViewNV,
    spvrefl_capability_PerViewAttributesNV,
    spvrefl_capability_FragmentFullyCoveredEXT,
    spvrefl_capability_MeshShadingNV,
    spvrefl_capability_ImageFootprintNV,
    spvrefl_capability_FragmentBarycentricNV,
    spvrefl_capability_ComputeDerivativeGroupQuadsNV,
    spvrefl_capability_FragmentDensityEXT,
    spvrefl_capability_ShadingRateNV,
    spvrefl_capability_GroupNonUniformPartitionedNV,
    spvrefl_capability_ShaderNonUniform,
    //spvrefl_capability_ShaderNonUniformEXT,
    spvrefl_capability_RuntimeDescriptorArray,
    //spvrefl_capability_RuntimeDescriptorArrayEXT,
    spvrefl_capability_InputAttachmentArrayDynamicIndexing,
    //spvrefl_capability_InputAttachmentArrayDynamicIndexingEXT,
    spvrefl_capability_UniformTexelBufferArrayDynamicIndexing,
    //spvrefl_capability_UniformTexelBufferArrayDynamicIndexingEXT,
    spvrefl_capability_StorageTexelBufferArrayDynamicIndexing,
    //spvrefl_capability_StorageTexelBufferArrayDynamicIndexingEXT,
    spvrefl_capability_UniformBufferArrayNonUniformIndexing,
    //spvrefl_capability_UniformBufferArrayNonUniformIndexingEXT,
    spvrefl_capability_SampledImageArrayNonUniformIndexing,
    //spvrefl_capability_SampledImageArrayNonUniformIndexingEXT,
    spvrefl_capability_StorageBufferArrayNonUniformIndexing,
    //spvrefl_capability_StorageBufferArrayNonUniformIndexingEXT,
    spvrefl_capability_StorageImageArrayNonUniformIndexing,
    //spvrefl_capability_StorageImageArrayNonUniformIndexingEXT,
    spvrefl_capability_InputAttachmentArrayNonUniformIndexing,
    //spvrefl_capability_InputAttachmentArrayNonUniformIndexingEXT,
    spvrefl_capability_UniformTexelBufferArrayNonUniformIndexing,
    //spvrefl_capability_UniformTexelBufferArrayNonUniformIndexingEXT,
    spvrefl_capability_StorageTexelBufferArrayNonUniformIndexing,
    //spvrefl_capability_StorageTexelBufferArrayNonUniformIndexingEXT,
    spvrefl_capability_RayTracingNV,
    spvrefl_capability_VulkanMemoryModel,
    //spvrefl_capability_VulkanMemoryModelKHR,
    spvrefl_capability_VulkanMemoryModelDeviceScope,
    //spvrefl_capability_VulkanMemoryModelDeviceScopeKHR,
    spvrefl_capability_PhysicalStorageBufferAddresses,
    //spvrefl_capability_PhysicalStorageBufferAddressesEXT,
    spvrefl_capability_ComputeDerivativeGroupLinearNV,
    spvrefl_capability_CooperativeMatrixNV,
    spvrefl_capability_FragmentShaderSampleInterlockEXT,
    spvrefl_capability_FragmentShaderShadingRateInterlockEXT,
    spvrefl_capability_ShaderSMBuiltinsNV,
    spvrefl_capability_FragmentShaderPixelInterlockEXT,
    spvrefl_capability_DemoteToHelperInvocationEXT,
    spvrefl_capability_SubgroupShuffleINTEL,
    spvrefl_capability_SubgroupBufferBlockIOINTEL,
    spvrefl_capability_SubgroupImageBlockIOINTEL,
    spvrefl_capability_SubgroupImageMediaBlockIOINTEL,
    spvrefl_capability_IntegerFunctions2INTEL,
    spvrefl_capability_SubgroupAvcMotionEstimationINTEL,
    spvrefl_capability_SubgroupAvcMotionEstimationIntraINTEL,
    spvrefl_capability_SubgroupAvcMotionEstimationChromaINTEL,

    spvrefl_capability__count
} spvrefl_capability_e;

typedef struct {
    int count;
    int needed_count;
    char const * names [SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT];
} spvrefl_struct_members_t;

typedef struct {
    uint32_t id;
    spvrefl_idtype_e type;
    char const * name;  // Will point into scratch memory passed to spvrefl_reflect()
    spvrefl_struct_members_t * struct_members; // NULL for non-structs; otherwise will point into scratch memory passed to spvrefl_reflect()
} spvrefl_id_data_t;

typedef struct {
    // NOTE: As of SPIR-V 1.5r2, there are 141 unique capabilities defined,
    //       so they will fit in 160 bits.
    uint32_t bits [5];
} spvrefl_capability_set_t;

typedef struct {
    int count;
    int needed_count;
    char const * names [SPVREFL_OPT_MAX_USED_EXTENSIONS];   // Will point into scratch memory passed to spvrefl_reflect()
} spvrefl_extension_set_t;

typedef struct {
    int count;
    int needed_count;
    uint32_t ids [SPVREFL_OPT_MAX_USED_EXTENDED_INSTRUCTION_SET_IMPORT];
    char const * names [SPVREFL_OPT_MAX_USED_EXTENDED_INSTRUCTION_SET_IMPORT];  // Will point into scratch memory passed to spvrefl_reflect()
} spvrefl_instruction_set_import_set_t;

typedef struct {
    int count;
    int needed_count;
    char const * names [SPVREFL_OPT_MAX_USED_SOURCE_EXTENSIONS];   // Will point into scratch memory passed to spvrefl_reflect()
} spvrefl_source_extension_set_t;

//typedef struct {
//    int count;
//    int needed_count;
//    spvrefl_struct_t desc [SPVREFL_OPT_MAX_STRUCT_COUNT];
//} spvrefl_struct_set_t;

typedef struct {
    uint32_t magic_number;
    uint8_t version_major, version_minor;
    uint32_t generator;
    uint32_t id_upper_bound;
    uint32_t instruction_count;
    spvrefl_capability_set_t capabilities;
    spvrefl_extension_set_t extensions;
    spvrefl_instruction_set_import_set_t instruction_sets;
    //spvrefl_struct_set_t structs;
    int struct_count;
    int struct_needed_count;

    int ids_count;
    spvrefl_id_data_t * ids;    // Points to an array of length "ids_count", inside scratch memory.

    spvrefl_sourcelang_e source_language;
    uint32_t source_language_version;
    spvrefl_source_extension_set_t source_extensions;
    char const * source_file_name;
    char const * source_text;
} spvrefl_info_t;

typedef struct {
    spvrefl_error_e error_code;
    int error_position_byte;
    int scratch_memory_used_bytes;
} spvrefl_result_t;


spvrefl_result_t
spvrefl_reflect (
    void const * input_spirv,
    int input_size_bytes,
    spvrefl_info_t * out_reflection_info,
    void * scratch_memory,
    int scratch_memory_size_bytes
);


char const *
spvrefl_get_capability_name (spvrefl_capability_e cap);

#if defined(__cplusplus)
}
#endif

#endif  // INTERNAL_SPVREFLECT_HEADER_GUARD__
