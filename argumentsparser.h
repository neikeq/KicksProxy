#ifndef ARGUMENTSPARSER_H
#define ARGUMENTSPARSER_H

#include <QCommandLineParser>

class ArgumentsParser
{
public:
    void parseArguments(const QStringList &arguments);

    static ArgumentsParser& instance()
    {
        static ArgumentsParser instance;
        return instance;
    }

private:
    ArgumentsParser();

    // To avoid getting copies of this singleton
    ArgumentsParser(ArgumentsParser const&) = delete;
    void operator=(ArgumentsParser const&) = delete;

    QCommandLineParser parser;
};

#endif // ARGUMENTSPARSER_H
