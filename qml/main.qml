import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    id: root

    width: 1024
    height: 576

    menuBar: MenuBar {

        Menu {
            title: qsTr("Products") + translator.tr

            MenuItem {
                text: qsTr("Add") + translator.tr
            }
        }

        Menu {
            title: qsTr("Settings") + translator.tr

            MenuItem {
                text: qsTr("Language") + translator.tr
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

    StackView {
        id: stackView

        anchors.fill: parent

        initialItem: products
    }

    Connections {
        target: productsModel
        onError: console.log(error)
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