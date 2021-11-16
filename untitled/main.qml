import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
ApplicationWindow  {
    id:root
    visible: true
    width:1800
    height:1020
    x:(Screen.desktopAvailableWidth-width)/2
    y:(Screen.desktopAvailableHeight-height)/2
    maximumHeight: height
    minimumHeight: height
    maximumWidth: width
    minimumWidth: width
    flags: Qt.Window |Qt.FramelessWindowHint
    function onMiniWindow(){
        root.visibility= Window.Minimized
    }
    function resetPanel(){
        labelpanl.visible=false
        usepanel.visible=false
        trainpanel.visible=false
    }
    function onLabelPanelSignal(){
        root.resetPanel()
        labelpanl.visible=true
    }
    function onTrainPanelSignal(){
        root.resetPanel()
        trainpanel.visible=true
    }
    function onUsePanelSignal(){
        root.resetPanel()
        usepanel.visible=true
    }
    MouseArea { //为窗口添加鼠标事件
            x:0
            y:0
            width:500
            height:50
            acceptedButtons: Qt.LeftButton //只处理鼠标左键
            property point clickPos: "0,0"
            onPressed: { //接收鼠标按下事件
                    clickPos  = Qt.point(mouse.x,mouse.y)
            }
            onPositionChanged: { //鼠标按下后改变位置
                    var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                    root.setX(root.x+delta.x)
                    root.setY(root.y+delta.y)
            }
        }
    SidePanel{
        id:sidepanel
        x:0
        y:0
    }
    LabelPanel{
        id:labelpanl
        x:sidepanel.x+sidepanel.width
        y:0
        visible: true
    }
    TrainPanel{
        id:trainpanel
        x:sidepanel.x+sidepanel.width
        y:0
        visible: false
    }
    UsePanel{
        id:usepanel
        x:sidepanel.x+sidepanel.width
        visible: false
        y:0
    }
    Component.onCompleted: {
        usepanel.miniWindow.connect(root.onMiniWindow)
        trainpanel.miniWindow.connect(root.onMiniWindow)
        labelpanl.miniWindow.connect(root.onMiniWindow)
        sidepanel.labelPanelSignal.connect(root.onLabelPanelSignal)
        sidepanel.trainPanelSignal.connect(root.onTrainPanelSignal)
        sidepanel.usePanelSignal.connect(root.onUsePanelSignal)
        labelpanl.addLabel.connect(sidepanel.onAddLabel)
    }
}
