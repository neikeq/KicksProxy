#include "argumentsparser.h"

#include <QCommandLineOption>
#include <QCoreApplication>
#include <QDebug>

ArgumentsParser::ArgumentsParser()
{
    parser.addOption(QCommandLineOption(QStringList() << "k" << "kill"));
}

void ArgumentsParser::parseArguments(const QStringList &arguments)
{
    if (!parser.parse(arguments)) {
        qDebug() << parser.errorText();
    }

    if (parser.isSet("kill")) {
        qDebug() << "Received kill argument.";
        QCoreApplication::exit();
    }
}
