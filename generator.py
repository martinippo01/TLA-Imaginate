from PIL import Image
overlay_image = Image.open("src/backend/code-generation/python/focus/Water.png").convert("RGBA")
background_image = Image.open("src/backend/code-generation/python/background/Bricks.png").convert("RGBA")
background_image.paste(overlay_image, (0, 0), overlay_image)
background_image.show()
background_image.save("exported.png")
