
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore/QUrl>
#include <QDebug>
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QQmlContext>
#include <qtwebengineglobal.h>

int main(int argc, char *argv[])
{

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qputenv("QML_DISABLE_DISK_CACHE", QByteArray("1"));

    QGuiApplication app(argc, argv);
    QtWebEngine::initialize();

    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    //Options:
    QCommandLineOption keyboardOption({{"k", "keyboard"}, "Activate virtual keyboard."});
    QCommandLineOption cacheOption({{"c", "cache"}, "Enable cache."});
    QCommandLineParser parser;

    parser.setApplicationDescription(QGuiApplication::applicationDisplayName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(keyboardOption);
    parser.addOption(cacheOption);
    parser.addPositionalArgument("source","url or filename");

    QStringList arguments = app.arguments();

#ifdef Q_OS_WINRT
    arguments.removeAt(1); // The launcher always passes in the -ServerName parameter, breaking the command line parser
#endif

    parser.process(arguments);

    QString initialUrl = parser.positionalArguments().isEmpty() ? QStringLiteral("pages/index.html") : parser.positionalArguments().first();
    bool keyboard = parser.isSet(keyboardOption) ? true : false;
    if(parser.isSet(cacheOption))qputenv("QML_DISABLE_DISK_CACHE", QByteArray("0"));

    QQmlApplicationEngine engine;

    bool isEmbedded = false;
#ifdef QTWEBENGINE_RECIPE_BROWSER_EMBEDDED
    isEmbedded = true;
#endif

    //Pass variable to the qml:
    engine.rootContext()->setContextProperty(QStringLiteral("isEmbedded"), isEmbedded);
    engine.rootContext()->setContextProperty(QStringLiteral("initialUrl"), initialUrl);
    engine.rootContext()->setContextProperty(QStringLiteral("keyboardVisible"), keyboard);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
