val earth : {setting: "./earth.png"}
val mars : {setting: "./mars.png", color: ""}

def setLocation(location):
    .addBackground(location.setting)

Imaginate
    .forEachFocus("earth.setting", "mars.setting")
    .setLocation(earth)
    .renderAll()


