#define SPVREFL_IMPLEMENTATION
#if defined(SPVREFL_IMPLEMENTATION)
#include "spvreflect.h"

#include <stdio.h>
#define DEBUG_PRINT(...)        printf("[DEBUG] " __VA_ARGS__)
#define ERROR_PRINT(...)        printf("[ERROR] " __VA_ARGS__)
#define DEPRECATED(...)         printf("[DEPRECATED] " __VA_ARGS__)

#include <assert.h>
#define SPVREFL_ASSERT(cond)    assert(cond)

typedef struct {
    uint32_t code;
    spvrefl_capability_e enum_bit;
    spvrefl_capability_e also_declares_enum_bits [2];
    char const * name_str;
} ispvr_capability_entry_t;
static ispvr_capability_entry_t const ispvr_capability_data [] = {
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
static int const ispvr_capability_data_count = sizeof(ispvr_capability_data) / sizeof(ispvr_capability_data[0]);

typedef struct {
    uint32_t code;
    spvrefl_capability_e enum_bit;
    int param_count;    // 0, 1, or 3
    char const * name_str;
} ispvr_execmode_entry_t;
static ispvr_execmode_entry_t const ispvr_execmode_data [] = {
    {   0, spvrefl_execmode_Invocations                     , 1, "Invocations"},
    {   1, spvrefl_execmode_SpacingEqual                    , 0, "SpacingEqual"},
    {   2, spvrefl_execmode_SpacingFractionalEven           , 0, "SpacingFractionalEven"},
    {   3, spvrefl_execmode_SpacingFractionalOdd            , 0, "SpacingFractionalOdd"},
    {   4, spvrefl_execmode_VertexOrderCw                   , 0, "VertexOrderCw"},
    {   5, spvrefl_execmode_VertexOrderCcw                  , 0, "VertexOrderCcw"},
    {   6, spvrefl_execmode_PixelCenterInteger              , 0, "PixelCenterInteger"},
    {   7, spvrefl_execmode_OriginUpperLeft                 , 0, "OriginUpperLeft"},
    {   8, spvrefl_execmode_OriginLowerLeft                 , 0, "OriginLowerLeft"},
    {   9, spvrefl_execmode_EarlyFragmentTests              , 0, "EarlyFragmentTests"},
    {  10, spvrefl_execmode_PointMode                       , 0, "PointMode"},
    {  11, spvrefl_execmode_Xfb                             , 0, "Xfb"},
    {  12, spvrefl_execmode_DepthReplacing                  , 0, "DepthReplacing"},
    {  14, spvrefl_execmode_DepthGreater                    , 0, "DepthGreater"},
    {  15, spvrefl_execmode_DepthLess                       , 0, "DepthLess"},
    {  16, spvrefl_execmode_DepthUnchanged                  , 0, "DepthUnchanged"},
    {  17, spvrefl_execmode_LocalSize                       , 3, "LocalSize"},
    {  18, spvrefl_execmode_LocalSizeHint                   , 3, "LocalSizeHint"},
    {  19, spvrefl_execmode_InputPoints                     , 0, "InputPoints"},
    {  20, spvrefl_execmode_InputLines                      , 0, "InputLines"},
    {  21, spvrefl_execmode_InputLinesAdjacency             , 0, "InputLinesAdjacency"},
    {  22, spvrefl_execmode_Triangles                       , 0, "Triangles"},
    {  23, spvrefl_execmode_InputTrianglesAdjacency         , 0, "InputTrianglesAdjacency"},
    {  24, spvrefl_execmode_Quads                           , 0, "Quads"},
    {  25, spvrefl_execmode_Isolines                        , 0, "Isolines"},
    {  26, spvrefl_execmode_OutputVertices                  , 1, "OutputVertices"},
    {  27, spvrefl_execmode_OutputPoints                    , 0, "OutputPoints"},
    {  28, spvrefl_execmode_OutputLineStrip                 , 0, "OutputLineStrip"},
    {  29, spvrefl_execmode_OutputTriangleStrip             , 0, "OutputTriangleStrip"},
    {  30, spvrefl_execmode_VecTypeHint                     , 1, "VecTypeHint"},
    {  31, spvrefl_execmode_ContractionOff                  , 0, "ContractionOff"},
    {  33, spvrefl_execmode_Initializer                     , 0, "Initializer"},
    {  34, spvrefl_execmode_Finalizer                       , 0, "Finalizer"},
    {  35, spvrefl_execmode_SubgroupSize                    , 1, "SubgroupSize"},
    {  36, spvrefl_execmode_SubgroupsPerWorkgroup           , 1, "SubgroupsPerWorkgroup"},
    {  37, spvrefl_execmode_SubgroupsPerWorkgroupId         , 1, "SubgroupsPerWorkgroupId"},
    {  38, spvrefl_execmode_LocalSizeId                     , 3, "LocalSizeId"},
    {  39, spvrefl_execmode_LocalSizeHintId                 , 3, "LocalSizeHintId"},
    {4446, spvrefl_execmode_PostDepthCoverage               , 0, "PostDepthCoverage"},
    {4459, spvrefl_execmode_DenormPreserve                  , 1, "DenormPreserve"},
    {4460, spvrefl_execmode_DenormFlushToZero               , 1, "DenormFlushToZero"},
    {4461, spvrefl_execmode_SignedZeroInfNanPreserve        , 1, "SignedZeroInfNanPreserve"},
    {4462, spvrefl_execmode_RoundingModeRTE                 , 1, "RoundingModeRTE"},
    {4463, spvrefl_execmode_RoundingModeRTZ                 , 1, "RoundingModeRTZ"},
    {5027, spvrefl_execmode_StencilRefReplacingEXT          , 0, "StencilRefReplacingEXT"},
    {5269, spvrefl_execmode_OutputLinesNV                   , 0, "OutputLinesNV"},
    {5270, spvrefl_execmode_OutputPrimitivesNV              , 1, "OutputPrimitivesNV"},
    {5289, spvrefl_execmode_DerivativeGroupQuadsNV          , 0, "DerivativeGroupQuadsNV"},
    {5290, spvrefl_execmode_DerivativeGroupLinearNV         , 0, "DerivativeGroupLinearNV"},
    {5298, spvrefl_execmode_OutputTrianglesNV               , 0, "OutputTrianglesNV"},
    {5366, spvrefl_execmode_PixelInterlockOrderedEXT        , 0, "PixelInterlockOrderedEXT"},
    {5367, spvrefl_execmode_PixelInterlockUnorderedEXT      , 0, "PixelInterlockUnorderedEXT"},
    {5368, spvrefl_execmode_SampleInterlockOrderedEXT       , 0, "SampleInterlockOrderedEXT"},
    {5369, spvrefl_execmode_SampleInterlockUnorderedEXT     , 0, "SampleInterlockUnorderedEXT"},
    {5370, spvrefl_execmode_ShadingRateInterlockOrderedEXT  , 0, "ShadingRateInterlockOrderedEXT"},
    {5371, spvrefl_execmode_ShadingRateInterlockUnorderedEXT, 0, "ShadingRateInterlockUnorderedEXT"},
};
static int const ispvr_execmode_data_count = sizeof(ispvr_execmode_data) / sizeof(ispvr_execmode_data[0]);

typedef struct {
    uint32_t code;
    spvrefl_decoration_e enum_bit;
    int param_count;
    char const * name_str;
} ispvr_decoration_entry_t;
static ispvr_decoration_entry_t const ispvr_decoration_data [] = {
    {   0, spvrefl_decoration_RelaxedPrecision           , 0, "RelaxedPrecision"           },  // params: --
    {   1, spvrefl_decoration_SpecId                     , 1, "SpecId"                     },  // params: Literal:Specialization Constant ID
    {   2, spvrefl_decoration_Block                      , 0, "Block"                      },  // params: --
    {   3, spvrefl_decoration_BufferBlock                , 0, "BufferBlock"                },  // params: --
    {   4, spvrefl_decoration_RowMajor                   , 0, "RowMajor"                   },  // params: --
    {   5, spvrefl_decoration_ColMajor                   , 0, "ColMajor"                   },  // params: --
    {   6, spvrefl_decoration_ArrayStride                , 1, "ArrayStride"                },  // params: Literal:Array Stride
    {   7, spvrefl_decoration_MatrixStride               , 1, "MatrixStride"               },  // params: Literal:Matrix Stride
    {   8, spvrefl_decoration_GLSLShared                 , 0, "GLSLShared"                 },  // params: --
    {   9, spvrefl_decoration_GLSLPacked                 , 0, "GLSLPacked"                 },  // params: --
    {  10, spvrefl_decoration_CPacked                    , 0, "CPacked"                    },  // params: --
    {  11, spvrefl_decoration_BuiltIn                    , 1, "BuiltIn"                    },  // params: BuiltIn
    {  13, spvrefl_decoration_NoPerspective              , 0, "NoPerspective"              },  // params: --
    {  14, spvrefl_decoration_Flat                       , 0, "Flat"                       },  // params: --
    {  15, spvrefl_decoration_Patch                      , 0, "Patch"                      },  // params: --
    {  16, spvrefl_decoration_Centroid                   , 0, "Centroid"                   },  // params: --
    {  17, spvrefl_decoration_Sample                     , 0, "Sample"                     },  // params: --
    {  18, spvrefl_decoration_Invariant                  , 0, "Invariant"                  },  // params: --
    {  19, spvrefl_decoration_Restrict                   , 0, "Restrict"                   },  // params: --
    {  20, spvrefl_decoration_Aliased                    , 0, "Aliased"                    },  // params: --
    {  21, spvrefl_decoration_Volatile                   , 0, "Volatile"                   },  // params: --
    {  22, spvrefl_decoration_Constant                   , 0, "Constant"                   },  // params: --
    {  23, spvrefl_decoration_Coherent                   , 0, "Coherent"                   },  // params: --
    {  24, spvrefl_decoration_NonWritable                , 0, "NonWritable"                },  // params: --
    {  25, spvrefl_decoration_NonReadable                , 0, "NonReadable"                },  // params: --
    {  26, spvrefl_decoration_Uniform                    , 0, "Uniform"                    },  // params: --
    {  27, spvrefl_decoration_UniformId                  , 1, "UniformId"                  },  // params: Scope<id>:Execution
    {  28, spvrefl_decoration_SaturatedConversion        , 0, "SaturatedConversion"        },  // params: --
    {  29, spvrefl_decoration_Stream                     , 1, "Stream"                     },  // params: Literal:Stream Number
    {  30, spvrefl_decoration_Location                   , 1, "Location"                   },  // params: Literal:Location
    {  31, spvrefl_decoration_Component                  , 1, "Component"                  },  // params: Literal:Component
    {  32, spvrefl_decoration_Index                      , 1, "Index"                      },  // params: Literal:Index
    {  33, spvrefl_decoration_Binding                    , 1, "Binding"                    },  // params: Literal:Binding Point
    {  34, spvrefl_decoration_DescriptorSet              , 1, "DescriptorSet"              },  // params: Literal:Descriptor Set
    {  35, spvrefl_decoration_Offset                     , 1, "Offset"                     },  // params: Literal:Byte Offset
    {  36, spvrefl_decoration_XfbBuffer                  , 1, "XfbBuffer"                  },  // params: Literal:XFB Buffer Number
    {  37, spvrefl_decoration_XfbStride                  , 1, "XfbStride"                  },  // params: Literal:XFB Stride
    {  38, spvrefl_decoration_FuncParamAttr              , 1, "FuncParamAttr"              },  // params: Function Parameter Attribute:Function Parameter Attribute
    {  39, spvrefl_decoration_FPRoundingMode             , 1, "FPRoundingMode"             },  // params: FP Rounding Mode:Floating-Point Rounding Mode
    {  40, spvrefl_decoration_FPFastMathMode             , 1, "FPFastMathMode"             },  // params: FP Fast Math Mode:Fast-Math Mode
    {  41, spvrefl_decoration_LinkageAttributes          , 2, "LinkageAttributes"          },  //[INVERTED] params: Literal:Name,Linkage Type:Linkage Type
    {  42, spvrefl_decoration_NoContraction              , 0, "NoContraction"              },  // params: --
    {  43, spvrefl_decoration_InputAttachmentIndex       , 1, "InputAttachmentIndex"       },  // params: Literal:Attachment Index
    {  44, spvrefl_decoration_Alignment                  , 1, "Alignment"                  },  // params: Literal:Alignment
    {  45, spvrefl_decoration_MaxByteOffset              , 1, "MaxByteOffset"              },  // params: Literal:Max Byte Offset
    {  46, spvrefl_decoration_AlignmentId                , 1, "AlignmentId"                },  // params: <id>:Alignment
    {  47, spvrefl_decoration_MaxByteOffsetId            , 1, "MaxByteOffsetId"            },  // params: <id>:Max Byte Offset
    {4469, spvrefl_decoration_NoSignedWrap               , 0, "NoSignedWrap"               },  // params: --
    {4470, spvrefl_decoration_NoUnsignedWrap             , 0, "NoUnsignedWrap"             },  // params: --
    {4999, spvrefl_decoration_ExplicitInterpAMD          , 0, "ExplicitInterpAMD"          },  // params: --
    {5248, spvrefl_decoration_OverrideCoverageNV         , 0, "OverrideCoverageNV"         },  // params: --
    {5250, spvrefl_decoration_PassthroughNV              , 0, "PassthroughNV"              },  // params: --
    {5252, spvrefl_decoration_ViewportRelativeNV         , 0, "ViewportRelativeNV"         },  // params: --
    {5256, spvrefl_decoration_SecondaryViewportRelativeNV, 1, "SecondaryViewportRelativeNV"},  // params: Literal:Offset
    {5271, spvrefl_decoration_PerPrimitiveNV             , 0, "PerPrimitiveNV"             },  // params: --
    {5272, spvrefl_decoration_PerViewNV                  , 0, "PerViewNV"                  },  // params: --
    {5273, spvrefl_decoration_PerTaskNV                  , 0, "PerTaskNV"                  },  // params: --
    {5285, spvrefl_decoration_PerVertexNV                , 0, "PerVertexNV"                },  // params: --
    {5300, spvrefl_decoration_NonUniform                 , 0, "NonUniform"                 },  // params: --
  //{5300, spvrefl_decoration_NonUniformEXT              , 0, "NonUniformEXT"              },  // params: --
    {5355, spvrefl_decoration_RestrictPointer            , 0, "RestrictPointer"            },  // params: --
  //{5355, spvrefl_decoration_RestrictPointerEXT         , 0, "RestrictPointerEXT"         },  // params: --
    {5356, spvrefl_decoration_AliasedPointer             , 0, "AliasedPointer"             },  // params: --
  //{5356, spvrefl_decoration_AliasedPointerEXT          , 0, "AliasedPointerEXT"          },  // params: --
    {5634, spvrefl_decoration_CounterBuffer              , 1, "CounterBuffer"              },  // params: <id>:Counter Buffer
  //{5634, spvrefl_decoration_HlslCounterBufferGOOGLE    , 1, "HlslCounterBufferGOOGLE"    },  // params: <id>:Counter Buffer
    {5635, spvrefl_decoration_UserSemantic               , 1, "UserSemantic"               },  // params: Literal:Semantic
  //{5635, spvrefl_decoration_HlslSemanticGOOGLE         , 1, "HlslSemanticGOOGLE"         },  // params: Literal:Semantic
    {5636, spvrefl_decoration_UserTypeGOOGLE             , 1, "UserTypeGOOGLE"             },  // params: Literal:User Type
};
static int const ispvr_decoration_data_count = sizeof(ispvr_decoration_data) / sizeof(ispvr_decoration_data[0]);

static void
ispvr_zero_memory (void * ptr, size_t size) {
    char * p = (char *)ptr;
    for (size_t i = 0; i < size; ++i)
        p[i] = 0;
}

typedef struct {
    uint32_t const * ptr_begin;
    uint32_t const * ptr_end;
    uint32_t const * ptr_cur;

    uint32_t cur_word;
    uint16_t inst_word_count;
    uint16_t inst_opcode;
} ispvr_input_t;

static void
ispvr_input_init (ispvr_input_t * input, void const * data, int size_in_words) {
    input->ptr_begin = (uint32_t const *)data;
    input->ptr_end = input->ptr_begin + size_in_words;
    input->ptr_cur = input->ptr_begin;
}
static bool
ispvr_input_ended (ispvr_input_t const * input) {
    return !input || !input->ptr_cur || input->ptr_cur >= input->ptr_end;
}
static uint32_t
ispvr_input_advance_data (ispvr_input_t * input) {
    if (input->ptr_cur < input->ptr_end)
        input->cur_word = *input->ptr_cur++;
    else
        input->cur_word = 0;
    return input->cur_word;
}
static void
ispvr_input_advance_instruction (ispvr_input_t * input) {
    ispvr_input_advance_data(input);
    input->inst_word_count = (uint16_t)(input->cur_word >> 16);
    input->inst_opcode = (uint16_t)(input->cur_word & 0xFFFF);
}

typedef struct {
    char * begin;
    char * end;
    char * cur;
} ispvr_stringtab_t;

static char *
ispvr_stringtab_push (ispvr_stringtab_t * strtab, ispvr_input_t * input, int expected_words, int * out_used_words) {
    char * ret = strtab->cur;
    int used_words = 0;
    bool ended = false;
    while (!ended && strtab->cur < strtab->end) {
        uint32_t w = ispvr_input_advance_data(input);
        used_words += 1;
        for (int i = 0; i < 4 && !ended; ++i) {
            char c = w & 0xFF;
            w >>= 8;
            *strtab->cur++ = c;
            ended = ('\0' == c);
        }
    }
    if (expected_words >= 0 && expected_words != used_words) {
        ERROR_PRINT("[SPVREFL INTERNAL] Expected %u words in the literal string '%s', but found %u.\n", expected_words, ret, used_words);
    }
    if (out_used_words)
        *out_used_words = used_words;
    return ret;
}

static void
ispvr_validate_capability_data () {
    //DEBUG_PRINT("[INTERNAL] Capbilities enum has %u struct_members.\n", spvrefl_capability__count);
    //DEBUG_PRINT("[INTERNAL] Capbilities table has %u entries.\n", ispvr_capability_data_count);
    if (spvrefl_capability__count != ispvr_capability_data_count)
        ERROR_PRINT("[INTERNAL ERROR] Capabilities enum and its corresponding table don't match in size.\n");
    for (int i = 0; i < ispvr_capability_data_count; ++i) {
        if (i != ispvr_capability_data[i].enum_bit)
            ERROR_PRINT("[INTERNAL ERROR] Capability entry #%u doesn't match its enum bit #%d.\n", i, ispvr_capability_data[i].enum_bit);
    }
}
static void
ispvr_capability_add_simple (spvrefl_capability_set_t * capability_set, spvrefl_capability_e new_capability) {
    capability_set->bits[new_capability / 32] |= 1U << (new_capability % 32);
}
static void
ispvr_capability_add_with_requisites (spvrefl_capability_set_t * capability_set, spvrefl_capability_e new_capability) {
    ispvr_capability_add_simple(capability_set, new_capability);
    for (int i = 0; i < 2; ++i) {
        int additional = ispvr_capability_data[new_capability].also_declares_enum_bits[i];
        if (additional != -1)
            ispvr_capability_add_with_requisites(capability_set, additional);
    }
}
static void
ispvr_capability_find_and_add_with_requisites (spvrefl_capability_set_t * capability_set, uint32_t new_capability_code) {
    int i = 0;
    for (; i < ispvr_capability_data_count; ++i)
        if (ispvr_capability_data[i].code == new_capability_code)
            break;
    if (i < ispvr_capability_data_count) {
        ispvr_capability_add_with_requisites(capability_set, ispvr_capability_data[i].enum_bit);
    } else {
        ERROR_PRINT("[SPVREFL INTERNAL ERROR] Couldn't find capability #%u in internal data tables.\n", new_capability_code);
    }
}

static spvrefl_struct_members_t *
ispvr_alloc_struct_for_id (spvrefl_info_t * info, uint32_t struct_id, spvrefl_struct_members_t * structs) {
    if (NULL == info->ids[struct_id].struct_members) {
        SPVREFL_ASSERT(spvrefl_idtype_struct == info->ids[struct_id].type || spvrefl_idtype_unknown == info->ids[struct_id].type);
        if (spvrefl_idtype_unknown == info->ids[struct_id].type) {
            info->ids[struct_id].type = spvrefl_idtype_struct;
            info->struct_needed_count += 1;
            if (info->struct_count < SPVREFL_OPT_MAX_STRUCT_COUNT) {
                info->ids[struct_id].struct_members = structs + info->struct_count;
                info->struct_count += 1;
            }
        }
    }
    return info->ids[struct_id].struct_members;
}

static ispvr_execmode_entry_t const *
ispvr_execmode_find_entry (uint32_t execmode_code) {
    for (int i = 0; i < ispvr_execmode_data_count; ++i)
        if (ispvr_execmode_data[i].code == execmode_code)
            return &ispvr_execmode_data[i];
    return NULL;
}
static bool
ispvr_execmode_add_to_entrypoint (spvrefl_entry_point_set_t * entry_points, uint32_t entry_point_id, spvrefl_execmode_e execmode, int actual_param_count, uint32_t params [3]) {
    bool ret = false;
    ispvr_execmode_entry_t const * eme = ispvr_execmode_find_entry(execmode);
    SPVREFL_ASSERT(eme != NULL);
    SPVREFL_ASSERT(eme->param_count == actual_param_count);
    if (eme) {
        if (eme->param_count == actual_param_count) {
            spvrefl_entry_point_t * ep = NULL;
            for (int i = 0; i < entry_points->count; ++i)
                if (entry_point_id == entry_points->functions[i].id) {
                    ep = &entry_points->functions[i];
                    break;
                }
            SPVREFL_ASSERT(ep != NULL);

            if (ep) {
                ep->execmode.mode = eme->enum_bit;
                ep->execmode.param_count = actual_param_count;
                for (int i = 0; i < actual_param_count; ++i)
                    ep->execmode.params[i] = params[i];
                ret = true;
            } else {
                ERROR_PRINT("[SPVREFL INTERNAL] Couldn't find the specified entry point ID #%u.", entry_point_id);
            }
        } else {
            ERROR_PRINT("[SPVREFL INTERNAL] Expected %d parameters for execmode \"%s\", but %d params found.", eme->param_count, eme->name_str, actual_param_count);
        }
    } else {
        ERROR_PRINT("[SPVREFL INTERNAL] Couldn't find the specified execution mode data (%d).", execmode);
    }
    return ret;
}

static ispvr_decoration_entry_t const *
ispvr_decoration_find_entry (uint32_t decoration_code) {
    for (int i = 0; i < ispvr_decoration_data_count; ++i)
        if (ispvr_decoration_data[i].code == decoration_code)
            return &ispvr_decoration_data[i];
    return NULL;
}
static bool
ispvr_decorate (spvrefl_decoration_set_t * decoration_set, /*spvrefl_decoration_index_set_t * index_set,*/ spvrefl_decoration_e decoration_no, int param_count, uint32_t param1) {
    bool ret = false;
    ispvr_decoration_entry_t const * de = ispvr_decoration_find_entry(decoration_no);
    SPVREFL_ASSERT(de);
    if (de) {
        decoration_set->needed_count += 1;
        if (decoration_set->count < SPVREFL_OPT_MAX_TOTAL_DECORATIONS) {
            int idx = decoration_set->count;
            decoration_set->count += 1;
            decoration_set->decorations[idx] = de->enum_bit;
            if (param_count > 0)
                decoration_set->param_ones[idx].raw_value_ = param1;
            ret = true;
        }
    } else {
    }
    return ret;
}

spvrefl_result_t
spvrefl_reflect (
    void const * input_spirv,
    int input_size_bytes,
    spvrefl_info_t * out_reflection_info,
    void * scratch_memory,
    int scratch_memory_size_bytes
) {
    spvrefl_result_t ret = {0};

    /* Validate some internal stuff... */
    //ispvr_validate_capability_data();

    /* Check parameter errors... */
    if (!input_spirv || input_size_bytes <= 0 || !out_reflection_info) {
        ret.error_code = spvrefl_error_bad_params;
        return ret;
    }
    if (input_size_bytes % 4 != 0 || input_size_bytes < 20) {
        ret.error_code = spvrefl_error_bad_input_length;
        return ret;
    }

    /* Zero-out output reflection info... */
    spvrefl_info_t * info = out_reflection_info;
    ispvr_zero_memory(info, sizeof(*info));

    /* Setup use of input... */
    ispvr_input_t input_storage;
    ispvr_input_t * input = &input_storage;
    ispvr_input_init(input, input_spirv, input_size_bytes / 4);

    /* Read header... */
    info->magic_number = ispvr_input_advance_data(input);
    if (info->magic_number != 0x07230203) {
        ret.error_code = spvrefl_error_bad_magic_number;
        return ret;
    }
    ispvr_input_advance_data(input);
    info->version_major = (input->cur_word >> 16) & 0xFF;
    info->version_minor = (input->cur_word >>  8) & 0xFF;
    info->generator = ispvr_input_advance_data(input);
    info->id_upper_bound = ispvr_input_advance_data(input);
    ispvr_input_advance_data(input);

    /* Setup use of scratch memory (id table and string table) */
    if (!scratch_memory || scratch_memory_size_bytes < (int)(info->id_upper_bound * sizeof(spvrefl_id_data_t))) {
        ret.error_code = spvrefl_error_insufficient_scratch_mem;
        return ret;
    }
    ispvr_zero_memory(scratch_memory, scratch_memory_size_bytes);

    char * scratch = (char *)scratch_memory;
    int scratch_left = scratch_memory_size_bytes;

    info->ids_count = (int)info->id_upper_bound;
    info->ids = (spvrefl_id_data_t *)scratch;
    scratch += info->id_upper_bound * sizeof(spvrefl_id_data_t);
    scratch_left -= info->id_upper_bound * sizeof(spvrefl_id_data_t);
    for (int i = 0; i < info->ids_count; ++i) {
        info->ids[i].id = ~0U;
        info->ids[i].name = NULL;
    }

    // Struct table:
    spvrefl_struct_members_t * structtab = (spvrefl_struct_members_t *)scratch;
    scratch += SPVREFL_OPT_MAX_STRUCT_COUNT * sizeof(spvrefl_struct_members_t);
    scratch_left -= SPVREFL_OPT_MAX_STRUCT_COUNT * sizeof(spvrefl_struct_members_t);
    ispvr_zero_memory(structtab, SPVREFL_OPT_MAX_STRUCT_COUNT * sizeof(spvrefl_struct_members_t));
    //for (int i = 0; i < SPVREFL_OPT_MAX_STRUCT_COUNT; ++i) {
    //    structtab[i].count = 0;
    //    structtab[i].needed_count = 0;
    //    for (int j = 0; j < SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT; ++j) {
    //        structtab[i].members[j].name = NULL;
    //        structtab[i].members[j].decorations.count = 0;
    //        structtab[i].members[j].decorations.needed_count = 0;
    //        for (int k = 0; k < SPVREFL_OPT_MAX_DECORATIONS_PER_ID_OR_MEMBER; ++k)
    //            structtab[i].members[j].decorations.indices[k] = -1;
    //    }
    //}

    // String table must be the last thing in scratch memory, because it has variable length.
    ispvr_stringtab_t strtab_storage = {0};
    ispvr_stringtab_t * strtab = &strtab_storage;
    if (scratch_left > 0) {
        strtab->begin = scratch;
        strtab->end = strtab->begin + scratch_left - 1;  // Reserve 1 byte for a sentinel NUL at the end
        strtab->cur = strtab->begin;
        *strtab->end = '\0';
    }

    /* Special IDs to be filled later... */
    uint32_t id_of_source_file_name_string = ~0U;

    /* Read the instructions... */
    while (!ispvr_input_ended(input)) {
        ispvr_input_advance_instruction(input);
        info->instruction_count += 1;
        
        uint16_t const word_count = input->inst_word_count;
        uint16_t const opcode = input->inst_opcode;

        switch (opcode) {
        case 2: {   // OpSourceContinued
            SPVREFL_ASSERT(2 <= word_count);
            DEBUG_PRINT("- (@%u) OpSourceContinued (%u words)\n", info->instruction_count, input->inst_word_count);
            for (unsigned i = 1; i < input->inst_word_count; ++i)
                ispvr_input_advance_data(input);
        } break;
        case 3: {  // OpSource
            SPVREFL_ASSERT(3 <= word_count);
            info->source_language = ispvr_input_advance_data(input);
            info->source_language_version = ispvr_input_advance_data(input);
            if (word_count > 3)
                id_of_source_file_name_string = ispvr_input_advance_data(input);
            if (word_count > 4)
                info->source_text = ispvr_stringtab_push(strtab, input, word_count - 4, NULL);
        } break;
        case 4: {  // OpSourceExtension
            SPVREFL_ASSERT(2 <= word_count);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 1, NULL);
            info->source_extensions.needed_count += 1;
            if (info->source_extensions.count < SPVREFL_OPT_MAX_SOURCE_EXTENSIONS)
                info->source_extensions.names[info->source_extensions.count++] = str;
        } break;
        case 5: {   // OpName
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t id = ispvr_input_advance_data(input);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 2, NULL);
            SPVREFL_ASSERT(id < info->id_upper_bound);
            info->ids[id].id = id;
            info->ids[id].name = str;
        } break;
        case 6: {   // OpMemberName
            SPVREFL_ASSERT(4 <= word_count);
            uint32_t id = ispvr_input_advance_data(input);
            int member_no = (int)ispvr_input_advance_data(input);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 3, NULL);
            SPVREFL_ASSERT(id < info->id_upper_bound);
            spvrefl_struct_members_t * struct_ptr = ispvr_alloc_struct_for_id(info, id, structtab);
            if (member_no >= struct_ptr->needed_count)
                struct_ptr->needed_count = member_no + 1;
            if (member_no >= struct_ptr->count && member_no < SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT)
                struct_ptr->count = member_no + 1;
            if (member_no < SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT)
                struct_ptr->members[member_no].name = str;
        } break;
        case 10: {  // OpExtension
            SPVREFL_ASSERT(2 <= word_count);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 1, NULL);
            info->extensions.needed_count += 1;
            if (info->extensions.count < SPVREFL_OPT_MAX_EXTENSIONS)
                info->extensions.names[info->extensions.count++] = str;
        } break;
        case 11: {  // OpExtInstImport
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t id = ispvr_input_advance_data(input);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 2, NULL);
            info->instruction_sets.needed_count += 1;
            if (info->instruction_sets.count < SPVREFL_OPT_MAX_EXTENDED_INSTRUCTION_SET_IMPORTS) {
                info->instruction_sets.ids[info->instruction_sets.count] = id;
                info->instruction_sets.names[info->instruction_sets.count] = str;
                info->instruction_sets.count += 1;
            }
        } break;
        case 12: {  // OpExtInst
            SPVREFL_ASSERT(5 <= word_count);
            DEBUG_PRINT("- (@%u) OpExtInst (%u words)\n", info->instruction_count, input->inst_word_count);
            for (unsigned i = 1; i < input->inst_word_count; ++i)
                ispvr_input_advance_data(input);
        } break;
        case 14: {  // OpMemoryModel
            SPVREFL_ASSERT(3 == word_count);
            info->addressing_model = ispvr_input_advance_data(input);
            info->memory_model = ispvr_input_advance_data(input);
        } break;
        case 15: {  // OpEntryPoint
            SPVREFL_ASSERT(4 <= word_count);
            info->entry_points.needed_count += 1;
            int cur_ep = info->entry_points.count;
            if (cur_ep < SPVREFL_OPT_MAX_ENTRY_POINTS) {
                info->entry_points.count += 1;
                info->entry_points.functions[cur_ep].execution_model = ispvr_input_advance_data(input);
                info->entry_points.functions[cur_ep].id = ispvr_input_advance_data(input);
                int name_words = 0;
                info->entry_points.functions[cur_ep].name = ispvr_stringtab_push(strtab, input, -1, &name_words);
                int params_count = word_count - 3 - name_words;
                int params_that_fit = (params_count <= SPVREFL_OPT_MAX_ENTRY_POINT_FUNC_PARAMS ? params_count : SPVREFL_OPT_MAX_ENTRY_POINT_FUNC_PARAMS);
                info->entry_points.functions[cur_ep].needed_param_count = params_count;
                info->entry_points.functions[cur_ep].param_count = params_that_fit;
                for (int i = 0; i < params_that_fit; ++i)
                    info->entry_points.functions[cur_ep].parameter_ids[i] = ispvr_input_advance_data(input);
                for (int i = params_that_fit; i < params_count; ++i)
                    ispvr_input_advance_data(input);
            } else {
                for (unsigned i = 1; i < word_count; ++i)
                    ispvr_input_advance_data(input);
            }
        } break;
        case 16: {  // OpExecutionMode
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t entry_point_id = ispvr_input_advance_data(input);
            SPVREFL_ASSERT(entry_point_id < info->id_upper_bound);
            uint32_t exec_mode_no = ispvr_input_advance_data(input);
            int param_count = word_count - 3;
            SPVREFL_ASSERT(param_count <= 3);
            uint32_t params [3];
            for (int i = 0; i < 3 && i < param_count; ++i)
                params[i] = ispvr_input_advance_data(input);
            ispvr_execmode_add_to_entrypoint(&info->entry_points, entry_point_id, exec_mode_no, param_count, params);
        } break;
        case 17: {  // OpCapability
            SPVREFL_ASSERT(2 == word_count);
            uint32_t cap = ispvr_input_advance_data(input);
            ispvr_capability_find_and_add_with_requisites(&info->capabilities, cap);
        } break;

        case 71: {   // OpDecorate
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t target_id = ispvr_input_advance_data(input);
            uint32_t decoration = ispvr_input_advance_data(input);
            int param_count = (word_count > 3 ? 1 : 0);
            uint32_t param = (param_count > 0 ? ispvr_input_advance_data(input) : 0);
            for (unsigned i = 4; i < word_count; ++i)
                ispvr_input_advance_data(input);
            SPVREFL_ASSERT(target_id < info->id_upper_bound);
            //DEBUG_PRINT("- (@%u) OpDecorate (%u words): #%u, %u\n", info->instruction_count, input->inst_word_count, target_id, decoration);
            ispvr_decorate(/*&info->decorations,*/ &info->ids[target_id].decorations, decoration, param_count, param);
        } break;
        case 72: {   // OpMemberDecorate
            SPVREFL_ASSERT(4 <= word_count);
            uint32_t struct_id = ispvr_input_advance_data(input);
            int member_no = ispvr_input_advance_data(input);
            uint32_t decoration = ispvr_input_advance_data(input);
            int param_count = (word_count > 4 ? 1 : 0);
            uint32_t param = (param_count > 0 ? ispvr_input_advance_data(input) : 0);
            for (unsigned i = 5; i < word_count; ++i)
                ispvr_input_advance_data(input);
            SPVREFL_ASSERT(struct_id < info->id_upper_bound);
            SPVREFL_ASSERT(info->ids[struct_id].type == spvrefl_idtype_struct);
            SPVREFL_ASSERT(info->ids[struct_id].struct_members);
            SPVREFL_ASSERT(info->ids[struct_id].struct_members->count > member_no);
            //DEBUG_PRINT("- (@%u) OpMemberDecorate (%u words): #%u, %u, %u\n", info->instruction_count, input->inst_word_count, struct_id, member_no, decoration);
            ispvr_decorate(/*&info->decorations,*/ &info->ids[struct_id].struct_members->members[member_no].decorations, decoration, param_count, param);
        } break;
        case 332: {   // OpDecorateId
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t target_id = ispvr_input_advance_data(input);
            uint32_t decoration = ispvr_input_advance_data(input);
            for (unsigned i = 3; i < word_count; ++i)
                ispvr_input_advance_data(input);    // These are IDs
            SPVREFL_ASSERT(target_id < info->id_upper_bound);
            DEBUG_PRINT("- (@%u) OpDecorateId (%u words): #%u, %u\n", info->instruction_count, input->inst_word_count, target_id, decoration);
        } break;
        case 5632: {   // OpDecorateString
            SPVREFL_ASSERT(4 <= word_count);
            uint32_t target_id = ispvr_input_advance_data(input);
            uint32_t decoration = ispvr_input_advance_data(input);
            for (unsigned i = 3; i < word_count; ++i)
                ispvr_input_advance_data(input);
            SPVREFL_ASSERT(target_id < info->id_upper_bound);
            DEBUG_PRINT("- (@%u) OpDecorateString (%u words): #%u, %u\n", info->instruction_count, input->inst_word_count, target_id, decoration);
        } break;
        case 5633: {   // OpMemberDecorateString
            SPVREFL_ASSERT(5 <= word_count);
            uint32_t struct_id = ispvr_input_advance_data(input);
            uint32_t member_no = ispvr_input_advance_data(input);
            uint32_t decoration = ispvr_input_advance_data(input);
            for (unsigned i = 4; i < word_count; ++i)
                ispvr_input_advance_data(input);
            SPVREFL_ASSERT(struct_id < info->id_upper_bound);
            DEBUG_PRINT("- (@%u) OpMemberDecorateString (%u words): #%u, %u, %u\n", info->instruction_count, input->inst_word_count, struct_id, member_no, decoration);
        } break;

        case 7: {   // OpString
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t id = ispvr_input_advance_data(input);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 2, NULL);
            SPVREFL_ASSERT(id < info->id_upper_bound);
            DEBUG_PRINT("- (@%u) OpString (%u words): #%u -> \"%s\"\n", info->instruction_count, input->inst_word_count, id, str);
        } break;
        case 8: {   // OpLine
            SPVREFL_ASSERT(4 == word_count);
            uint32_t file_id = ispvr_input_advance_data(input);
            uint32_t line_no = ispvr_input_advance_data(input);
            uint32_t column_no = ispvr_input_advance_data(input);
            SPVREFL_ASSERT(file_id < info->id_upper_bound);
            DEBUG_PRINT("- (@%u) OpLine (%u words): #%u, %u, %u\n", info->instruction_count, input->inst_word_count, file_id, line_no, column_no);
        } break;

        case 73: {  // OpDecorationGroup
            SPVREFL_ASSERT(2 == word_count);
            uint32_t result_id = ispvr_input_advance_data(input);
            DEPRECATED("- (@%u) OpDecorationGroup (%u words) -> #%u\n", info->instruction_count, input->inst_word_count, result_id);
        } break;
        case 74: {  // OpGroupDecorate
            SPVREFL_ASSERT(2 <= word_count);
            uint32_t group_id = ispvr_input_advance_data(input);
            DEPRECATED("- (@%u) OpGroupDecorate (%u words) -> #%u\n", info->instruction_count, input->inst_word_count, group_id);
            for (unsigned i = 2; i < word_count; ++i)
                ispvr_input_advance_data(input);
        } break;
        case 75: {  // OpGroupMemberDecorate
            SPVREFL_ASSERT(2 <= word_count);
            uint32_t group_id = ispvr_input_advance_data(input);
            DEPRECATED("- (@%u) OpGroupMemberDecorate (%u words) -> #%u\n", info->instruction_count, input->inst_word_count, group_id);
            for (unsigned i = 2; i < word_count; ++i)
                ispvr_input_advance_data(input);
        } break;
        default: {
            //DEBUG_PRINT("[%hu, 0x%04hX] ", input->inst_word_count, input->inst_opcode);
            for (unsigned i = 1; i < word_count; ++i)
                ispvr_input_advance_data(input);
        } break;
        }
    }
    //DEBUG_PRINT("\n");

    ret.scratch_memory_used_bytes = (int)(strtab->cur - (char *)scratch_memory);
    return ret;
}

char const *
spvrefl_get_capability_name (spvrefl_capability_e cap) {
    if (cap >= 0 && cap < ispvr_capability_data_count)
        return ispvr_capability_data[cap].name_str;
    else
        return NULL;
}

char const *
spvrefl_get_decoration_name (spvrefl_decoration_e dec) {
    if (dec >= 0 && dec < ispvr_decoration_data_count)
        return ispvr_decoration_data[dec].name_str;
    else
        return NULL;
}

#endif  // SPVREFL_IMPLEMENTATION
