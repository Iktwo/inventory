import QtQuick 2.2
import QtQuick.Controls 1.1
import Notifications 1.0

ApplicationWindow {
    id: root

    width: 1024
    height: 576
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Products") + translator.tr

            MenuItem {
                text: qsTr("&Add") + translator.tr
                shortcut: "ctrl+a";
                onTriggered: {
                    productsModel.addProduct("");
                }
            }
        }

        Menu {
            title: qsTr("&Settings") + translator.tr

            MenuItem {
                text: qsTr("&Language") + translator.tr
                onTriggered: {
                    if (stackView.currentItem.objectName !== "LanguageSelector")
                        stackView.push(languages)
                }
            }
        }
    }

    statusBar: StatusBar {
        Keys.onReleased: {
            if (event.key === Qt.Key_Back) {
                if (stackView.depth > 1) {
                    stackView.pop();
                    event.accepted = true;
                } else {
                    /// TODO: Show message letting the user now that if there's a second press application will exit
                    Qt.quit();
                }
            }
        }

        Label {
            text: qsTr("Products") + translator.tr + ": " + productsModel.count
        }
    }

    Notifications {
        id: notifications
    }

    StackView {
        id: stackView

        anchors {
            top: notificationBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        initialItem: products

        Behavior on y { NumberAnimation { easing.type: Easing.InOutCubic } }
    }

    NotificationBar {
        id: notificationBar

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Connections {
        target: productsModel
        onShowMessage: notificationBar.showMessage(message, type, duration)
    }

    Component {
        id: products

        Products { }
    }

    Component {
        id: languages

        LanguageSelector { }
    }
}
