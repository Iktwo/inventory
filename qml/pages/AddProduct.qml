import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import Notifications 1.0
import components 2.0

Page {
    focus: true
    __type: "AddProduct"

    onActivated: textFieldId.forceActiveFocus()

    FocusScope {
        anchors {
            fill: parent
            margins: 10
        }

        ColumnLayout {
            RowLayout {
                Label {
                    text: qsTr("Id")
                    Layout.preferredWidth: 120
                    wrapMode: "Wrap"
                }

                TextField {
                    id: textFieldId

                    anchors.verticalCenter: parent.verticalCenter

                    validator: RegExpValidator {
                        regExp: /[0-9]+/
                    }

                    inputMethodHints: Qt.ImhDigitsOnly
                    placeholderText: qsTr("Product id")
                }
            }

            RowLayout {
                Label {
                    text: qsTr("Name")
                    Layout.preferredWidth: 120
                    wrapMode: "Wrap"
                }

                TextField {
                    id: textFieldName

                    anchors.verticalCenter: parent.verticalCenter
                    placeholderText: qsTr("Product name")
                }
            }

            RowLayout {
                Label {
                    text: qsTr("Quantity")
                    Layout.preferredWidth: 120
                    wrapMode: "Wrap"
                }

                SpinBox {
                    id: spinBoxQuantity

                    anchors.verticalCenter: parent.verticalCenter

                    minimumValue: 0
                    maximumValue: 999
                }
            }

            ImageDropArea {
                id: imageDropArea

                Layout.preferredHeight: 300
                Layout.preferredWidth: 300
            }

            RowLayout {
                anchors.left: parent.left

                Button {
                    text: qsTr("Add")
                    onClicked: {
                        if (!isNaN(parseInt(textFieldId.text))) {
                            if (productsModel.addProduct(textFieldId.text, textFieldName.text, spinBoxQuantity.value, imageDropArea.source)) {
                                goToMainPage()
                            }
                        } else {
                            notificationBar.showMessage(qsTr("Can't add product without id"), Notifications.Error, Notifications.Long);
                        }
                    }

                    Keys.onEnterPressed: clicked()
                    Keys.onReturnPressed: clicked()
                }

                Button {
                    text: qsTr("Cancel")
                    onClicked: stackView.pop()
                    Keys.onEnterPressed: clicked()
                    Keys.onReturnPressed: clicked()
                }
            }
        }
    }
}
