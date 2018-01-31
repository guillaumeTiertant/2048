import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3



Item {
    id: root
    width: 500
    height: 700

    property double responsive: ( root.width < root.height)? root.width/500: root.height/700

    MultiPointTouchArea {
        id: zoneTactile
        anchors.fill : parent
        mouseEnabled: true

        touchPoints : TouchPoint {
            id : touch
            property int startX: 0
            property int startY: 0
        }



        onPressed: {
            touch.startX = touch.x;
            touch.startY = touch.y;
        }

        onReleased: {
            var deltaX = touch.x - touch.startX;
            var deltaY = touch.y - touch.startY;
            var horizontal = Math.abs(deltaX) > Math.abs(deltaY);

            if ( horizontal ) {
                if (deltaX > 20){
                    Context.setDirection("right");
                }
                else if (deltaX < -20){
                    Context.setDirection("left");
                }
            }

            else {
                if (deltaY > 20){
                    Context.setDirection("down");
                }
                else if (deltaY < -20){
                    Context.setDirection("up");
                }
            }
        }
    }


Plateau {
    id: grid
}


Rectangle{
    id:score
    x: 10
    y:(root.width < root.height)? 10 : grid.y
    width: 100  * root.responsive
    height: 40 * root.responsive
    Text {
        color: "#4480f7"
        text: Context.score
        fontSizeMode: Text.Fit
        font.pointSize: 18 * root.responsive
        verticalAlignment: Text.AlignVCenter
    }
}


Rectangle {
    id: newGameButton
    x : (root.width < root.height)? grid.x : 10
    y: (root.width < root.height) ? root.height - height - score.height : score.height + score.y
    width: height * 2.5
    height: 60 * root.responsive
    color: "#4480f7"
    radius: 10

    border.color: "#7a7d81"
    border.width: 3
    Text {
        color: "#ffffff"
        anchors.fill: parent
        text:  "New Game"
        font.pointSize: parent.width/10
        font.bold: true
        font.family: "Verdana"
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        MouseArea{
            anchors.fill: parent
            onClicked: Context.setNewGame("new");
        }
    }
}
Component.onCompleted: Context.setNewGame("new");

}
