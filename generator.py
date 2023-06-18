from PIL import Image, ImageEnhance
import random

def overlay_images(background_image, overlay_image, position):
	modified_image = background_image.copy()
	overlay_with_alpha = Image.new("RGBA", overlay_image.size)
	overlay_with_alpha = Image.blend(overlay_with_alpha, overlay_image, 1)
	modified_image.paste(overlay_with_alpha, position, overlay_with_alpha)
	return modified_image

def function(images, obj):

	# ADD_FLAVOUR 
	flavour_image = Image.open(0).convert("RGBA")
	position = (0, 0)
	images = [ overlay_images(image, flavour_image, position) for image in images]


file_paths = ["src/backend/code-generation/python/background/Bricks.png", "src/backend/code-generation/python/background/Green.png"]
images_map = lambda image: Image.open(image).convert("RGBA")
images = list(map(images_map, file_paths))


function(images, bricks)


# SAVE_IMAGES 
count = 0
for image, file_path in zip(images, file_paths):
	image.save("exported-" + str(count) + ".png")
	count = count + 1

