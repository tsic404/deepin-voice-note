/*
* Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
*
* Author:     zhangteng <zhangteng@uniontech.com>
* Maintainer: zhangteng <zhangteng@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ut_vnoteitemoper.h"
#include "vnotedbmanager.h"
#include "vnotedatamanager.h"
#include "vnotefolderoper.h"
#include "vnoteforlder.h"
#include "vnoteitemoper.h"
#include "vnoteitem.h"

UT_VNoteItemOper::UT_VNoteItemOper()
{
}

void UT_VNoteItemOper::SetUp()
{
    VNOTE_ALL_NOTES_MAP *notes = VNoteDataManager::instance()->getAllNotesInFolder();
    if (notes && !notes->notes.isEmpty()) {
        VNOTE_ITEMS_MAP *tmp = notes->notes.first();
        if (tmp && !tmp->folderNotes.isEmpty()) {
            m_note = tmp->folderNotes.first();
        }
    }

    m_vnoteitemoper = new VNoteItemOper(m_note);
}

void UT_VNoteItemOper::TearDown()
{
    delete m_vnoteitemoper;
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_loadAllVNotes_001)
{
    VNOTE_ALL_NOTES_MAP *notes = m_vnoteitemoper->loadAllVNotes();
    EXPECT_FALSE(nullptr == notes);
    delete notes;
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_modifyNoteTitle_001)
{
    EXPECT_FALSE(m_vnoteitemoper->modifyNoteTitle("test"));
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_updateNote_001)
{
    EXPECT_FALSE(m_vnoteitemoper->updateNote());
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_addNote_001)
{
    VNoteItem tmpNote;
    tmpNote.folderId = m_note->folderId;
    tmpNote.noteType = VNoteItem::VNT_Text;
    tmpNote.noteTitle = m_vnoteitemoper->getDefaultNoteName(tmpNote.folderId);
    VNoteBlock *ptrBlock1 = tmpNote.newBlock(VNoteBlock::Text);
    tmpNote.addBlock(ptrBlock1);
    EXPECT_TRUE(m_vnoteitemoper->addNote(tmpNote) == nullptr);
    VNoteItemOper op(&tmpNote);
    EXPECT_FALSE(op.deleteNote());
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_getDefaultVoiceName_001)
{
    m_vnoteitemoper->getDefaultVoiceName();
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_updateTop_001)
{
    EXPECT_FALSE(m_vnoteitemoper->updateTop(!m_note->isTop));
    EXPECT_FALSE(m_vnoteitemoper->updateTop(!m_note->isTop));
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_updateFolderId_001)
{
    EXPECT_FALSE(m_vnoteitemoper->updateFolderId(m_note));
}

TEST_F(UT_VNoteItemOper, UT_VNoteItemOper_getNote_001)
{
    EXPECT_TRUE(m_vnoteitemoper->getNote(m_note->folderId, m_note->noteId));
}
