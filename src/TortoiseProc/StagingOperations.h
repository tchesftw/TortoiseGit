﻿// TortoiseGit - a Windows shell extension for easy version control

// Copyright (C) 2016, 2019-2021 - TortoiseGit
// Copyright (C) 2007, 2009-2013, 2020 - TortoiseSVN

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#pragma once
#include "stdafx.h"
#include "DiffLinesForStaging.h"

enum class StagingType
{
	StageLines,
	StageHunks,
	UnstageLines,
	UnstageHunks
};

class StagingOperations
{
public:
	StagingOperations(const CDiffLinesForStaging* lines)
	{
		m_lines = lines;
	}
	std::unique_ptr<char[]> CreatePatchBufferToStageOrUnstageSelectedHunks() const;
	std::unique_ptr<char[]> CreatePatchBufferToStageOrUnstageSelectedLines(StagingType stagingType) const;
	static CString WritePatchBufferToTemporaryFile(const char* data);

private:
	const CDiffLinesForStaging* m_lines;
	bool IsWithinFileHeader(int line) const;
	int FindHunkStartBackwardsFrom(int line, int topBoundaryLine) const;
	int FindHunkStartForwardsFrom(int line, int bottomBoundaryLine) const;
	int FindHunkEndForwardsFrom(int line, int topBoundaryLine) const;
	int FindHunkEndGivenHunkStartAndCounts(int hunkStart, int oldCount, int newCount) const;
	std::unique_ptr<char[]> FindFileHeaderBackwardsFrom(int line) const;
#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
public:
#endif
	std::unique_ptr<char[]> ChangeOldAndNewLinesCount(const char* strHunkStart, int oldCount, int newCount) const;

private:
	bool ParseHunkOnEitherSelectionBoundary(char* hunkWithoutStartLine, int hunkWithoutStartLineLen,
											int hunkStartLine, int hunkLastLine,
											int firstLineSelected, int lastLineSelected,
											int* oldCount, int* newCount, StagingType stagingType) const;
};
