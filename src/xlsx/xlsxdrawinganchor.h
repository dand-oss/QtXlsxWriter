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

#ifndef QXLSX_XLSXDRAWINGANCHOR_P_H
#define QXLSX_XLSXDRAWINGANCHOR_P_H

#include "xlsxglobal.h"

#include <QPoint>
#include <QSize>
#include <QString>
#include <QSharedPointer>

class QXmlStreamReader;
class QXmlStreamWriter;

namespace QXlsx {

class Drawing;
class MediaFile;
class Chart;

//Helper classes
struct XlsxMarker
{
    XlsxMarker() = default ;
    ~XlsxMarker() = default ;

    explicit XlsxMarker(int row, int column, int rowOffset, int colOffset)
        :cell(QPoint(row, column))
        , offset(rowOffset, colOffset)
    {
    }

    int row() const { return cell.x(); }
    int col() const { return cell.y(); }
    int rowOff() const { return offset.width(); }
    int colOff() const { return offset.height(); }

    QPoint cell;
    QSize offset;
};

//Shape
struct XlsxShape
{
    XlsxShape() = default;
    ~XlsxShape() = default;

    explicit XlsxShape(int _id, QString _name)
        : id(_id)
        , name(_name)
    {}

    int id;
    QString name;
};


class DrawingAnchor
{
public:
    enum ObjectType { GraphicFrame, Shape, GroupShape, ConnectionShape, Picture, Unknown };

    DrawingAnchor() = delete ;
    virtual ~DrawingAnchor();

    explicit DrawingAnchor(ObjectType objectType);
    explicit DrawingAnchor(Drawing *drawing, ObjectType objectType);
    void setObjectFile(
        const QString &filename,
        const QString &mimeType,
        const ObjectType objType);
    void setObjectPicture(const QImage &img);
    void setObjectGraphicFrame(QSharedPointer<Chart> chart);
    QSharedPointer<MediaFile> picture() { return m_pictureFile; }

    virtual bool loadFromXml(QXmlStreamReader &reader) = 0;
    virtual void saveToXml(QXmlStreamWriter &writer) const = 0;

    XlsxShape shape() const;

protected:
    QPoint loadXmlPos(QXmlStreamReader &reader);
    QSize loadXmlExt(QXmlStreamReader &reader);
    XlsxMarker loadXmlMarker(QXmlStreamReader &reader, const QString &node);
    void loadXmlObject(QXmlStreamReader &reader);
    void loadXmlObjectShape(QXmlStreamReader &reader);
    void loadXmlObjectGroupShape(QXmlStreamReader &reader);
    void loadXmlObjectGraphicFrame(QXmlStreamReader &reader);
    void loadXmlObjectConnectionShape(QXmlStreamReader &reader);
    void loadXmlObjectPicture(QXmlStreamReader &reader);

    void saveXmlPos(QXmlStreamWriter &writer, const QPoint &pos) const;
    void saveXmlExt(QXmlStreamWriter &writer, const QSize &ext) const;
    void saveXmlMarker(QXmlStreamWriter &writer, const XlsxMarker &marker,
                       const QString &node) const;
    void saveXmlObject(QXmlStreamWriter &writer) const;
    void saveXmlObjectShape(QXmlStreamWriter &writer) const;
    void saveXmlObjectGroupShape(QXmlStreamWriter &writer) const;
    void saveXmlObjectGraphicFrame(QXmlStreamWriter &writer) const;
    void saveXmlObjectConnectionShape(QXmlStreamWriter &writer) const;
    void saveXmlObjectPicture(QXmlStreamWriter &writer) const;

    Drawing *m_drawing {nullptr};
    ObjectType m_objectType;
    QSharedPointer<MediaFile> m_pictureFile;
    QSharedPointer<Chart> m_chartFile;
    XlsxShape m_shape;

    int m_id {-1};
};

class DrawingAbsoluteAnchor : public DrawingAnchor
{
public:
    ~DrawingAbsoluteAnchor() override = default;

    explicit DrawingAbsoluteAnchor(Drawing *drawing, ObjectType objectType=Unknown);

    QPoint pos;
    QSize ext;

    bool loadFromXml(QXmlStreamReader &reader);
    void saveToXml(QXmlStreamWriter &writer) const;
};

class DrawingOneCellAnchor : public DrawingAnchor
{
public:
    ~DrawingOneCellAnchor() override = default ;
    explicit DrawingOneCellAnchor(Drawing *drawing, ObjectType objectType=Unknown);

    XlsxMarker from;
    QSize ext;

    bool loadFromXml(QXmlStreamReader &reader);
    void saveToXml(QXmlStreamWriter &writer) const;
};

class DrawingTwoCellAnchor : public DrawingAnchor
{
public:
    ~DrawingTwoCellAnchor() override = default;

    explicit DrawingTwoCellAnchor(Drawing *drawing, ObjectType objectType=Unknown);

    XlsxMarker from;
    XlsxMarker to;

    bool loadFromXml(QXmlStreamReader &reader);
    void saveToXml(QXmlStreamWriter &writer) const;
};

} // namespace QXlsx

#endif // QXLSX_XLSXDRAWINGANCHOR_P_H
