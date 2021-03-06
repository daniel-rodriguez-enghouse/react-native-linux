import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Button {
    id: buttonRoot

    property string p_accessibilityLabel
    property string p_title
    property string p_color: "#e0e0e0"
    property bool p_disabled: false
    property bool p_onPress: false
    property string p_testID

    property var buttonManager: null

    text: p_title
    objectName: p_testID

    implicitHeight: 40
    implicitWidth: 100

    background: Rectangle {
        color: buttonRoot.down ? Qt.darker(buttonRoot.p_color, 1.2) : buttonRoot.p_color
        visible: !buttonRoot.flat || buttonRoot.down || buttonRoot.checked || buttonRoot.highlighted
    }

    onPressed: buttonManager.sendPressedNotificationToJs(buttonRoot)
}
