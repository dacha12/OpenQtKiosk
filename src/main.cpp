
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore/QUrl>
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QQmlContext>
#include <qtwebengineglobal.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtWebEngine::initialize();

    QCommandLineParser parser;
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    parser.setApplicationDescription(QGuiApplication::applicationDisplayName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", "The initial URL to open.");
    QStringList arguments = app.arguments();
#ifdef Q_OS_WINRT
    arguments.removeAt(1); // The launcher always passes in the -ServerName parameter, breaking the command line parser
#endif
    parser.process(arguments);
    const QString initialUrl = parser.positionalArguments().isEmpty() ? QStringLiteral("pages/index.html") : parser.positionalArguments().first();


    QQmlApplicationEngine engine;

    bool isEmbedded = false;
#ifdef QTWEBENGINE_RECIPE_BROWSER_EMBEDDED
    isEmbedded = true;
#endif

    engine.rootContext()->setContextProperty(QStringLiteral("isEmbedded"), isEmbedded);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQmlContext *context = engine.rootContext();
    context->setContextProperty(QStringLiteral("initialUrl"), initialUrl);


    return app.exec();
}
