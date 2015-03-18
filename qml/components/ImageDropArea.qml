import QtQuick 2.4
import QtQuick.Controls 1.3

Rectangle {
    id: root

    property alias source: image.source

    width: 150
    height: 150

    color: "transparent"
    radius: 10
    antialiasing: true

    border {
        width: 2
        color: "black"
    }

    Label {
        anchors {
            fill: parent
            margins: 10
        }

        horizontalAlignment: "AlignHCenter"
        verticalAlignment: "AlignVCenter"
        text: qsTr("Drag Image Here")
        wrapMode: "Wrap"
        font.pointSize: root.height / 10
    }

    DropArea {
        anchors.fill: parent

        onDropped: {
            if (drop.hasUrls) {
                var file = drop.urls[0]
                if (file.slice(file.length - 3) === "png" || file.slice(file.length - 3) === "jpg")
                    image.source = file
            }
        }
    }

    Image {
        id: image

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }
}
