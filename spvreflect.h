#if !defined(INTERNAL_SPVREFLECT_HEADER_GUARD__)
#define INTERNAL_SPVREFLECT_HEADER_GUARD__

#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma region "Compile-Time Options"
//#define  SPVREFL_OPT_DONT_SUPPORT_TYPE_STRINGIFICATION              // Would require snprintf() from stdio.h
#if !defined(SPVREFL_OPT_MAX_EXTENSIONS)
    #define  SPVREFL_OPT_MAX_EXTENSIONS                             4
#endif
#if !defined(SPVREFL_OPT_MAX_EXTENDED_INSTRUCTION_SET_IMPORTS)
    #define  SPVREFL_OPT_MAX_EXTENDED_INSTRUCTION_SET_IMPORTS       4
#endif
#if !defined(SPVREFL_OPT_MAX_SOURCE_EXTENSIONS)
    #define  SPVREFL_OPT_MAX_SOURCE_EXTENSIONS                      4
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
#if !defined(SPVREFL_OPT_MAX_DECORATIONS_PER_ID_OR_MEMBER)
    #define  SPVREFL_OPT_MAX_DECORATIONS_PER_ID_OR_MEMBER           8
#endif

#if !defined(SPVREFL_OPT_MAX_BLOCKS_IN_SPIRV)
    #define  SPVREFL_OPT_MAX_BLOCKS_IN_SPIRV                        32
#endif
#if !defined(SPVREFL_OPT_MAX_SHADER_NAME_LEN)
    #define SPVREFL_MAX_EXTRACTED_STRING_LEN                             32
#endif
#pragma endregion

#pragma region "Enumerations"
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
  //spvrefl_storageclass_PhysicalStorageBufferEXT = 5349,
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
    spvrefl_decoration_RelaxedPrecision,
    spvrefl_decoration_SpecId,
    spvrefl_decoration_Block,
    spvrefl_decoration_BufferBlock,
    spvrefl_decoration_RowMajor,
    spvrefl_decoration_ColMajor,
    spvrefl_decoration_ArrayStride,
    spvrefl_decoration_MatrixStride,
    spvrefl_decoration_GLSLShared,
    spvrefl_decoration_GLSLPacked,
    spvrefl_decoration_CPacked,
    spvrefl_decoration_BuiltIn,
    spvrefl_decoration_NoPerspective,
    spvrefl_decoration_Flat,
    spvrefl_decoration_Patch,
    spvrefl_decoration_Centroid,
    spvrefl_decoration_Sample,
    spvrefl_decoration_Invariant,
    spvrefl_decoration_Restrict,
    spvrefl_decoration_Aliased,
    spvrefl_decoration_Volatile,
    spvrefl_decoration_Constant,
    spvrefl_decoration_Coherent,
    spvrefl_decoration_NonWritable,
    spvrefl_decoration_NonReadable,
    spvrefl_decoration_Uniform,
    spvrefl_decoration_UniformId,
    spvrefl_decoration_SaturatedConversion,
    spvrefl_decoration_Stream,
    spvrefl_decoration_Location,
    spvrefl_decoration_Component,
    spvrefl_decoration_Index,
    spvrefl_decoration_Binding,
    spvrefl_decoration_DescriptorSet,
    spvrefl_decoration_Offset,
    spvrefl_decoration_XfbBuffer,
    spvrefl_decoration_XfbStride,
    spvrefl_decoration_FuncParamAttr,
    spvrefl_decoration_FPRoundingMode,
    spvrefl_decoration_FPFastMathMode,
    spvrefl_decoration_LinkageAttributes,
    spvrefl_decoration_NoContraction,
    spvrefl_decoration_InputAttachmentIndex,
    spvrefl_decoration_Alignment,
    spvrefl_decoration_MaxByteOffset,
    spvrefl_decoration_AlignmentId,
    spvrefl_decoration_MaxByteOffsetId,
    spvrefl_decoration_NoSignedWrap,
    spvrefl_decoration_NoUnsignedWrap,
    spvrefl_decoration_ExplicitInterpAMD,
    spvrefl_decoration_OverrideCoverageNV,
    spvrefl_decoration_PassthroughNV,
    spvrefl_decoration_ViewportRelativeNV,
    spvrefl_decoration_SecondaryViewportRelativeNV,
    spvrefl_decoration_PerPrimitiveNV,
    spvrefl_decoration_PerViewNV,
    spvrefl_decoration_PerTaskNV,
    spvrefl_decoration_PerVertexNV,
    spvrefl_decoration_NonUniform,
    spvrefl_decoration_NonUniformEXT,
    spvrefl_decoration_RestrictPointer,
    spvrefl_decoration_RestrictPointerEXT,
    spvrefl_decoration_AliasedPointer,
    spvrefl_decoration_AliasedPointerEXT,
    spvrefl_decoration_CounterBuffer,
    spvrefl_decoration_HlslCounterBufferGOOGLE,
    spvrefl_decoration_UserSemantic,
    spvrefl_decoration_HlslSemanticGOOGLE,
    spvrefl_decoration_UserTypeGOOGLE,

    spvrefl_decoration__count
} spvrefl_decoration_e;

typedef enum {
    spvrefl_builtin_Position                    = 0,
    spvrefl_builtin_PointSize                   = 1,
    spvrefl_builtin_ClipDistance                = 3,
    spvrefl_builtin_CullDistance                = 4,
    spvrefl_builtin_VertexId                    = 5,
    spvrefl_builtin_InstanceId                  = 6,
    spvrefl_builtin_PrimitiveId                 = 7,
    spvrefl_builtin_InvocationId                = 8,
    spvrefl_builtin_Layer                       = 9,
    spvrefl_builtin_ViewportIndex               = 10,
    spvrefl_builtin_TessLevelOuter              = 11,
    spvrefl_builtin_TessLevelInner              = 12,
    spvrefl_builtin_TessCoord                   = 13,
    spvrefl_builtin_PatchVertices               = 14,
    spvrefl_builtin_FragCoord                   = 15,
    spvrefl_builtin_PointCoord                  = 16,
    spvrefl_builtin_FrontFacing                 = 17,
    spvrefl_builtin_SampleId                    = 18,
    spvrefl_builtin_SamplePosition              = 19,
    spvrefl_builtin_SampleMask                  = 20,
    spvrefl_builtin_FragDepth                   = 22,
    spvrefl_builtin_HelperInvocation            = 23,
    spvrefl_builtin_NumWorkgroups               = 24,
    spvrefl_builtin_WorkgroupSize               = 25,
    spvrefl_builtin_WorkgroupId                 = 26,
    spvrefl_builtin_LocalInvocationId           = 27,
    spvrefl_builtin_GlobalInvocationId          = 28,
    spvrefl_builtin_LocalInvocationIndex        = 29,
    spvrefl_builtin_WorkDim                     = 30,
    spvrefl_builtin_GlobalSize                  = 31,
    spvrefl_builtin_EnqueuedWorkgroupSize       = 32,
    spvrefl_builtin_GlobalOffset                = 33,
    spvrefl_builtin_GlobalLinearId              = 34,
    spvrefl_builtin_SubgroupSize                = 36,
    spvrefl_builtin_SubgroupMaxSize             = 37,
    spvrefl_builtin_NumSubgroups                = 38,
    spvrefl_builtin_NumEnqueuedSubgroups        = 39,
    spvrefl_builtin_SubgroupId                  = 40,
    spvrefl_builtin_SubgroupLocalInvocationId   = 41,
    spvrefl_builtin_VertexIndex                 = 42,
    spvrefl_builtin_InstanceIndex               = 43,
    spvrefl_builtin_SubgroupEqMask              = 4416,
    spvrefl_builtin_SubgroupGeMask              = 4417,
    spvrefl_builtin_SubgroupGtMask              = 4418,
    spvrefl_builtin_SubgroupLeMask              = 4419,
    spvrefl_builtin_SubgroupLtMask              = 4420,
  //spvrefl_builtin_SubgroupEqMaskKHR           = 4416,
  //spvrefl_builtin_SubgroupGeMaskKHR           = 4417,
  //spvrefl_builtin_SubgroupGtMaskKHR           = 4418,
  //spvrefl_builtin_SubgroupLeMaskKHR           = 4419,
  //spvrefl_builtin_SubgroupLtMaskKHR           = 4420,
    spvrefl_builtin_BaseVertex                  = 4424,
    spvrefl_builtin_BaseInstance                = 4425,
    spvrefl_builtin_DrawIndex                   = 4426,
    spvrefl_builtin_DeviceIndex                 = 4438,
    spvrefl_builtin_ViewIndex                   = 4440,
    spvrefl_builtin_BaryCoordNoPerspAMD         = 4992,
    spvrefl_builtin_BaryCoordNoPerspCentroidAMD = 4993,
    spvrefl_builtin_BaryCoordNoPerspSampleAMD   = 4994,
    spvrefl_builtin_BaryCoordSmoothAMD          = 4995,
    spvrefl_builtin_BaryCoordSmoothCentroidAMD  = 4996,
    spvrefl_builtin_BaryCoordSmoothSampleAMD    = 4997,
    spvrefl_builtin_BaryCoordPullModelAMD       = 4998,
    spvrefl_builtin_FragStencilRefEXT           = 5014,
    spvrefl_builtin_ViewportMaskNV              = 5253,
    spvrefl_builtin_SecondaryPositionNV         = 5257,
    spvrefl_builtin_SecondaryViewportMaskNV     = 5258,
    spvrefl_builtin_PositionPerViewNV           = 5261,
    spvrefl_builtin_ViewportMaskPerViewNV       = 5262,
    spvrefl_builtin_FullyCoveredEXT             = 5264,
    spvrefl_builtin_TaskCountNV                 = 5274,
    spvrefl_builtin_PrimitiveCountNV            = 5275,
    spvrefl_builtin_PrimitiveIndicesNV          = 5276,
    spvrefl_builtin_ClipDistancePerViewNV       = 5277,
    spvrefl_builtin_CullDistancePerViewNV       = 5278,
    spvrefl_builtin_LayerPerViewNV              = 5279,
    spvrefl_builtin_MeshViewCountNV             = 5280,
    spvrefl_builtin_MeshViewIndicesNV           = 5281,
    spvrefl_builtin_BaryCoordNV                 = 5286,
    spvrefl_builtin_BaryCoordNoPerspNV          = 5287,
    spvrefl_builtin_FragSizeEXT                 = 5292,
  //spvrefl_builtin_FragmentSizeNV              = 5292,
    spvrefl_builtin_FragInvocationCountEXT      = 5293,
  //spvrefl_builtin_InvocationsPerPixelNV       = 5293,
    spvrefl_builtin_LaunchIdNV                  = 5319,
    spvrefl_builtin_LaunchSizeNV                = 5320,
    spvrefl_builtin_WorldRayOriginNV            = 5321,
    spvrefl_builtin_WorldRayDirectionNV         = 5322,
    spvrefl_builtin_ObjectRayOriginNV           = 5323,
    spvrefl_builtin_ObjectRayDirectionNV        = 5324,
    spvrefl_builtin_RayTminNV                   = 5325,
    spvrefl_builtin_RayTmaxNV                   = 5326,
    spvrefl_builtin_InstanceCustomIndexNV       = 5327,
    spvrefl_builtin_ObjectToWorldNV             = 5330,
    spvrefl_builtin_WorldToObjectNV             = 5331,
    spvrefl_builtin_HitTNV                      = 5332,
    spvrefl_builtin_HitKindNV                   = 5333,
    spvrefl_builtin_IncomingRayFlagsNV          = 5351,
    spvrefl_builtin_WarpsPerSMNV                = 5374,
    spvrefl_builtin_SMCountNV                   = 5375,
    spvrefl_builtin_WarpIDNV                    = 5376,
    spvrefl_builtin_SMIDNV                      = 5377,
} spvrefl_builtin_e;

typedef enum {
    spvrefl_selectioncontrol_None           = 0x0,
    spvrefl_selectioncontrol_Flatten        = 0x1,
    spvrefl_selectioncontrol_DontFlatten    = 0x2,
} spvrefl_selectioncontrol_e;

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

//typedef enum {
//    spvrefl_idtype_unknown = 0,
//    spvrefl_idtype_source_file_name,
//    spvrefl_idtype_struct,
//} spvrefl_idtype_e;

typedef enum {
    spvrefl_basictype_not_a_type = 0,
    spvrefl_basictype_struct,
    spvrefl_basictype_void,
    spvrefl_basictype_bool,
    spvrefl_basictype_uint,
    spvrefl_basictype_sint,
    spvrefl_basictype_float,
    //spvrefl_basictype_image,
    spvrefl_basictype_sampler,
    //spvrefl_basictype_sampled_image,
    spvrefl_basictype_pointer,
} spvrefl_basictype_e;

typedef enum {
    spvrefl_imagetype_not_an_image  = 0,
    spvrefl_imagetype_image         = 1,
    spvrefl_imagetype_sampled_image = 2,
} spvrefl_imagetype_e;

typedef enum {
    spvrefl_imageisdepth_no         = 0,
    spvrefl_imageisdepth_yes        = 1,
    spvrefl_imageisdepth_unknown    = 2,
} spvrefl_imageisdepth_e;

typedef enum {
    spvrefl_imageissampled_runtime  = 0,
    spvrefl_imageissampled_yes      = 1,
    spvrefl_imageissampled_no       = 2,
} spvrefl_imageissampled_e;

typedef enum {
    spvrefl_typecategory_unknown    = 0,
    spvrefl_typecategory_basic      = 1,
    spvrefl_typecategory_image      = 2,
    spvrefl_typecategory_pointer    = 3,
    spvrefl_typecategory_variable   = 4,
    spvrefl_typecategory_function   = 5,
    spvrefl_typecategory_constant   = 6,
} spvrefl_typecategory_e;
#pragma endregion

#pragma region "Unions"
typedef union {
    uint32_t raw_value_;

    uint32_t spec_const_id;
    uint32_t array_stride;
    uint32_t matrix_stride;
    spvrefl_builtin_e builtin;
    uint32_t exec_scope_id;
    uint32_t stream_number;
    uint32_t location;
    uint32_t component;
    uint32_t index;
    uint32_t binding_point;
    uint32_t descriptor_set;
    uint32_t byte_offset;
    uint32_t xfb_buffer_number;
    uint32_t xfb_stride;
    spvrefl_functionparamattrib_e func_param_attrib;
    spvrefl_fproundingmode_e fp_rounding_mode;
    spvrefl_fpfastmathmode_e fp_fast_math_mode;
    spvrefl_linkagetype_e linkage_type;
    uint32_t attachment_index;
    uint32_t alignment;
    uint32_t max_byte_offset;
    uint32_t alignment_id;
    uint32_t max_byte_offset_id;
    uint32_t offset;
    uint32_t counter_buffer_id;
    uint32_t semantic;
    uint32_t user_type;
} spvrefl_decoration_param1_u;

typedef union {
    char const * linkage_name;
} spvrefl_decoration_param2_u;
#pragma endregion

#pragma region "Structs"

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4214)     // nonstandard extension used: bit field types other than int
#else
// TODO: Add for other compilers
#endif
typedef struct {
    spvrefl_basictype_e basic_type;
    spvrefl_storageclass_e storage_class;
    uint32_t array_elem_count;      // 0 means not an array, or runtime-sized array; check "is_array"
    uint8_t component_bit_size;

    uint8_t columns;                        // Scalars have both columns and rows set to 1.
    uint8_t rows;                           // Vectors have columns set to 1, and rows set to the number of their components.
                                            // Matrices have both columns and rows set.
    bool is_array                   : 1;
    bool has_storage_class          : 1;    // This is for all types; not just images.
    bool image_is_array             : 1;    // This and below are for images and sampled-images only. For an image, the above contain information for the sampled type
    bool image_is_multisampled      : 1;
    bool has_image_access_qualifier : 1;
    spvrefl_typecategory_e category                     : 4;    // This one is not specific to images!
    spvrefl_imagetype_e image_type                      : 3;
    spvrefl_dim_e image_dimensions                      : 4;
    spvrefl_imageisdepth_e image_is_depth               : 3;
    spvrefl_imageissampled_e image_is_sampled           : 3;
    spvrefl_imageformat_e image_format                  : 7;
    spvrefl_accessqualifier_e image_access_qualifier    : 3;
} spvrefl_type_t;
static_assert(sizeof(spvrefl_type_t) == 20, "");
#if defined(_MSC_VER)
#pragma warning (pop)
#else
// TODO: Add for other compilers
#endif

typedef struct {
    spvrefl_decoration_e decoration;
    spvrefl_decoration_param1_u param1;
    //spvrefl_decoration_param2_u param2;
} spvrefl_decoration_t;

typedef struct {
    int count;
    int needed_count;
    spvrefl_decoration_e decorations [SPVREFL_OPT_MAX_DECORATIONS_PER_ID_OR_MEMBER];
    spvrefl_decoration_param1_u param_ones [SPVREFL_OPT_MAX_DECORATIONS_PER_ID_OR_MEMBER];
    //spvrefl_decoration_param2_u param_twos [SPVREFL_OPT_MAX_DECORATIONS_PER_ID_OR_MEMBER];
} spvrefl_decoration_set_t;

typedef struct {
    spvrefl_type_t type;
    char const * name;  // Will point into scratch memory passed to spvrefl_reflect()
    spvrefl_decoration_set_t decorations;
} spvrefl_struct_member_t;

typedef struct {
    int count;
    int needed_count;
    spvrefl_struct_member_t members [SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT];
} spvrefl_struct_members_t;

typedef struct {
    uint32_t id;
    ///spvrefl_idtype_e type;
    spvrefl_type_t type;
    char const * name;  // Will point into scratch memory passed to spvrefl_reflect()
    spvrefl_struct_members_t * struct_members; // NULL for non-structs; otherwise will point into scratch memory passed to spvrefl_reflect()
    spvrefl_decoration_set_t decorations;
    union {
        bool boolean;
        uint32_t integer;
        float real;
        struct {
            uint8_t addressing_mode;        // Actually a "spvrefl_sampleraddressingmode_e"
            uint8_t filter_mode;            // Actually a "spvrefl_samplerfiltermode_e"
            bool is_normalized;
        } sampler;
    } constant_value;
} spvrefl_id_data_t;
//static_assert(sizeof(spvrefl_id_data_t::constant_value) == 4, "");

typedef struct {
    // NOTE: As of SPIR-V 1.5r2, there are 141 unique capabilities defined,
    //       so they will fit in 160 bits.
    uint32_t bits [5];
} spvrefl_capability_set_t;

typedef struct {
    int count;
    int needed_count;
    char const * names [SPVREFL_OPT_MAX_EXTENSIONS];   // Will point into scratch memory passed to spvrefl_reflect()
} spvrefl_extension_set_t;

typedef struct {
    int count;
    int needed_count;
    uint32_t ids [SPVREFL_OPT_MAX_EXTENDED_INSTRUCTION_SET_IMPORTS];
    char const * names [SPVREFL_OPT_MAX_EXTENDED_INSTRUCTION_SET_IMPORTS];  // Will point into scratch memory passed to spvrefl_reflect()
} spvrefl_instruction_set_import_set_t;

typedef struct {
    int count;
    int needed_count;
    char const * names [SPVREFL_OPT_MAX_SOURCE_EXTENSIONS];   // Will point into scratch memory passed to spvrefl_reflect()
} spvrefl_source_extension_set_t;

typedef struct {
    spvrefl_execmode_e mode;
    int param_count;
    uint32_t params [3];
} spvrefl_execmode_data_t;

typedef struct {
    spvrefl_executionmodel_e execution_model;
    uint32_t id;
    char const * name;
    int param_count;
    int needed_param_count;
    uint32_t parameter_ids [SPVREFL_OPT_MAX_ENTRY_POINT_FUNC_PARAMS];
    spvrefl_execmode_data_t execmode;
} spvrefl_entry_point_t;

typedef struct {
    int count;
    int needed_count;
    spvrefl_entry_point_t functions [SPVREFL_OPT_MAX_ENTRY_POINTS];
} spvrefl_entry_point_set_t;

///typedef struct {
///    int count;
///    int needed_count;
///    spvrefl_decoration_t decorations [SPVREFL_OPT_MAX_TOTAL_DECORATIONS];
///} spvrefl_decoration_set_t;

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
    ///spvrefl_decoration_set_t decorations;

    ///spvrefl_struct_set_t structs;
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


typedef struct {
    bool is_output;             // false: input, true: output
    bool is_array;
    spvrefl_basictype_e basic;
    uint8_t component_bit_size;
    uint8_t columns;
    uint8_t rows;
    uint32_t elem_count;
} spvrefl_extracted_type_t;
typedef struct {
    char const * name;
} spvrefl_extracted_param_t;

typedef struct {
    char name [SPVREFL_MAX_EXTRACTED_STRING_LEN + 1];
    spvrefl_executionmodel_e stage;
    int param_count;
} spvrefl_extracted_entry_point_t;

typedef enum {
    spvrefl_extracted_blockcategory_INVALID                 = 0,
    spvrefl_extracted_blockcategory_sampler               ,
    spvrefl_extracted_blockcategory_combined_image_sampler,
    spvrefl_extracted_blockcategory_sampled_image         ,
    spvrefl_extracted_blockcategory_storage_image         ,
    spvrefl_extracted_blockcategory_uniform_texel_buffer  ,
    spvrefl_extracted_blockcategory_storage_texel_buffer  ,
    spvrefl_extracted_blockcategory_uniform_buffer        ,
    spvrefl_extracted_blockcategory_storage_buffer        ,
    spvrefl_extracted_blockcategory_uniform_buffer_dynamic,
    spvrefl_extracted_blockcategory_storage_buffer_dynamic,
    spvrefl_extracted_blockcategory_input_attachment      ,

    spvrefl_extracted_blockcategory_push_constants        ,
} spvrefl_extracted_blockcategory_e;
typedef struct {
    char name [SPVREFL_MAX_EXTRACTED_STRING_LEN + 1];
    char type_name [SPVREFL_MAX_EXTRACTED_STRING_LEN + 1];
    spvrefl_extracted_blockcategory_e category;
    int descriptor_no;
    int binding_no;
    int size;
    int count;
    bool is_variable_length;            // If true, means that "size" is actually the mininum size.
} spvrefl_extracted_block_t;
typedef struct {
    struct {
        int entry_points;
        int entry_points_needed;

        int total_blocks;
        int total_blocks_needed;

        //int uniform_buffers;
        //int samplers;
        //int images;
        //int combined_image_samplers;
        //int storage_images;
        //int storage_buffers;
        //int push_constants;             // 0 or 1
    } counts;
    
    spvrefl_extracted_entry_point_t entry_points [SPVREFL_OPT_MAX_ENTRY_POINTS];
    spvrefl_extracted_block_t blocks [SPVREFL_OPT_MAX_BLOCKS_IN_SPIRV];
    int max_string_length;
} spvrefl_extracted_shader_info_t;
#pragma endregion

#pragma region "API"
spvrefl_result_t
spvrefl_reflect (
    void const * input_spirv,
    int input_size_bytes,
    spvrefl_info_t * out_reflection_info,
    void * scratch_memory,
    int scratch_memory_size_bytes
);

bool
spvrefl_extract_shader_info (
    spvrefl_info_t const * reflection_info,
    spvrefl_extracted_shader_info_t * out_shader_info
);

char const *
spvrefl_get_capability_name (spvrefl_capability_e cap);

char const *
spvrefl_get_decoration_name (spvrefl_decoration_e dec);

char const *
spvrefl_get_execmode_name (spvrefl_execmode_e em);

char const *
spvrefl_get_executionmodel_name (spvrefl_executionmodel_e emodel);

char const *
spvrefl_get_basictype_name (spvrefl_basictype_e bt);

char const *
spvrefl_get_imageformat_name (spvrefl_imageformat_e ifmt);

char const *
spvrefl_get_imagedimension_name (spvrefl_dim_e idim);

char const *
spvrefl_get_storageclass_name (spvrefl_storageclass_e sc);

char const *
spvrefl_get_extracted_blockcategory_name (spvrefl_extracted_blockcategory_e ebc);

#if !defined(SPVREFL_OPT_DONT_SUPPORT_TYPE_STRINGIFICATION)
char const *
spvrefl_generate_type_string (spvrefl_type_t const * type, spvrefl_struct_members_t const * members, char * buffer, size_t buffer_size);  // buffer needs to be ~60 chars
#endif

#pragma endregion

#if defined(__cplusplus)
}
#endif

#endif  // INTERNAL_SPVREFLECT_HEADER_GUARD__
