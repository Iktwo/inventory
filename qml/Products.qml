import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    id: root

    objectName: "Main"

    /*Flow {
        id: flow

        TextField {
            id: nameField
            placeholderText: qsTr("Product name") + translator.tr
        }

        Button {
            text: qsTr("Add") + translator.tr
            onClicked: {
                if (nameField.text != "")
                    productsModel.addProduct(nameField.text)
            }
        }

        Button {
            text: qsTr("Remove") + translator.tr
            onClicked: {
                if (productsModel.itemAt(listView.currentIndex)) {
                    productsModel.removeProduct(productsModel.itemAt(listView.currentIndex).id)
                } else {
                    console.log("ERROR: item does not exist")
                }
            }
        }

        Button {
            text: qsTr("Update") + translator.tr
        }
    }*/

    RowLayout {
        id: layout

        anchors.fill: parent

        ListView {
            id: listView

            Layout.minimumWidth: root.width / 3
            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true

            highlight: Rectangle {
                width: 200; height: 50
                color: "#FFFF88"
                y: listView.currentItem.y
            }

            onCurrentItemChanged: productDetails.dataObject = listView.currentItem.modelData

            highlightFollowsCurrentItem: false
            model: productsModel

            delegate: Label {
                property variant modelData: model
                width: 200
                height: 50
                text: model.id + " - " + model.name + " - " + model.quantity

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        //model.name = "XXXX"
                        //productDetails.dataObject = model
                        listView.currentIndex = index
                    }
                }
            }
        }

        ProductDetails {
            id: productDetails

            Layout.minimumWidth: root.width / 2
            Layout.fillHeight: true
        }
    }
}
