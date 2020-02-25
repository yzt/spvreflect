//#if defined(SPVREFL_IMPLEMENTATION)
#include "spvreflect.h"

#include <stdio.h>
#define DEBUG_PRINT(...)        printf(__VA_ARGS__)
#define ERROR_PRINT(...)        printf("[ERROR] " __VA_ARGS__)

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
    {   0, spvrefl_execmode_Invocations, 1, "Invocations"},
    {   1, spvrefl_execmode_SpacingEqual, 0, "SpacingEqual"},
    {   2, spvrefl_execmode_SpacingFractionalEven, 0, "SpacingFractionalEven"},
    {   3, spvrefl_execmode_SpacingFractionalOdd, 0, "SpacingFractionalOdd"},
    {   4, spvrefl_execmode_VertexOrderCw, 0, "VertexOrderCw"},
    {   5, spvrefl_execmode_VertexOrderCcw, 0, "VertexOrderCcw"},
    {   6, spvrefl_execmode_PixelCenterInteger, 0, "PixelCenterInteger"},
    {   7, spvrefl_execmode_OriginUpperLeft, 0, "OriginUpperLeft"},
    {   8, spvrefl_execmode_OriginLowerLeft, 0, "OriginLowerLeft"},
    {   9, spvrefl_execmode_EarlyFragmentTests, 0, "EarlyFragmentTests"},
    {  10, spvrefl_execmode_PointMode, 0, "PointMode"},
    {  11, spvrefl_execmode_Xfb, 0, "Xfb"},
    {  12, spvrefl_execmode_DepthReplacing, 0, "DepthReplacing"},
    {  14, spvrefl_execmode_DepthGreater, 0, "DepthGreater"},
    {  15, spvrefl_execmode_DepthLess, 0, "DepthLess"},
    {  16, spvrefl_execmode_DepthUnchanged, 0, "DepthUnchanged"},
    {  17, spvrefl_execmode_LocalSize, 3, "LocalSize"},
    {  18, spvrefl_execmode_LocalSizeHint, 3	, "LocalSizeHint"},
    {  19, spvrefl_execmode_InputPoints, 0, "InputPoints"},
    {  20, spvrefl_execmode_InputLines, 0, "InputLines"},
    {  21, spvrefl_execmode_InputLinesAdjacency, 0, "InputLinesAdjacency"},
    {  22, spvrefl_execmode_Triangles, 0, "Triangles"},
    {  23, spvrefl_execmode_InputTrianglesAdjacency, 0, "InputTrianglesAdjacency"},
    {  24, spvrefl_execmode_Quads, 0, "Quads"},
    {  25, spvrefl_execmode_Isolines, 0, "Isolines"},
    {  26, spvrefl_execmode_OutputVertices, 1, "OutputVertices"},
    {  27, spvrefl_execmode_OutputPoints, 0, "OutputPoints"},
    {  28, spvrefl_execmode_OutputLineStrip, 0, "OutputLineStrip"},
    {  29, spvrefl_execmode_OutputTriangleStrip, 0, "OutputTriangleStrip"},
    {  30, spvrefl_execmode_VecTypeHint, 1, "VecTypeHint"},
    {  31, spvrefl_execmode_ContractionOff, 0, "ContractionOff"},
    {  33, spvrefl_execmode_Initializer, 0, "Initializer"},
    {  34, spvrefl_execmode_Finalizer, 0, "Finalizer"},
    {  35, spvrefl_execmode_SubgroupSize, 1, "SubgroupSize"},
    {  36, spvrefl_execmode_SubgroupsPerWorkgroup, 1, "SubgroupsPerWorkgroup"},
    {  37, spvrefl_execmode_SubgroupsPerWorkgroupId, 1, "SubgroupsPerWorkgroupId"},
    {  38, spvrefl_execmode_LocalSizeId, 3, "LocalSizeId"},
    {  39, spvrefl_execmode_LocalSizeHintId, 3, "LocalSizeHintId"},
    {4446, spvrefl_execmode_PostDepthCoverage, 0, "PostDepthCoverage"},
    {4459, spvrefl_execmode_DenormPreserve, 1, "DenormPreserve"},
    {4460, spvrefl_execmode_DenormFlushToZero, 1, "DenormFlushToZero"},
    {4461, spvrefl_execmode_SignedZeroInfNanPreserve, 1, "SignedZeroInfNanPreserve"},
    {4462, spvrefl_execmode_RoundingModeRTE, 1, "RoundingModeRTE"},
    {4463, spvrefl_execmode_RoundingModeRTZ, 1, "RoundingModeRTZ"},
    {5027, spvrefl_execmode_StencilRefReplacingEXT, 0, "StencilRefReplacingEXT"},
    {5269, spvrefl_execmode_OutputLinesNV, 0, "OutputLinesNV"},
    {5270, spvrefl_execmode_OutputPrimitivesNV, 1, "OutputPrimitivesNV"},
    {5289, spvrefl_execmode_DerivativeGroupQuadsNV, 0, "DerivativeGroupQuadsNV"},
    {5290, spvrefl_execmode_DerivativeGroupLinearNV, 0, "DerivativeGroupLinearNV"},
    {5298, spvrefl_execmode_OutputTrianglesNV, 0, "OutputTrianglesNV"},
    {5366, spvrefl_execmode_PixelInterlockOrderedEXT, 0, "PixelInterlockOrderedEXT"},
    {5367, spvrefl_execmode_PixelInterlockUnorderedEXT, 0, "PixelInterlockUnorderedEXT"},
    {5368, spvrefl_execmode_SampleInterlockOrderedEXT, 0, "SampleInterlockOrderedEXT"},
    {5369, spvrefl_execmode_SampleInterlockUnorderedEXT, 0, "SampleInterlockUnorderedEXT"},
    {5370, spvrefl_execmode_ShadingRateInterlockOrderedEXT, 0, "ShadingRateInterlockOrderedEXT"},
    {5371, spvrefl_execmode_ShadingRateInterlockUnorderedEXT, 0, "ShadingRateInterlockUnorderedEXT"},
};

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
ispvr_stringtab_push (ispvr_stringtab_t * strtab, ispvr_input_t * input, uint16_t expected_words, unsigned * out_used_words) {
    char * ret = strtab->cur;
    unsigned used_words = 0;
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
        ERROR_PRINT("[SPVREFL INTERNAL ERROR] Expected %u words in the literal string '%s', but found %u.\n", expected_words, ret, used_words);
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

char const *
spvrefl_get_capability_name (spvrefl_capability_e cap) {
    if (cap >= 0 && cap < ispvr_capability_data_count)
        return ispvr_capability_data[cap].name_str;
    else
        return NULL;
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
    for (unsigned i = 0; i < sizeof(*info); ++i)
        *((char *)info + i) = 0;

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
    for (int i = 0; i < SPVREFL_OPT_MAX_STRUCT_COUNT; ++i) {
        structtab[i].count = 0;
        structtab[i].needed_count = 0;
        for (int j = 0; j < SPVREFL_OPT_MAX_STRUCT_MEMBER_COUNT; ++j)
            structtab[i].names[j] = NULL;
    }

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
        case 17: {  // OpCapability
            SPVREFL_ASSERT(2 == word_count);
            ispvr_input_advance_data(input);
            ispvr_capability_find_and_add_with_requisites(&info->capabilities, input->cur_word);
        } break;
        case 10: {  // OpExtension
            SPVREFL_ASSERT(2 <= word_count);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 1, NULL);
            info->extensions.needed_count += 1;
            if (info->extensions.count < SPVREFL_OPT_MAX_USED_EXTENSIONS)
                info->extensions.names[info->extensions.count++] = str;
        } break;
        case 11: {  // OpExtInstImport
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t id = ispvr_input_advance_data(input);
            char const * str = ispvr_stringtab_push(strtab, input, input->inst_word_count - 2, NULL);
            info->instruction_sets.needed_count += 1;
            if (info->instruction_sets.count < SPVREFL_OPT_MAX_USED_EXTENDED_INSTRUCTION_SET_IMPORT) {
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
            if (info->source_extensions.count < SPVREFL_OPT_MAX_USED_SOURCE_EXTENSIONS)
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
                struct_ptr->names[member_no] = str;
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
        case 71: {   // OpDecorate
            SPVREFL_ASSERT(3 <= word_count);
            uint32_t target_id = ispvr_input_advance_data(input);
            uint32_t decoration = ispvr_input_advance_data(input);
            for (unsigned i = 3; i < word_count; ++i)
                ispvr_input_advance_data(input);
            SPVREFL_ASSERT(target_id < info->id_upper_bound);
            DEBUG_PRINT("- (@%u) OpDecorate (%u words): #%u, %u\n", info->instruction_count, input->inst_word_count, target_id, decoration);
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

//#endif  // SPVREFL_IMPLEMENTATION
