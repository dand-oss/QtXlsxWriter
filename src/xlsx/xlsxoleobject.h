/****************************************************************************
** Copyright (c) 2015 AppSmiths, Inc.
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

#pragma once

#include "xlsxglobal.h"
#include "xlsxanchor.h"

#include <QString>
#include <QByteArray>

namespace QXlsx {

class OleObject
{
public:
    OleObject(const QString &fileName,
              const QString &suffix=QString(),
              const QString &progID=QString(),
              const QString &requires=QString(),
              const QString &shapeID=QString());

    void set(const QString &fileName,
             const QString &suffix=QString(),
             const QString &progID=QString(),
             const QString &requires=QString(),
             const QString &shapeID=QString());

    bool isIndexValid() const;
    int index() const;
    void setIndex(int idx);
    QByteArray hashKey() const;

    void setSuffix(const QString& suffix);
    QString suffix() const;

    void setContents(const QByteArray& bytes);
    QByteArray contents() const;

    void setFileName(const QString &name);
    QString fileName() const;

    void setProgID(const QString& id);
    QString progID() const;

    void setRequires(const QString& req);
    QString requires() const;

    void setShapeID(const QString& id);
    QString shapeID() const;

    void setMimeType(const QString& mime_type);
    QString mimeType() const;

    void setAnchor(const QSharedPointer<Anchor> anchor);
    QSharedPointer<Anchor> anchor() const;

    void setPrMediaFile(QSharedPointer<MediaFile> media);
    QSharedPointer<MediaFile> prMediaFile() const;

    bool isPrIndexValid() const;
    int prIndex() const;
    void setPrIndex(int idx);

private:
    QString m_fileName; //...
    QByteArray m_contents;
    QString m_suffix;
    QString m_progID; // program ID
    QString m_mimeType;
    QString m_requires;
    QString m_shapeID;

    int m_index;
    bool m_indexValid;
    int m_pr_index;
    bool m_pr_indexValid;
    QByteArray m_hashKey;
    QSharedPointer<Anchor> m_anchor;
    QSharedPointer<MediaFile> m_mediaFile;
};

} // namespace QXlsx
