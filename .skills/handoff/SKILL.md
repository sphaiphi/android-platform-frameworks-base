---
name: handoff
description: Serializes internal state and drops a structured context payload into a shared  file path for consumption by a target subagent.
---

# Skill: Subagent Context Handoff

## 1. Purpose
To handle seamless state and data transfers between independent runtime entities. This skill minimizes context window pollution during orchestrator dispatch by serializing execution history, extracted artifacts, and next-action targets into a decoupled intermediate state file.

## 2. Target Subagent
**[Specify Target Agent Name]** *(e.g., Android_NDK_Agent, Compiler_Verification_Agent)*

## 3. Trigger Conditions
Execute this skill when:
* A pipeline phase concludes and specialized processing is required by a distinct downstream entity.
* Local operational bounds are hit requiring fallback or handover to an explicit sub-agent.
* Complex code/data generated locally exceeds reasonable orchestrator message payload constraints.

## 4. Execution Steps
1. **Context Synthesis:** Aggregate original objectives, completed operations list, key extracted tokens/code-blocks, and targeted pending requirements.
2. **Deterministic Payload Generation:** Format synthesized data strictly matching the Schema defined in Section 5.
3. **Unique Path Generation:** Compute target string following the pattern: `${WORKSPACE_DIR:-./handoff}/handoff_${target_agent}_${timestamp_ms}_${uuid_short}.json`.
4. **I/O Execution & Flush:** Call `fs_write` to commit data to disk. Ensure file handle is closed and data is completely flushed to storage media.
5. **Dispatch:** Emit or invoke the orchestrator signal targeting the downstream agent, passing *only* the absolute path generated in Step 3.

## 5. Handoff Output Format (JSON Schema)
```json
{
  "$schema": "[http://json-schema.org/draft-07/schema#](http://json-schema.org/draft-07/schema#)",
  "type": "object",
  "required": ["source_agent", "target_agent", "execution_id", "original_goal", "completed_actions", "extracted_data", "target_assignment"],
  "properties": {
    "source_agent": { "type": "string" },
    "target_agent": { "type": "string" },
    "execution_id": { "type": "string", "description": "Unique UUID or run identifier" },
    "timestamp": { "type": "string", "format": "date-time" },
    "original_goal": { "type": "string" },
    "completed_actions": {
      "type": "array",
      "items": { "type": "string" }
    },
    "extracted_data": {
      "type": "object",
      "description": "State flags, source code buffers, variables, or environment configurations."
    },
    "target_assignment": { "type": "string", "description": "Explicit prompt instruction for what the receiving agent must do first." }
  }
}