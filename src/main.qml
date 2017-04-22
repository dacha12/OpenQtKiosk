import QtQml 2.0
import QtQuick 2.0
import QtQuick.Window 2.2
import QtWebEngine 1.3

Window {
    width: 1024
    height: 750
    visible: true
    visibility: "FullScreen"

    WebEngineView {
        id:webView
        objectName: "webView"
        anchors.fill: parent
        url: initialUrl
    }

}


