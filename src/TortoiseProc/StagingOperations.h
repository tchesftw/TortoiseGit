// TortoiseGit - a Windows shell extension for easy version control

// Copyright (C) 2016, 2019-2020 - TortoiseGit
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
#define STAGING_TYPE_STAGE_LINES 0
#define STAGING_TYPE_STAGE_HUNKS 1
#define STAGING_TYPE_UNSTAGE_LINES 2
#define STAGING_TYPE_UNSTAGE_HUNKS 3

class StagingOperations
{
public:
	StagingOperations(const CDiffLinesForStaging* lines)
	{
		m_lines = lines;
	}
	std::unique_ptr<char[]> CreatePatchBufferToStageOrUnstageSelectedHunks() const;
	std::unique_ptr<char[]> CreatePatchBufferToStageOrUnstageSelectedLines(int stagingType) const;

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
	std::unique_ptr<char[]> ChangeOldAndNewLinesCount(const std::unique_ptr<char[]>* strHunkStart, int oldCount, int newCount) const;

private:
	bool ParseHunkOnEitherSelectionBoundary(std::unique_ptr<char[]>* hunkWithoutStartLine, int hunkWithoutStartLineLen,
											int hunkStartLine, int hunkLastLine,
											int firstLineSelected, int lastLineSelected,
											int* oldCount, int* newCount, int stagingType) const;
};
