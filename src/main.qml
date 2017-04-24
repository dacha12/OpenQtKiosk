import QtQml 2.0
import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.1
//import QtQuick.VirtualKeyboard.Settings 2.0
import QtQuick.Window 2.2
import QtWebEngine 1.3


Window {
    id: appContainer
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

    InputPanel {
        id: inputPanel
        z: 99
        y: appContainer.height
        anchors.left: parent.left
        anchors.right: parent.right
        visible: keyboardVisible
        states: State {
            name: "visible"
            /*  The visibility of the InputPanel can be bound to the Qt.inputMethod.visible property,
                but then the handwriting input panel and the keyboard input panel can be visible
                at the same time. Here the visibility is bound to InputPanel.active property instead,
                which allows the handwriting panel to control the visibility when necessary.
            */
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: appContainer.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
        /*Component.onCompleted: {
            console.log("locales available: " + VirtualKeyboardSettings.availableLocales)
            console.log("Locale before changing it: " + VirtualKeyboardSettings.locale)
            VirtualKeyboardSettings.locale = "fi_FI";
            console.log("Locale after changing it: " + VirtualKeyboardSettings.locale)
        }*/

     }

}


