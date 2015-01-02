import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import Notifications 1.0

FocusScope {
    focus: true

    FocusScope {
        anchors {
            fill: parent
            margins: 10
        }

        ColumnLayout {
            RowLayout {
                Label {
                    text: qsTr("Name")
                }

                TextField {
                    id: textFieldName

                    placeholderText: qsTr("Product name")
                }
            }

            RowLayout {
                Label {
                    text: qsTr("Id")
                }

                TextField {
                    id: textFieldId

                    validator: RegExpValidator {
                        regExp: /[0-9]+/
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                    placeholderText: qsTr("Product id")
                }
            }

            RowLayout {
                anchors.left: parent.left

                Button {
                    text: qsTr("Add")
                    onClicked: {
                        if (!isNaN(parseInt(textFieldId.text)))
                            productsModel.addProduct(textFieldName.text);
                        else
                            notificationBar.showMessage(qsTr("Can't add product without id"), Notifications.Error, Notifications.Long);
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
