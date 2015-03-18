import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1


Item {
    property variant dataObject

    property bool _editingMode: false

    onDataObjectChanged: {
        if (!_editingMode)
            spinBoxQuantity.value = dataObject.quantity
    }

    ColumnLayout {
        Rectangle {
            width: 300
            height: 300
            color: "transparent"
            border {
                color: "black"
                width: 2
            }

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: dataObject !== undefined && dataObject.image !== "" ? "file://" + imagesDir + "/" + dataObject.image : ""
            }
        }

        RowLayout {
            spacing: 10

            Label {
                text: qsTr("Name") + translator.tr + ":"
                Layout.preferredWidth: 120
                wrapMode: "Wrap"
            }

            TextField {
                id: nameField

                readOnly: !_editingMode
                text: dataObject !== undefined ? dataObject.name : ""
                placeholderText: qsTr("Name") + translator.tr

            }
        }

        RowLayout {
            Label {
                text: qsTr("Quantity") + translator.tr + ":"
                Layout.preferredWidth: 120
                wrapMode: "Wrap"
            }

            SpinBox {
                id: spinBoxQuantity

                minimumValue: 0
                maximumValue: 999

                enabled: _editingMode
            }
        }

        RowLayout {
            Button {
                text: (_editingMode ? qsTr("Cancel") : qsTr("Edit")) + translator.tr

                onClicked: {
                    _editingMode = !_editingMode

                    if (!_editingMode)
                        dataObjectChanged()
                    else
                        nameField.focus = true
                }
            }

            Label {
                text: _editingMode ? "Editing" : ""
                color: "red"
            }

            Button {
                text: qsTr("Save") + translator.tr
                visible: _editingMode
                onClicked: {
                    if (nameField.text != "") {
                        dataObject.name = nameField.text
                    }

                    if (spinBoxQuantity.value !== dataObject.quantity) {
                        dataObject.quantity = spinBoxQuantity.value
                    }

                    _editingMode = false
                }
            }
        }
    }
}
