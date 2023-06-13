// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PROFILER_CHROME_UNWINDER_ANDROID_V2_H_
#define BASE_PROFILER_CHROME_UNWINDER_ANDROID_V2_H_

#include <stdint.h>

#include "base/base_export.h"
#include "base/containers/span.h"
#include "base/profiler/register_context.h"
#include "third_party/abseil-cpp/absl/types/optional.h"

namespace base {

struct FunctionTableEntry;

enum class UnwindInstructionResult {
  kCompleted,           // Signals the end of unwind process.
  kInstructionPending,  // Continues to unwind next instruction.
  kAborted,             // Unable to unwind.
};

// Execute a single unwind instruction on the given thread_context, and moves
// `instruction` to point to next instruction right after the executed
// instruction.
//
// Arguments:
//   instruction: The pointer to the instruction to execute. This pointer will
//                be advanced by the size of the instruction executed after the
//                function call.
//   pc_was_updated: Set to true if the pc was updated by the instruction
//                   execution. Used to decide whether to copy lr to pc on
//                   COMPLETE.
//   thread_context: The thread_context the instruction operates on.
BASE_EXPORT UnwindInstructionResult
ExecuteUnwindInstruction(const uint8_t*& instruction,
                         bool& pc_was_updated,
                         RegisterContext* thread_context);

// Represents an index that can locate a specific entry on function offset
// table.
struct FunctionOffsetTableIndex {
  // Number of 2-byte instructions between the instruction of interest and
  // function_start_address.
  int instruction_offset_from_function_start;
  // The byte index of the first offset for the function in the function
  // offset table.
  uint16_t function_offset_table_byte_index;
};

// Given `FunctionOffsetTableIndex`, finds the instruction to execute on unwind
// instruction table.
//
// Arguments:
//  unwind_instruction_table: See
//    `ChromeUnwindInfoAndroid::unwind_instruction_table` for details.
//  function_offset_table: See
//    `ChromeUnwindInfoAndroid::function_offset_table` for details.
//  index: The index used to locate an entry in `function_offset_table`.
BASE_EXPORT const uint8_t*
GetFirstUnwindInstructionFromFunctionOffsetTableIndex(
    const uint8_t* unwind_instruction_table,
    const uint8_t* function_offset_table,
    const FunctionOffsetTableIndex& index);

// Given an instruction_offset_from_text_section_start, finds the corresponding
// `FunctionOffsetTableIndex`.
//
// Arguments:
//  page_start_instructions: A list of page_numbers. See
//    `ChromeUnwindInfoAndroid::page_table` for details.
//  function_offsets_table_indices: A list of `FunctionTableEntry`. See
//    `ChromeUnwindInfoAndroid::function_table` for details.
//  instruction_offset_from_text_section_start: The distance in bytes between
//    the instruction of interest and text section start.
BASE_EXPORT const absl::optional<FunctionOffsetTableIndex>
GetFunctionTableIndexFromInstructionOffset(
    span<const uint32_t> page_start_instructions,
    span<const FunctionTableEntry> function_offset_table_indices,
    uint32_t instruction_offset_from_text_section_start);

}  // namespace base

#endif  // BASE_PROFILER_CHROME_UNWINDER_ANDROID_V2_H_
