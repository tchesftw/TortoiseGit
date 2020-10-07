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
#include "stdafx.h"
#include "FileTextLinesFromScintilla.h"

void CFileTextLinesFromScintilla::AddLine(const char* lineWithEOL, int style)
{
	size_t size = std::strlen(lineWithEOL);
	// Regardless of locales, a "\ No newline at end of file" will always begin with "\ " and 10 is a sane minimum length to look for
	bool isNoNewlineComment = false;
	if (size >= 10 && std::strncmp(lineWithEOL, "\\ ", 2) == 0)
		isNoNewlineComment = true;
	m_linevec.emplace_back(lineWithEOL, size, style, isNoNewlineComment);
}

void CFileTextLinesFromScintilla::SetFirstLineNumberSelected(int line)
{
	m_firstLineSelected = line;
}

void CFileTextLinesFromScintilla::SetLastLineNumberSelected(int line)
{
	m_lastLineSelected = line;
}

int CFileTextLinesFromScintilla::GetFirstLineNumberSelected() const
{
	return m_firstLineSelected;
}

int CFileTextLinesFromScintilla::GetLastLineNumberSelected() const
{
	return m_lastLineSelected;
}

// Includes EOL characters of all lines
std::unique_ptr<char[]> CFileTextLinesFromScintilla::GetFullTextOfSelectedLines() const
{
	return GetFullTextOfLineRange(GetFirstLineNumberSelected(), GetLastLineNumberSelected());
}

// Includes EOL characters of all lines
std::unique_ptr<char[]> CFileTextLinesFromScintilla::GetFullTextOfLineRange(int startline, int endline) const
{
	if (endline < startline)
		return nullptr;
	int size = 0;
	for (int i = startline; i <= endline; i++)
		size += m_linevec.at(i).size;
	std::unique_ptr<char[]> ret = std::make_unique<char[]>(size + 1);
	for (int i = startline; i <= endline; i++)
		strcat_s(ret.get(), size + 1, m_linevec.at(i).sLine.get());
	return ret;
}

// Assumes a whole line is styled the same
int CFileTextLinesFromScintilla::GetStyleAtLine(int line) const
{
	return m_linevec.at(line).style;
}

bool CFileTextLinesFromScintilla::IsNoNewlineComment(int line) const
{
	return m_linevec.at(line).isNoNewlineComment;
}

// Includes EOL characters
std::unique_ptr<char[]> CFileTextLinesFromScintilla::GetFullLineByLineNumber(int line) const
{
	int size = m_linevec.at(line).size + 1;
	std::unique_ptr<char[]> ret = std::make_unique<char[]>(size);
	strcpy_s(ret.get(), size, m_linevec.at(line).sLine.get());
	return ret;
}

int CFileTextLinesFromScintilla::GetLastDocumentLine() const
{
	return m_linevec.size() - 1;
}

int CFileTextLinesFromScintilla::GetDocumentLength() const
{
	int linesCount = m_linevec.size();
	int documentLength = 0;
	for (int i = 0; i < linesCount; i++)
		documentLength += m_linevec.at(i).size;
	return documentLength;
}
