val earth : {setting: "./earth.png"}
val mars : {setting: "./mars.png", color: ""}

def setLocation(location):
    .addBackground(location.setting)

def addSpaceship(spaceship):
    .addFlavour(spaceship.spaceship)

def addCharacters(characters):
    .addFlavour(characters.characters)

Imaginate
    .forEachFocus(earth, mars)
    .setLocation(earth)
    .renderAll()


