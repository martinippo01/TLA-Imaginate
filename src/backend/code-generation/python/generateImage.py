from PIL import Image

# Focos -> Un conjunto de posibles overlay images
# Background image
# Flavours -> Un conjunto de posibles overlay images
# Filters -> Conjunto
#           -
#           -
#           -
#           -

# Open the overlay image and convert it to RGBA mode
overlay_image = Image.open("focus/Water.png").convert("RGBA")
background_image = Image.open("background/Bricks.png").convert("RGBA")

background_image.paste(overlay_image, (0, 0), overlay_image)

background_image.show()
