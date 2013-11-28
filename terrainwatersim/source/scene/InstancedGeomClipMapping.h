#pragma once

class InstancedGeomClipMapping
{
public:
  InstancedGeomClipMapping(float maxGridSize, float minPatchSizeWorld);
  ~InstancedGeomClipMapping();

  void UpdateInstanceData(const ezVec3& cameraPosition);
  void DrawGeometry();

private:

  float m_maxGridSize;
  float m_minPatchSizeWorld;
  ezUInt32 m_maxNumRenderedPatchInstances;

  static const ezUInt32 m_ringThinkness = 8;
  static const ezUInt32 m_numRings = 6;

  // Contains immutable relative patch positions.
  gl::BufferId m_patchVertexBuffer;

  enum class PatchType : ezUInt32
  {
    FULL,
    STITCH1,
    STITCH2,

    NUM_TYPES
  };

  gl::IndexBufferId m_patchIndexBuffer[(ezUInt32)PatchType::NUM_TYPES];
  gl::BufferId m_patchInstanceBuffer[(ezUInt32)PatchType::NUM_TYPES];
  ezUInt32 m_maxPatchInstances[(ezUInt32)PatchType::NUM_TYPES];
  gl::VertexArrayObjectId m_patchVertexArray[(ezUInt32)PatchType::NUM_TYPES];

  struct PatchInstanceData
  {
    ezVec2 worldPosition;
    float worldScale;
    ezUInt32 rotationType;
  };

  // Serves as CPU buffer for instance data. The element counter will be used to determine how many instances are active at the moment.
  ezDynamicArray<PatchInstanceData> m_currentInstanceData[(ezUInt32)PatchType::NUM_TYPES];
};
