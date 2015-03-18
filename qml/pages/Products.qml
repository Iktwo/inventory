import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import components 2.0
import "products"

Page {
    id: root

    objectName: "Main"
    __type: "Products"

    RowLayout {
        id: layout

        anchors {
            fill: parent
            margins: 10
        }

        ListView {
            id: listView

            Layout.minimumWidth: root.width / 3
            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true

            highlight: Rectangle {
                width: listView.width
                height: listView.currentItem.height
                color: "#883498db"
                y: listView.currentItem.y
            }

            onCurrentItemChanged: {
                productDetails._editingMode = false
                productDetails.dataObject = listView.currentItem.modelData
            }

            highlightFollowsCurrentItem: false
            model: productsModel

            delegate: Item {
                property variant modelData: model

                width: ListView.view.width
                height: 50

                Label {
                    anchors {
                        fill: parent
                        margins: 5
                    }

                    text: qsTr("id:") + " " + model.id + " - " + qsTr("Name:") + " " + model.name + " - " + qsTr("quantity:") + " " + model.quantity + translator.tr

                    verticalAlignment: "AlignVCenter"

                    MouseArea {
                        anchors.fill: parent

                        onClicked: listView.currentIndex = index
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
