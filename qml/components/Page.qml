import QtQuick 2.4

FocusScope {
    id: root

    default property alias content: contentItem.data
    property alias titleBar: titleBarContainer.data
    property bool active: false
    property string __type: "Page"

    signal activated
    signal currentItemChanged

    objectName: "Page"

    Component.onCompleted: {
        if (__type === "Page")
            console.warn("Did not overwrite __type, this might cause problems!")

        if (root.parent === null || root.parent.toString().substring(0, 9) !== "StackView") {
            root.activated()
            root.active = true
            root.focus = true
        }
    }

    Connections {
        target: root.parent !== null && root.parent.toString().substring(0, 9) === "StackView" ? root.parent : root

        onCurrentItemChanged: {
            if (root.parent.currentItem === root) {
                root.active = true
                root.activated()
                root.focus = true
            } else {
                root.active = false
            }
        }
    }

    FocusScope {
        id: titleBarContainer

        height: childrenRect.height
        width: parent.width
        focus: true
    }

    FocusScope {
        id: contentItem

        anchors {
            top: titleBarContainer.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        focus: true
    }
}
