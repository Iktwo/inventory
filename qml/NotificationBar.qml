import QtQuick 2.4
import QtQuick.Controls 1.3
import Notifications 1.0

Rectangle {
    id: root

    function close() {
        timerClose.stop()
        labelMessage.text = ""
        height = 0
    }

    function showMessage(message, type, duration) {
        labelMessage.text = message
        height = 40
        color = notifications.colorForType(type);
        timerClose.interval = duration

        if (duration === Notifications.Infinite)
            return

        timerClose.restart()
    }

    color: "#3498db"
    Behavior on height { NumberAnimation { easing.type: Easing.InOutCubic } }

    Timer {
        id: timerClose
        onTriggered: root.close()
    }

    Label {
        id: labelMessage

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left; leftMargin: 15
            right: parent.right; rightMargin: 15
        }

        clip: true
        color: "#ffffff"
        verticalAlignment: "AlignVCenter"
        maximumLineCount: 4
        wrapMode: "Wrap"
    }

    Image {
        id: imageClose

        anchors {
            right: parent.right; rightMargin: 10
            verticalCenter: parent.verticalCenter
        }

        source: "qrc:/images/remove"
        height: Math.min(parent.height * 0.9, parent.width / 5)
        width: height
        sourceSize.height: Math.min(parent.height * 0.9, parent.width / 5)
        sourceSize.width: Math.min(parent.height * 0.9, parent.width / 5)

        MouseArea {
            anchors.fill: parent
            onClicked: root.close()
        }
    }
}
