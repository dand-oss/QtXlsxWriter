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
#include "xlsxdrawinganchor.h"

#include <QPoint>
#include <QSize>
#include <QString>
#include <QSharedPointer>

class QXmlStreamReader;
class QXmlStreamWriter;

namespace QXlsx {

struct XlsxMarker;

class Q_XLSX_EXPORT Anchor
{
public:

    Anchor();
    Anchor(int from_row, int from_column, int from_rowOffset, int from_colOffset,
           int to_row, int to_column, int to_rowOffset, int to_colOffset);
    virtual ~Anchor();

    bool loadFromXml(QXmlStreamReader &reader);
    void saveToXml(QXmlStreamWriter &writer) const;

protected:
    XlsxMarker loadXmlMarker(QXmlStreamReader &reader, const QString &node);
    void saveXmlMarker(QXmlStreamWriter &writer, const XlsxMarker &marker, const QString &node) const;

    bool moveWithCells;
    XlsxMarker from_marker, to_marker;
};

} // namespace QXlsx
