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

#include "xlsxanchor.h"
#include "xlsxutility_p.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QBuffer>
#include <QDir>
#include <QFile>
#include <QFileInfo>

namespace QXlsx {

/*
     The vertices that define the position of a graphical object
     within the worksheet in pixels.

             +------------+------------+
             |     A      |      B     |
       +-----+------------+------------+
       |     |(x1,y1)     |            |
       |  1  |(from)._____|______      |
       |     |    |              |     |
       |     |    |              |     |
       +-----+----|    OBJECT    |-----+
       |     |    |              |     |
       |  2  |    |______________.     |
       |     |            |        (to)|
       |     |            |     (x2,y2)|
       +---- +------------+------------+

     Example of an object that covers some of the area from cell A1 to  B2.

     Based on the width and height of the object we need to calculate 8 vars:

         col_start, row_start, col_end, row_end, x1, y1, x2, y2.

     We also calculate the absolute x and y position of the top left vertex of
     the object. This is required for images.

     The width and height of the cells that the object occupies can be
     variable and have to be taken into account.
*/

//anchor

Anchor::Anchor() :
    from_marker(0, 0, 0, 0)
  , to_marker(0, 0, 0, 0)
{

}

Anchor::Anchor(int from_row, int from_column, int from_rowOffset, int from_colOffset,
               int to_row, int to_column, int to_rowOffset, int to_colOffset) :
    from_marker(from_row, from_column, from_rowOffset, from_colOffset)
  , to_marker(to_row, to_column, to_rowOffset, to_colOffset)
{

}

Anchor::~Anchor()
{}

XlsxMarker Anchor::loadXmlMarker(QXmlStreamReader &reader, const QString &node)
{
    Q_ASSERT(reader.name() == node);

    int col = 0;
    int colOffset = 0;
    int row = 0;
    int rowOffset = 0;
    while (!reader.atEnd()) {
        reader.readNextStartElement();
        if (reader.tokenType() == QXmlStreamReader::StartElement) {
            if (reader.name() == QLatin1String("col")) {
                col = reader.readElementText().toInt();
            } else if (reader.name() == QLatin1String("colOff")) {
                colOffset = reader.readElementText().toInt();
            } else if (reader.name() == QLatin1String("row")) {
                row = reader.readElementText().toInt();
            } else if (reader.name() == QLatin1String("rowOff")) {
                rowOffset = reader.readElementText().toInt();
            }
        } else if (reader.tokenType() == QXmlStreamReader::EndElement
                   && reader.name() == node) {
            break;
        }
    }

    return XlsxMarker(row, col, rowOffset, colOffset);
}

void Anchor::saveXmlMarker(QXmlStreamWriter &writer, const XlsxMarker &marker, const QString &node) const
{
    writer.writeStartElement(node); //xdr:from or xdr:to
    writer.writeTextElement(QStringLiteral("xdr:col"), QString::number(marker.col()));
    writer.writeTextElement(QStringLiteral("xdr:colOff"), QString::number(marker.colOff()));
    writer.writeTextElement(QStringLiteral("xdr:row"), QString::number(marker.row()));
    writer.writeTextElement(QStringLiteral("xdr:rowOff"), QString::number(marker.rowOff()));
    writer.writeEndElement();
}

void Anchor::saveToXml(QXmlStreamWriter &writer) const
{
    writer.writeStartElement(QStringLiteral("anchor"));
    saveXmlMarker(writer, from_marker, QStringLiteral("from"));
    saveXmlMarker(writer, to_marker, QStringLiteral("to"));
    writer.writeEndElement(); //anchor
}

bool Anchor::loadFromXml(QXmlStreamReader &reader)
{
    Q_ASSERT(reader.name() == QLatin1String("anchor"));

    while (!reader.atEnd() && !(reader.name() == QLatin1String("anchor")
            && reader.tokenType() == QXmlStreamReader::EndElement)) {
        reader.readNextStartElement();
        if (reader.tokenType() == QXmlStreamReader::StartElement) {
            if (reader.name() == QLatin1String("from")) {
                from_marker = loadXmlMarker(reader, QLatin1String("from"));
            } else if (reader.name() == QLatin1String("to")) {
                to_marker = loadXmlMarker(reader, QLatin1String("to"));
            }
        }
    }

    return true;
}

} // namespace QXlsx
