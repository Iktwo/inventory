import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    id: root

    objectName: "LanguageSelector"

    ListModel {
        id: languagesModel

        ListElement { name: "Español"; code: "SP"; iconSource: "mexico" }
        ListElement { name: "English"; code: "EN"; iconSource: "usa" }
    }

    GridView {
        id: view

        anchors.fill: parent
        model: languagesModel

        cellHeight: root.height / 3
        cellWidth: root.width / 3

        interactive: count > 3

        delegate: Item {
            height: view.cellHeight
            width: view.cellWidth

            Image {
                anchors.centerIn: parent

                source: "qrc:/translations/" + model.iconSource
            }

            Rectangle {
                anchors {
                    fill: nameLabel
                    margins: -10
                }

                color: translator.language === model.code ? "#566874" : "transparent"
            }

            Label {
                id: nameLabel

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                color: translator.language === model.code ? "white" : "black"

                text: model.name
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    translator.translate(model.code)
                    stackView.pop()
                }
            }
        }
    }
}
