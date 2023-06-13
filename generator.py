from PIL import Image, ImageEnhance
import random

def overlay_images(background_image, overlay_image, position):
	modified_image = background_image.copy()
	overlay_with_alpha = Image.new("RGBA", overlay_image.size)
	overlay_with_alpha = Image.blend(overlay_with_alpha, overlay_image, 1)
	modified_image.paste(overlay_with_alpha, position, overlay_with_alpha)
	return modified_image
file_paths = ["src/backend/code-generation/python/focos/Nike.png"]
images = [Image.open(name).convert("RGBA") for name in file_paths]


# ADD_CONTRAST 
images = [ ImageEnhance.Contrast(image).enhance(2) for image in images]


# PICK_FLAVOUR 
possible_flavours = ["src/backend/code-generation/python/flavours/Water.png", "src/backend/code-generation/python/flavours/Plants.png", "src/backend/code-generation/python/flavours/Fire.png"]
flavour_image = Image.open(possible_flavours[random.randint(0, len(possible_flavours) - 1)]).convert("RGBA")
position = (0, 0)
images = [ overlay_images(image, flavour_image, position) for image in images]


# SAVE_IMAGES 
count = 0
for image, file_path in zip(images, file_paths):
	image.save("exported-" + str(count) + ".png")
	count = count + 1

