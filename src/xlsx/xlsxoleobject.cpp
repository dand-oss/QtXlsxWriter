/****************************************************************************
** Copyright (c) 2013-2014 Debao Zhang <hello@debao.me>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#include "xlsxoleobject.h"
#include <QCryptographicHash>

namespace QXlsx {

OleObject::OleObject(const QString &fileName,
                     const QString &suffix,
                     const QString &progID,
                     const QString &requires,
                     const QString &shapeID)
    : m_fileName(fileName)
    , m_suffix(suffix)
    , m_progID(progID)
    , m_requires(requires)
    , m_shapeID(shapeID)
    , m_index(0)
    , m_indexValid(false)
    , m_pr_index(0)
    , m_pr_indexValid(false)
{
    m_hashKey = QCryptographicHash::hash(m_contents, QCryptographicHash::Md5);
}

void OleObject::set(const QString &fileName,
                    const QString &suffix,
                    const QString &progID,
                    const QString &requires,
                    const QString &shapeID)
{
    m_fileName = fileName;
    m_suffix = suffix;
    m_progID = progID;
    m_requires = requires;
    m_shapeID = shapeID;
    m_hashKey = QCryptographicHash::hash(m_contents, QCryptographicHash::Md5);
    m_indexValid = false;
}

void OleObject::setFileName(const QString &name)
{
    m_fileName = name;
}

QString OleObject::fileName() const
{
    return m_fileName;
}

void OleObject::setProgID(const QString &id)
{
    m_progID = id;
}

QString OleObject::progID() const
{
    return m_progID;
}

void OleObject::setSuffix(const QString &suffix)
{
    m_suffix = suffix;
}

QString OleObject::suffix() const
{
    return m_suffix;
}

void OleObject::setContents(const QByteArray &bytes)
{
    m_contents = bytes;
}

QByteArray OleObject::contents() const
{
    return m_contents;
}

void OleObject::setRequires(const QString &req)
{
    m_progID = req;
}

QString OleObject::requires() const
{
    return m_requires;
}

void OleObject::setShapeID(const QString &id)
{
    m_shapeID = id;
}

QString OleObject::shapeID() const
{
    return m_shapeID;
}

void OleObject::setMimeType(const QString &mime_type)
{
    m_mimeType = mime_type;
}

QString OleObject::mimeType() const
{
    return m_mimeType;
}

void OleObject::setAnchor(const QSharedPointer<Anchor> anchor)
{
    m_anchor = anchor;
}

QSharedPointer<Anchor> OleObject::anchor() const
{
    return m_anchor;
}

void OleObject::setPrMediaFile(QSharedPointer<MediaFile> media)
{
    m_mediaFile = media;
}

QSharedPointer<MediaFile> OleObject::prMediaFile() const
{
    return m_mediaFile;
}

bool OleObject::isPrIndexValid() const
{
    return m_pr_indexValid;
}

int OleObject::prIndex() const
{
    return m_pr_index;
}

void OleObject::setPrIndex(int idx)
{
    m_pr_index = idx;
    m_pr_indexValid = true;
}

int OleObject::index() const
{
    return m_index;
}

bool OleObject::isIndexValid() const
{
    return m_indexValid;
}

void OleObject::setIndex(int idx)
{
    m_index = idx;
    m_indexValid = true;
}

QByteArray OleObject::hashKey() const
{
    return m_hashKey;
}

} // namespace QXlsx
