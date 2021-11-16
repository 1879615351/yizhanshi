import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.12  //这个版本有菜单栏
Rectangle{
    width:  700
    height: 480
Image {
    id:    img
    cache: false  //不缓存防止卡死
    anchors.fill: parent
}
Connections{
target:imgSender  //发送信号的对象的id
onCallQmlRefeshImg:{    //on+信号名得到槽函数
img.source = ""
//最后这个pimg是注册到qml中的ImageProvider的id
//调用这句话会触发pimg中的requestImage函数(虚函数)
img.source = "image://imgProvider"
}
}
}
