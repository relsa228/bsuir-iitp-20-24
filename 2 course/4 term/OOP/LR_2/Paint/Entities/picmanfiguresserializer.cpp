#include "picmanfiguresserializer.h"

PicManFigureSerializer::PicManFigureSerializer()
{

}

bool PicManFigureSerializer::dump(DefaultPicManFigure* figure, QString filePath)
{
    QFile outFile(filePath);

    if(!outFile.open(QIODevice::WriteOnly))
        return false;

    QJsonObject serializeObj = figure->SerializeFigure();
    if(serializeObj.isEmpty())
        return false;
    QJsonDocument document = QJsonDocument(serializeObj);

    outFile.write(document.toJson());
    outFile.flush();
    outFile.close();

    return true;
}

DefaultPicManFigure* PicManFigureSerializer::load(QString filePath, PicManFigureFactory* factory)
{
    QFile inFile(filePath);

    if(!inFile.open(QIODevice::ReadOnly))
        return nullptr;

    QJsonDocument document = QJsonDocument().fromJson(inFile.readAll());
    QJsonObject jsonObj = document.object();

    DefaultPicManFigure* picManFigure = factory->createFigure(jsonObj.value("Type").toString());
    return picManFigure->DeserializeFigure(jsonObj);
}
