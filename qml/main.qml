import QtQuick 2.2
import QtQuick.Controls 1.1
import Notifications 1.0

ApplicationWindow {
    id: applicationWindow

    function openPage(page) {
        if (stackView.currentItem !== null
                && ((stackView.currentItem.__type !== undefined
                     && stackView.currentItem.__type === page)
                    || stackView.loadedPages.indexOf(page) !== -1)) {
            console.log("Trying to open a page that is already opened")
        } else {
            stackView.push(Qt.resolvedUrl(".") + "/pages/" + page + ".qml")
        }
    }

    function goToMainPage() {
        stackView.pop(Qt.resolvedUrl(".") + "/pages/Products.qml")
    }

    width: 1024
    height: 576
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Products") + translator.tr

            MenuItem {
                text: qsTr("&Add") + translator.tr
                shortcut: "ctrl+a"
                onTriggered: openPage("AddProduct")
            }
        }

        Menu {
            title: qsTr("&Settings") + translator.tr

            MenuItem {
                text: qsTr("&Language") + translator.tr
                onTriggered: openPage("LanguageSelector")
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

        property var loadedPages: []

        anchors {
            top: notificationBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        focus: true

        onCurrentItemChanged: {
            if (currentItem === null)
                return

            var pages = loadedPages

            if (depth > loadedPages.length)
                pages.push(currentItem.__type)
            else if (depth < loadedPages.length)
                pages.pop()

            loadedPages = pages
        }

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

    Component.onCompleted: openPage("Products")
}
