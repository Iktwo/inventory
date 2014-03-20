import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1


Item {
    property variant dataObject

    property bool _editingMode: false

    ColumnLayout {
        RowLayout {
            Button {
                text: qsTr("Edit") + translator.tr

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
                    if (nameField.text != "")
                        dataObject.name = nameField.text
                }
            }
        }

        RowLayout {
            spacing: 10

            Label {
                text: qsTr("Name") + translator.tr + ":"
            }

            TextField {
                id: nameField

                readOnly: !_editingMode
                text: dataObject !== undefined ? dataObject.name : ""
                placeholderText: qsTr("Name") + translator.tr

            }
        }
    }
}
