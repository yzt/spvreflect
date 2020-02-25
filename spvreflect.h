#if !defined(INTERNAL_SPVREFLECT_HEADER_GUARD__)
#define INTERNAL_SPVREFLECT_HEADER_GUARD__

#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(SPVREFL_OPT_MAX_USED_EXTENSIONS)
    #define  SPVREFL_OPT_MAX_USED_EXTENSIONS                        4
#endif
#if !defined(SPVREFL_OPT_MAX_USED_EXTENDED_INSTRUCTION_SET_IMPORT)
    #define  SPVREFL_OPT_MAX_USED_EXTENDED_INSTRUCTION_SET_IMPORT   4
#endif
#if !defined(SPVREFL_OPT_MAX_USED_SOURCE_EXTENSIONS)
    #define  SPVREFL_OPT_MAX_USED_SOURCE_EXTENSIONS                 4
#endif
#if !defined(SPVREFL_OPT_MAX_ENTRY_POINTS)
    #define  SPVREFL_OPT_MAX_ENTRY_POINTS                           4
#endif
#if !defined(SPVREFL_OPT_MAX_ENTRY_POINT_FUNC_PARAMS)
    #define  SPVREFL_OPT_MAX_ENTRY_POINT_FUNC_PARAMS                16
#endif
#if !defined(SPVREFL_OPT_MAX_STRUCT_COUNT)
    #define  SPVREFL_OPT_MAX_STRUCT_COUNT                           16
#endif
#if !defined(SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT)
    #define  SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT                    16
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
    spvrefl_sourcelang_Unknown      = 0, // NOTE: These values are based on the spec and mustn't change
    spvrefl_sourcelang_ESSL         = 1,
    spvrefl_sourcelang_GLSL         = 2,
    spvrefl_sourcelang_OpenCL_C     = 3,
    spvrefl_sourcelang_OpenCL_CPP   = 4,
    spvrefl_sourcelang_HLSL         = 5,
} spvrefl_sourcelang_e;

typedef enum {
    spvrefl_executionmodel_vertex        = 0,
    spvrefl_executionmodel_tess_control  = 1,
    spvrefl_executionmodel_tess_eval     = 2,
    spvrefl_executionmodel_geometry      = 3,
    spvrefl_executionmodel_fragment      = 4,
    spvrefl_executionmodel_glcompute     = 5,
    spvrefl_executionmodel_kernel        = 6,
    spvrefl_executionmodel_task_nv       = 5267,
    spvrefl_executionmodel_mesh_nv       = 5268,
    spvrefl_executionmodel_ray_gen_nv    = 5313,
    spvrefl_executionmodel_intersect_nv  = 5314,
    spvrefl_executionmodel_anyhit_nv     = 5315,
    spvrefl_executionmodel_closesthit_nv = 5316,
    spvrefl_executionmodel_miss_nv       = 5317,
    spvrefl_executionmodel_callable_nv   = 5318,
} spvrefl_executionmodel_e;

typedef enum {
    spvrefl_addressingmodel_logical                 = 0,
    spvrefl_addressingmodel_physical32              = 1,
    spvrefl_addressingmodel_physical64              = 2,
    spvrefl_addressingmodel_physicalstoragebuffer64 = 5348,
} spvrefl_addressingmodel_e;

typedef enum {
    spvrefl_memorymodel_simple      = 0,
    spvrefl_memorymodel_glsl450     = 1,
    spvrefl_memorymodel_opencl      = 2,
    spvrefl_memorymodel_vulkan      = 3,
} spvrefl_memorymodel_e;

typedef enum {
    spvrefl_execmode_Invocations,
    spvrefl_execmode_SpacingEqual,
    spvrefl_execmode_SpacingFractionalEven,
    spvrefl_execmode_SpacingFractionalOdd,
    spvrefl_execmode_VertexOrderCw,
    spvrefl_execmode_VertexOrderCcw,
    spvrefl_execmode_PixelCenterInteger,
    spvrefl_execmode_OriginUpperLeft,
    spvrefl_execmode_OriginLowerLeft,
    spvrefl_execmode_EarlyFragmentTests,
    spvrefl_execmode_PointMode,
    spvrefl_execmode_Xfb,
    spvrefl_execmode_DepthReplacing,
    spvrefl_execmode_DepthGreater,
    spvrefl_execmode_DepthLess,
    spvrefl_execmode_DepthUnchanged,
    spvrefl_execmode_LocalSize,
    spvrefl_execmode_LocalSizeHint,
    spvrefl_execmode_InputPoints,
    spvrefl_execmode_InputLines,
    spvrefl_execmode_InputLinesAdjacency,
    spvrefl_execmode_Triangles,
    spvrefl_execmode_InputTrianglesAdjacency,
    spvrefl_execmode_Quads,
    spvrefl_execmode_Isolines,
    spvrefl_execmode_OutputVertices,
    spvrefl_execmode_OutputPoints,
    spvrefl_execmode_OutputLineStrip,
    spvrefl_execmode_OutputTriangleStrip,
    spvrefl_execmode_VecTypeHint,
    spvrefl_execmode_ContractionOff,
    spvrefl_execmode_Initializer,
    spvrefl_execmode_Finalizer,
    spvrefl_execmode_SubgroupSize,
    spvrefl_execmode_SubgroupsPerWorkgroup,
    spvrefl_execmode_SubgroupsPerWorkgroupId,
    spvrefl_execmode_LocalSizeId,
    spvrefl_execmode_LocalSizeHintId,
    spvrefl_execmode_PostDepthCoverage,
    spvrefl_execmode_DenormPreserve,
    spvrefl_execmode_DenormFlushToZero,
    spvrefl_execmode_SignedZeroInfNanPreserve,
    spvrefl_execmode_RoundingModeRTE,
    spvrefl_execmode_RoundingModeRTZ,
    spvrefl_execmode_StencilRefReplacingEXT,
    spvrefl_execmode_OutputLinesNV,
    spvrefl_execmode_OutputPrimitivesNV,
    spvrefl_execmode_DerivativeGroupQuadsNV,
    spvrefl_execmode_DerivativeGroupLinearNV,
    spvrefl_execmode_OutputTrianglesNV,
    spvrefl_execmode_PixelInterlockOrderedEXT,
    spvrefl_execmode_PixelInterlockUnorderedEXT,
    spvrefl_execmode_SampleInterlockOrderedEXT,
    spvrefl_execmode_SampleInterlockUnorderedEXT,
    spvrefl_execmode_ShadingRateInterlockOrderedEXT,
    spvrefl_execmode_ShadingRateInterlockUnorderedEXT,
} spvrefl_execmode_e;

typedef enum {
    spvrefl_storageclass_UniformConstant          = 0,
    spvrefl_storageclass_Input                    = 1,
    spvrefl_storageclass_Uniform                  = 2,
    spvrefl_storageclass_Output                   = 3,
    spvrefl_storageclass_Workgroup                = 4,
    spvrefl_storageclass_CrossWorkgroup           = 5,
    spvrefl_storageclass_Private                  = 6,
    spvrefl_storageclass_Function                 = 7,
    spvrefl_storageclass_Generic                  = 8,
    spvrefl_storageclass_PushConstant             = 9,
    spvrefl_storageclass_AtomicCounter            = 10,
    spvrefl_storageclass_Image                    = 11,
    spvrefl_storageclass_StorageBuffer            = 12,
    spvrefl_storageclass_CallableDataNV           = 5328,
    spvrefl_storageclass_IncomingCallableDataNV   = 5329,
    spvrefl_storageclass_RayPayloadNV             = 5338,
    spvrefl_storageclass_HitAttributeNV           = 5339,
    spvrefl_storageclass_IncomingRayPayloadNV     = 5342,
    spvrefl_storageclass_ShaderRecordBufferNV     = 5343,
    spvrefl_storageclass_PhysicalStorageBuffer    = 5349,
    spvrefl_storageclass_PhysicalStorageBufferEXT = 5349,
} spvrefl_storageclass_e;

typedef enum {
    spvrefl_dim_1D          = 0,
    spvrefl_dim_2D          = 1,
    spvrefl_dim_3D          = 2,
    spvrefl_dim_Cube        = 3,
    spvrefl_dim_Rect        = 4,
    spvrefl_dim_Buffer      = 5,
    spvrefl_dim_SubpassData = 6,
} spvrefl_dim_e;

typedef enum {
    spvrefl_sampleraddressingmode_None           = 0,
    spvrefl_sampleraddressingmode_ClampToEdge    = 1,
    spvrefl_sampleraddressingmode_Clamp          = 2,
    spvrefl_sampleraddressingmode_Repeat         = 3,
    spvrefl_sampleraddressingmode_RepeatMirrored = 4,
} spvrefl_sampleraddressingmode_e;

typedef enum {
    spvrefl_samplerfiltermode_Nearest = 0,
    spvrefl_samplerfiltermode_Linear  = 1,
} spvrefl_samplerfiltermode_e;

typedef enum {
    spvrefl_imageformat_Unknown      = 0,
    spvrefl_imageformat_Rgba32f      = 1,
    spvrefl_imageformat_Rgba16f      = 2,
    spvrefl_imageformat_R32f         = 3,
    spvrefl_imageformat_Rgba8        = 4,
    spvrefl_imageformat_Rgba8Snorm   = 5,
    spvrefl_imageformat_Rg32f        = 6,
    spvrefl_imageformat_Rg16f        = 7,
    spvrefl_imageformat_R11fG11fB10f = 8,
    spvrefl_imageformat_R16f         = 9,
    spvrefl_imageformat_Rgba16       = 10,
    spvrefl_imageformat_Rgb10A2      = 11,
    spvrefl_imageformat_Rg16         = 12,
    spvrefl_imageformat_Rg8          = 13,
    spvrefl_imageformat_R16          = 14,
    spvrefl_imageformat_R8           = 15,
    spvrefl_imageformat_Rgba16Snorm  = 16,
    spvrefl_imageformat_Rg16Snorm    = 17,
    spvrefl_imageformat_Rg8Snorm     = 18,
    spvrefl_imageformat_R16Snorm     = 19,
    spvrefl_imageformat_R8Snorm      = 20,
    spvrefl_imageformat_Rgba32i      = 21,
    spvrefl_imageformat_Rgba16i      = 22,
    spvrefl_imageformat_Rgba8i       = 23,
    spvrefl_imageformat_R32i         = 24,
    spvrefl_imageformat_Rg32i        = 25,
    spvrefl_imageformat_Rg16i        = 26,
    spvrefl_imageformat_Rg8i         = 27,
    spvrefl_imageformat_R16i         = 28,
    spvrefl_imageformat_R8i          = 29,
    spvrefl_imageformat_Rgba32ui     = 30,
    spvrefl_imageformat_Rgba16ui     = 31,
    spvrefl_imageformat_Rgba8ui      = 32,
    spvrefl_imageformat_R32ui        = 33,
    spvrefl_imageformat_Rgb10a2ui    = 34,
    spvrefl_imageformat_Rg32ui       = 35,
    spvrefl_imageformat_Rg16ui       = 36,
    spvrefl_imageformat_Rg8ui        = 37,
    spvrefl_imageformat_R16ui        = 38,
    spvrefl_imageformat_R8ui         = 39,
} spvrefl_imageformat_e;

typedef enum {
    spvrefl_imagechannelorder_R            = 0,
    spvrefl_imagechannelorder_A            = 1,
    spvrefl_imagechannelorder_RG           = 2,
    spvrefl_imagechannelorder_RA           = 3,
    spvrefl_imagechannelorder_RGB          = 4,
    spvrefl_imagechannelorder_RGBA         = 5,
    spvrefl_imagechannelorder_BGRA         = 6,
    spvrefl_imagechannelorder_ARGB         = 7,
    spvrefl_imagechannelorder_Intensity    = 8,
    spvrefl_imagechannelorder_Luminance    = 9,
    spvrefl_imagechannelorder_Rx           = 10,
    spvrefl_imagechannelorder_RGx          = 11,
    spvrefl_imagechannelorder_RGBx         = 12,
    spvrefl_imagechannelorder_Depth        = 13,
    spvrefl_imagechannelorder_DepthStencil = 14,
    spvrefl_imagechannelorder_sRGB         = 15,
    spvrefl_imagechannelorder_sRGBx        = 16,
    spvrefl_imagechannelorder_sRGBA        = 17,
    spvrefl_imagechannelorder_sBGRA        = 18,
    spvrefl_imagechannelorder_ABGR         = 19,
} spvrefl_imagechannelorder_e;

typedef enum {
    spvrefl_imagechanneldatatype_SnormInt8        = 0,
    spvrefl_imagechanneldatatype_SnormInt16       = 1,
    spvrefl_imagechanneldatatype_UnormInt8        = 2,
    spvrefl_imagechanneldatatype_UnormInt16       = 3,
    spvrefl_imagechanneldatatype_UnormShort565    = 4,
    spvrefl_imagechanneldatatype_UnormShort555    = 5,
    spvrefl_imagechanneldatatype_UnormInt101010   = 6,
    spvrefl_imagechanneldatatype_SignedInt8       = 7,
    spvrefl_imagechanneldatatype_SignedInt16      = 8,
    spvrefl_imagechanneldatatype_SignedInt32      = 9,
    spvrefl_imagechanneldatatype_UnsignedInt8     = 10,
    spvrefl_imagechanneldatatype_UnsignedInt16    = 11,
    spvrefl_imagechanneldatatype_UnsignedInt32    = 12,
    spvrefl_imagechanneldatatype_HalfFloat        = 13,
    spvrefl_imagechanneldatatype_Float            = 14,
    spvrefl_imagechanneldatatype_UnormInt24       = 15,
    spvrefl_imagechanneldatatype_UnormInt101010_2 = 16,
} spvrefl_imagechanneldatatype_e;

typedef enum {
    spvrefl_imageoperands_None                  = 0x0,
    spvrefl_imageoperands_Bias                  = 0x1,
    spvrefl_imageoperands_Lod                   = 0x2,
    spvrefl_imageoperands_Grad                  = 0x4,
    spvrefl_imageoperands_ConstOffset           = 0x8,
    spvrefl_imageoperands_Offset                = 0x10,
    spvrefl_imageoperands_ConstOffsets          = 0x20,
    spvrefl_imageoperands_Sample                = 0x40,
    spvrefl_imageoperands_MinLod                = 0x80,
    spvrefl_imageoperands_MakeTexelAvailable    = 0x100,
  //spvrefl_imageoperands_MakeTexelAvailableKHR = 0x100,
    spvrefl_imageoperands_MakeTexelVisible      = 0x200,
  //spvrefl_imageoperands_MakeTexelVisibleKHR   = 0x200,
    spvrefl_imageoperands_NonPrivateTexel       = 0x400,
  //spvrefl_imageoperands_NonPrivateTexelKHR    = 0x400,
    spvrefl_imageoperands_VolatileTexel         = 0x800,
  //spvrefl_imageoperands_VolatileTexelKHR      = 0x800,
    spvrefl_imageoperands_SignExtend            = 0x1000,
    spvrefl_imageoperands_ZeroExtend            = 0x2000,
} spvrefl_imageoperands_e;

typedef enum {
    spvrefl_fpfastmathmode_None       = 0x0,
    spvrefl_fpfastmathmode_NotNaN     = 0x1,
    spvrefl_fpfastmathmode_NotInf     = 0x2,
    spvrefl_fpfastmathmode_NSZ        = 0x4,
    spvrefl_fpfastmathmode_AllowRecip = 0x8,
    spvrefl_fpfastmathmode_Fast       = 0x10,
} spvrefl_fpfastmathmode_e;

typedef enum {
    spvrefl_fproundingmode_RTE = 0,
    spvrefl_fproundingmode_RTZ = 1,
    spvrefl_fproundingmode_RTP = 2,
    spvrefl_fproundingmode_RTN = 3,
} spvrefl_fproundingmode_e;

typedef enum {
    spvrefl_linkagetype_Export = 0,
    spvrefl_linkagetype_Import = 1,
} spvrefl_linkagetype_e;

typedef enum {
    spvrefl_accessqualifier_ReadOnly  = 0,
    spvrefl_accessqualifier_WriteOnly = 1,
    spvrefl_accessqualifier_ReadWrite = 2,
} spvrefl_accessqualifier_e;

typedef enum {
    spvrefl_functionparamattrib_Zext        = 0,
    spvrefl_functionparamattrib_Sext        = 1,
    spvrefl_functionparamattrib_ByVal       = 2,
    spvrefl_functionparamattrib_Sret        = 3,
    spvrefl_functionparamattrib_NoAlias     = 4,
    spvrefl_functionparamattrib_NoCapture   = 5,
    spvrefl_functionparamattrib_NoWrite     = 6,
    spvrefl_functionparamattrib_NoReadWrite = 7,
} spvrefl_functionparamattrib_e;

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

typedef struct {
    spvrefl_executionmodel_e execution_model;
    uint32_t id;
    char const * name;
    int param_count;
    int needed_param_count;
    uint32_t params [SPVREFL_OPT_MAX_ENTRY_POINT_FUNC_PARAMS];
} spvrefl_entry_point_t;

typedef struct {
    int count;
    int needed_count;
    spvrefl_entry_point_t functions [SPVREFL_OPT_MAX_ENTRY_POINTS];
} spvrefl_entry_point_set_t;

typedef struct {
    uint32_t magic_number;
    uint8_t version_major, version_minor;
    uint32_t generator;
    uint32_t id_upper_bound;
    uint32_t instruction_count;
    
    spvrefl_capability_set_t capabilities;
    spvrefl_extension_set_t extensions;
    spvrefl_instruction_set_import_set_t instruction_sets;
    spvrefl_addressingmodel_e addressing_model;
    spvrefl_memorymodel_e memory_model;
    spvrefl_entry_point_set_t entry_points;

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
