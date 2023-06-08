from PIL import Image


# --------------------------------
# Multiple focos and backgrounds |
# -------------------------------
focus_list = ["focus/Water.png", "focus/Plants.png", "focus/Stars.png", "focus/Swirl.png", "focus/Water.png"]
bg_list = ["background/Bricks.png", "background/Canada.png", "background/Green.png", "background/Purple.png","background/Wood.png"];

img_count = 0

for bg in bg_list:
    for focus in focus_list:
        overlay_image = Image.open(focus).convert("RGBA")
        background_image = Image.open(bg).convert("RGBA")
        background_image.paste(overlay_image, (0,0), overlay_image)
        background_image.save("exported-" + str(img_count) + ".png")
        img_count = img_count + 1


# ----------------------------
# Single foco and background |
# ---------------------------
overlay_image = Image.open("focus/Water.png").convert("RGBA")
background_image = Image.open("background/Wood.png").convert("RGBA")

background_image.paste(overlay_image, (0, 0), overlay_image)

background_image.show()
background_image.save("exported.png")
