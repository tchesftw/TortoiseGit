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

struct CFileTextLineFromScintilla
{
	CFileTextLineFromScintilla() {}

	CFileTextLineFromScintilla(const char* line, int size, int style, bool isNoNewlineComment)
	{
		sLine = std::make_unique<char[]>(size + 1);
		strcpy_s(sLine.get(), size + 1, line);
		this->size = size;
		this->style = style;
		this->isNoNewlineComment = isNoNewlineComment;
	}

	std::unique_ptr<char[]> sLine; // Includes EOL, null-terminated
	int size; // In bytes, without terminating null
	int style; // Style of the first character, as was given by Scintilla's lexer (assumes the whole line is styled the same)
	bool isNoNewlineComment; // Does this line look like a "\ No newline at end of file"?
};

// Stores a copy of a patch loaded in Patch View Dialog, as a vector of lines (which also stores the style of each line).
// Also stores information about the selection made by the user. Handles line and style retrieval.
// Intended usage:
// When the user invokes the partial staging/unstaging functionality in the Patch View Dialog, it creates an instance
// of this class, calls AddLine for each line in the patch, calls SetFirstLineNumberSelected and SetLastLineNumberSelected,
// then pass the instance to StagingOperations, which will handle the staging/unstaging operations.
class CFileTextLinesFromScintilla
{
private:
	std::vector<CFileTextLineFromScintilla> m_linevec;
	int m_firstLineSelected;
	int m_lastLineSelected;

public:
	void AddLine(const char* lineWithEOL, int style);
	void SetFirstLineNumberSelected(int line);
	void SetLastLineNumberSelected(int line);

	int GetFirstLineNumberSelected() const;
	int GetLastLineNumberSelected() const;
	std::unique_ptr<char[]> GetFullLineByLineNumber(int line) const;
	std::unique_ptr<char[]> GetFullTextOfSelectedLines() const;
	std::unique_ptr<char[]> GetFullTextOfLineRange(int startline, int endline) const;
	int GetLastDocumentLine() const;
	int GetStyleAtLine(int line) const;
	bool IsNoNewlineComment(int line) const;
	int GetDocumentLength() const;
};
