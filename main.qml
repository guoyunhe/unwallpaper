import QtQuick 2.7
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import Unwallpaper 1.0

Window {
    visible: true
    width: 960
    height: 640
    title: "Unwallpaper"

    Item {
        id: navbar
        width: parent.width
        height: 40
        clip: true
        z: 1

        FastBlur {
            width: parent.width
            height: content.height
            source: content
            radius: 32
        }

        Rectangle {
            width: parent.width
            height: parent.height
            color: "#AAFFFFFF"
        }

        Row {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 20

            Nav {
                id: latestPhotoNav
                //: Navbar entry
                text: qsTr("Latest")
                active: true
            }

            Nav {
                id: popularPhotoNav
                //: Navbar entry
                text: qsTr("Popular")
                active: false
            }

            Nav {
                id: curatedPhotoNav
                //: Navbar entry
                text: qsTr("Curated")
                active: false
            }

            Nav {
                id: downloadedPhotoNav
                //: Navbar entry
                text: qsTr("Downloaded")
                active: false
            }

            Nav {
                id: aboutPageNav
                //: Navbar entry
                text: qsTr("About")
                active: false
            }
        }
    }

    Item {
        id: content
        width: parent.width
        height: parent.height

        PhotoList {
            id: latestPhotoList
            visible: latestPhotoNav.active
            model: PhotoListModel {
                order: PhotoListModel.Latest
            }
        }

        PhotoList {
            id: popularPhotoList
            visible: popularPhotoNav.active
            model: PhotoListModel {
                order: PhotoListModel.Popular
            }
        }

        PhotoList {
            id: curatedPhotoList
            visible: curatedPhotoNav.active
            model: PhotoListModel {
                order: PhotoListModel.Latest
                curated: true
            }
        }

        PhotoList {
            id: downloadedPhotoList
            visible: downloadedPhotoNav.active

            model: LocalPhotoListModel {
            }
        }

        AboutPage {
            id: aboutPage
            visible: aboutPageNav.active
        }
    }

}
